/*****************************************************************************
*   Copyright (C) 2015  Thales Areco Bandiera Paiva
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along
*   with this program; if not, write to the Free Software Foundation, Inc.,
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*****************************************************************************/

#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/time.h>

#include "mw100_recorder.h"
#include "cpu_profiler.h"

#define MAX_BUFF_SIZE       1024
#define MAX_FILENAME_LEN    100
#define MAX_IP4_LEN         20
#define MAX_REQ_SIZE        16

typedef struct _info {
    char    mw100ip4[MAX_IP4_LEN];
    int     mw100port;
    double  time_interval;
    int     channel;
} mw100_recorder_info;

int                 Running;
int                 PowerDump;
char                PowerDumpOutput[MAX_FILENAME_LEN];
double              AveragePowerConsumption;
pthread_t           MW100RecorderThreadID;
struct timeval      StartTime, EndTime;
mw100_recorder_info RecordingInfo;
mw100_record_info   UserInfo;

void  fatal(char message[], int error_code);
void *mw100_recorder_thread_init(void *vp_info);
void  mw100_recorder_thread(char mw100ip4[], int mw100port, double time_interval, int channel);

void mw100_enable_power_dump(char filename[]) {
    PowerDump = 1;
    strcpy(PowerDumpOutput, filename);
}

void mw100_recorder_init(char mw100ip4[], int mw100port, double time_interval, int channel) {
    strcpy(RecordingInfo.mw100ip4, mw100ip4);
    RecordingInfo.mw100port      = mw100port;
    RecordingInfo.time_interval  = time_interval;
    RecordingInfo.channel        = channel;
    PowerDump                    = 0;
}

void mw100_recorder_start(int verbose) {
    int res;

    Running = 1;
    AveragePowerConsumption = 0;

    gettimeofday(&StartTime, NULL);
    res = pthread_create(&MW100RecorderThreadID, NULL, mw100_recorder_thread_init, NULL);
    if (res < 0)
        fatal("[-] Error creating mw100 recorder thread.", 1);
}

void *mw100_recorder_thread_init(void *null) {
    mw100_recorder_thread(RecordingInfo.mw100ip4, RecordingInfo.mw100port, RecordingInfo.time_interval, RecordingInfo.channel);

    return NULL;
}

double extract_power_from_mw100_response(char response[]) {
    int     i;
    double  power;

    for (i = 0; response[i] != 0; i++) {
        if (response[i] == 'N') {
            sscanf(&response[i], "N %*d W + %lf", &power);
            return power;
       }
    }
    fprintf(stderr, "[-] Response: \n%s\n", response);
    fprintf(stderr, "[-] Unable to extract power from response. \n");
    return -1;
}

void mw100_recorder_thread(char mw100ip4[], int mw100port, double time_interval, int channel) {
    int     sockfd, n, i;
    double  tmp_power;
    char    recv_buff[MAX_BUFF_SIZE];
    struct  sockaddr_in serv_addr;
    char    request[MAX_REQ_SIZE];
    double  tmp_time, start_time;
    struct  timeval tv_tmp_time;
    FILE    *p_out;

    cpu_profiler_init();
    p_out = NULL;
    if (PowerDump == 1) {
        if (strcmp(PowerDumpOutput, "") == 0)
            p_out = stdout;
        else {
            p_out = fopen(PowerDumpOutput, "a");
            if (!p_out) {
                fprintf(stderr, "[-] Couldn't open %s. Using stdout instead.\n", PowerDumpOutput);
                p_out = stdout;
            }
        }
    }
    start_time = StartTime.tv_sec + (StartTime.tv_usec/1000000.0);

    memset(recv_buff, '0' ,sizeof(recv_buff));
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        fatal("[-] Unable to open socket. \n", 1);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(mw100port);
    serv_addr.sin_addr.s_addr = inet_addr(mw100ip4);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        fatal("[-] Unable to connect. \n", 1);

    n = recv(sockfd, recv_buff, sizeof(recv_buff) - 1, 0);                      /* ACK */

    sprintf(request, "FD0,%d,%d\n", channel, channel);
    AveragePowerConsumption = 0;
    i = 0;
    while (n > 0 && Running == 1) {
        if (send(sockfd, request, 8, 0) == -1)
            fatal("[-] Unable to send.", 1);
        n = recv(sockfd, recv_buff, sizeof(recv_buff) - 1, 0);
        recv_buff[n] = 0;
        tmp_power = extract_power_from_mw100_response(recv_buff);
        if (PowerDump == 1) {
            gettimeofday(&tv_tmp_time, NULL);
            tmp_time = tv_tmp_time.tv_sec + (tv_tmp_time.tv_usec/1000000.0);
            fprintf(p_out, "%.4lf,%.2lf,%.2lf\n", tmp_time - start_time, tmp_power, get_cpu_usage());
            fflush(p_out);
        }
        AveragePowerConsumption += tmp_power;
        i++;
        usleep(1000*1000*time_interval);
    }
    shutdown(sockfd, 2);
    AveragePowerConsumption /= i;
    if (PowerDump == 1)
        fclose(p_out);
    cpu_profiler_clean();
}

void mw100_recorder_stop(int verbose) {
    double start_time, end_time, elapsed_time;

    Running = 0;
    pthread_join(MW100RecorderThreadID, NULL);
    gettimeofday(&EndTime, NULL);

    start_time   = StartTime.tv_sec + (StartTime.tv_usec/1000000.0);
    end_time     = EndTime.tv_sec+(EndTime.tv_usec/1000000.0);
    elapsed_time = end_time - start_time;

    UserInfo.elapsed_time  = elapsed_time;
    UserInfo.average_power = AveragePowerConsumption;
    UserInfo.total_energy  = elapsed_time*AveragePowerConsumption;

    if (verbose) {
        printf("[+] Recording Time           : %-10.2lf s\n", elapsed_time);
        printf("[+] Av. Power Consumption    : %-10.2lf W\n", UserInfo.average_power);
        printf("[+] Total Energy Consumption : %-10.2lf J\n", UserInfo.total_energy);
    }
}

void mw100_get_recorded_info(mw100_record_info *p_user_info) {
    p_user_info->elapsed_time  = UserInfo.elapsed_time;
    p_user_info->average_power = UserInfo.average_power;
    p_user_info->total_energy  = UserInfo.total_energy;
}

void fatal(char message[], int error_code) {
    perror(message);
    exit(error_code);
}

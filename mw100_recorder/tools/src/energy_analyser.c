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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../../src/mw100_recorder.h"

#include "MW100_INFO.h"

#define MAX_COMMAND_LEN         1024
#define RUN_TIME_INTERVAL       5
#define IDLE_BENCHMARK_TIME     10


typedef struct _stats {
    double  mean;
    double  min;
    double  max;
    double  var;
} Stats;

int HumanReadableOutput;

void print_stats(Stats *stats, char command[]);
void run_suite(int n, char command[]);
void get_stats(Stats *stats, double array[], int n);

int main(int argc, char *argv[]) {
    int i, n;
    char command[MAX_COMMAND_LEN];

    if (argc < 4) {
        perror("[-] Usage: energy_analyser <h|d> <n> <command_line> \n");
        exit(1);
    }
    HumanReadableOutput =  (strcmp(argv[1], "h") == 0) ? 1 : 0;
    n = atoi(argv[2]);

    strcpy(command, argv[3]);
    for (i = 4; i < argc; i++) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }
    strcat(command, " > /dev/null");
    run_suite(n, command);
    return 0;
}

void run_suite(int n, char command[]) {
    int     i;
    double *energy_values;
    double  baseline_power_consumption;
    Stats   stats;
    mw100_record_info record_info;

    energy_values = malloc(n*sizeof(*energy_values));
    if (energy_values == NULL) {
        perror("[-] ... \n");
        exit(1);
    }

    sleep(IDLE_BENCHMARK_TIME/2);

    mw100_recorder_init(Mw100_IP, MW100_PORT, MW100_TIME_INTERVAL, MW100_CHANNEL);
    mw100_recorder_start(0);
    sleep(IDLE_BENCHMARK_TIME);
    mw100_recorder_stop(0);
    mw100_get_recorded_info(&record_info);
    baseline_power_consumption = record_info.average_power;

    if (HumanReadableOutput == 1)  {
        printf("[*] Command: %s\n", command);
        printf("[*] Baseline Power Consumption: %.4lf\n", baseline_power_consumption);
        printf("[*] Iteration   Time (s)   Av. Power (W)   Total Energy (J)   User Energy (J) \n");
    }
    for (i = 0; i < n; i++) {
        sleep(RUN_TIME_INTERVAL);
        mw100_recorder_start(0);
        system(command);
        mw100_recorder_stop(0);

        mw100_get_recorded_info(&record_info);
        if (record_info.average_power < baseline_power_consumption)
            energy_values[i] = 0;
        else
            energy_values[i] = record_info.total_energy - baseline_power_consumption*record_info.elapsed_time;

        if (HumanReadableOutput == 1) {
            printf("[.] %-9d   %-8.4lf   %-13.4lf   ", i, record_info.elapsed_time, record_info.average_power);
            printf("%-16.4lf   %-15.4lf\n", record_info.total_energy, energy_values[i]);
        }
        else {
            /* command, i, time, av_power, tot_energy, user_energy */
            printf("%s,%d,%.4lf,%.4lf,%.4lf,%.4lf,%.4lf\n", command, i, baseline_power_consumption,
                record_info.elapsed_time, record_info.average_power, record_info.total_energy, energy_values[i]);
        }
    }
    get_stats(&stats, energy_values, n);
    print_stats(&stats, command);
}

void get_stats(Stats *stats, double array[], int n) {
    int     i;
    double  exp_x2;

    exp_x2      = 0;
    stats->mean = 0;
    stats->var  = 0;
    if (n <= 0) {
        stats->min  = 0;
        stats->max  = 0;
        return;
    }
    stats->min  = array[0];
    stats->max  = array[0];

    for (i = 0; i < n; i++) {
        stats->mean += array[i];
        exp_x2      += array[i]*array[i];
        if (array[i] < stats->min)
            stats->min = array[i];
        if (array[i] > stats->max)
            stats->max = array[i];
    }
    stats->mean /= n;
    exp_x2      /= n;

    stats->var   = exp_x2 - stats->mean*stats->mean;
}

void print_stats(Stats *stats, char command[]) {
    if (HumanReadableOutput == 1) {
        printf("[*] Statistics \n");
        printf("[.] Mean      : %.4lf\n", stats->mean);
        printf("[.] Min       : %.4lf\n", stats->min);
        printf("[.] Max       : %.4lf\n", stats->max);
        printf("[.] Var       : %.4lf\n", stats->var);
    }
    else {
        printf("%s,stats,%.4lf,%.4lf,%.4lf,%.4lf\n", command, stats->mean, stats->min, stats->max, stats->var);
    }
}

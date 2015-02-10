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

void run_suite(int n, double baseline_power_consumption, char command[]);

int main(int argc, char *argv[]) {
    int i, n;
    double baseline_power_consumption;
    char command[MAX_COMMAND_LEN];

    if (argc < 4) {
        perror("[-] Usage: energy_analyser <av_pow> <n> <command_line> \n");
        exit(1);
    }
    baseline_power_consumption = atof(argv[1]);
    n = atoi(argv[2]);

    strcpy(command, argv[3]);
    for (i = 4; i < argc; i++) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }
    run_suite(n, baseline_power_consumption, command);
    return 0;
}

void run_suite(int n, double baseline_power_consumption, char command[]) {
    int     i;
    double *energy_values;
    mw100_record_info record_info;

    energy_values = malloc(n*sizeof(*energy_values));
    if (energy_values == NULL) {
        perror("[-] ... \n");
        exit(1);
    }

    mw100_recorder_init(Mw100_IP, MW100_PORT, MW100_TIME_INTERVAL, MW100_CHANNEL);

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
            /* command, i, time, av_power, tot_energy, user_energy */
        printf("%s,%d,%.4lf,%.4lf,%.4lf,%.4lf,%.4lf\n", command, i, baseline_power_consumption,
            record_info.elapsed_time, record_info.average_power, record_info.total_energy, energy_values[i]);
    }
}

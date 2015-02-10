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

#include "sortbench.h"
#include "../../../mw100_recorder/include/mw100_recorder.h"

int check_if_sorted(double array[], int array_size);
void run_benchmark(int n, int array_size, double baseline_power_consumption, char benchname[]);
void populate_random_array(double array[], int array_size);

int main(int argc, char *argv[]) {
    int     n, seed, size;
    double  baseline_power_consumption;

    if (argc != 5) {
        perror("[-] Usage: bench <n> <array_size> <seed> <baseline_power_cons>\n");
        exit(1);
    }

    n    = atoi(argv[1]);
    size = atoi(argv[2]);
    seed = atoi(argv[3]);
    baseline_power_consumption = atof(argv[4]);
    srand(seed);
    run_benchmark(n, size, baseline_power_consumption, argv[0]);
    exit(0);
}

int check_if_sorted(double array[], int array_size) {
    int i;

    for (i = 1; i < array_size; i++)
        if (array[i] < array[i - 1])
            return 0;
    return 1;
}

void populate_random_array(double array[], int array_size) {
    int i;

    for (i = 0; i < array_size; i++)
        array[i] = rand()*(rand()/(RAND_MAX + 1.0));
}

void run_benchmark(int n, int array_size, double baseline_power_consumption, char benchname[]) {
    int     i;
    double  user_energy;
    double  *array;
    mw100_record_info record_info;

    array = malloc(array_size*sizeof(*array));
    if(array == NULL) {
        perror("[-] Memory allocation failed.\n");
        exit(3);
    }

    mw100_recorder_init(Mw100_IP, MW100_PORT, MW100_TIME_INTERVAL, MW100_CHANNEL);

    for (i = 0; i < n; i++) {
        populate_random_array(array, array_size);

        sleep(2);
        mw100_recorder_start(0);
        sort(array, array_size);
        mw100_recorder_stop(0);
        if (!check_if_sorted(array, array_size)) {
            perror("[-] Sort failed!\n");
            exit(2);
        }

        mw100_get_recorded_info(&record_info);
        if (record_info.average_power < baseline_power_consumption)
            user_energy = 0;
        else
            user_energy = record_info.total_energy - baseline_power_consumption*record_info.elapsed_time;
        /* benchname, array_size, i, time, av_power, tot_energy, user_energy */
        printf("%s,%d,%d,%.4lf,%.4lf,%.4lf,%.4lf,%.4lf\n", benchname, array_size, i, baseline_power_consumption,
            record_info.elapsed_time, record_info.average_power, record_info.total_energy, user_energy);
    }
}

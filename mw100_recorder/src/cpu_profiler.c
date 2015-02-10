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

/* Based on:
 *  http://phoxis.org/2013/09/05/finding-overall-and-per-core-cpu-utilization/
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cpu_profiler.h"

FILE    *StatFilePointer;
ticks_t TotalTicks;
ticks_t IdleTicks;

void update_total_and_idle_ticks();

void cpu_profiler_init() {
    StatFilePointer = fopen(STAT_FILENAME, "r");
    update_total_and_idle_ticks();
}

void cpu_profiler_clean() {
    fclose(StatFilePointer);
    TotalTicks = 0;
    IdleTicks  = 0;
}

void update_total_and_idle_ticks() {
    int     i, retval;
    char    line[MAX_LINE];
    ticks_t fields[N_OF_CPU_FIELDS];

    fseek(StatFilePointer, 0, SEEK_SET);
    fflush(StatFilePointer);
    fgets(line, MAX_LINE, StatFilePointer);
    retval = sscanf (line, "cpu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu",
                     &fields[0], &fields[1], &fields[2], &fields[3],
                     &fields[4], &fields[5], &fields[6], &fields[7],
                     &fields[8], &fields[9]);

    if (retval < 4) {
        perror("[-] Error reading /proc/stat cpu field.\n");
        exit(1);
    }

    TotalTicks = 0;
    for (i = 0; i < N_OF_CPU_FIELDS; i++)
        TotalTicks += fields[i];
    IdleTicks = fields[IDLE_TICKS_FIELD] + fields[IOWAIT_TICKS_FIELD];
}

double get_cpu_usage() {
    double  usage;
    ticks_t total_ticks_old, idle_ticks_old;
    ticks_t total_ticks_delta, idle_ticks_delta;

    total_ticks_old = TotalTicks;
    idle_ticks_old  = IdleTicks;

    update_total_and_idle_ticks();

    total_ticks_delta  = TotalTicks - total_ticks_old;
    idle_ticks_delta   = IdleTicks  - idle_ticks_old;

    usage = ((total_ticks_delta - idle_ticks_delta)/(double) total_ticks_delta)*100;
    return usage;
}

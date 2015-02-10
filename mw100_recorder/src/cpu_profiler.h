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

#ifndef CPU_PROFILER_H
#define CPU_PROFILER_H

#define MAX_LINE            1024
#define N_OF_CPU_FIELDS     10
#define IDLE_TICKS_FIELD    3
#define IOWAIT_TICKS_FIELD  4
#define STAT_FILENAME       "/proc/stat"

typedef unsigned long long int ticks_t;

void   cpu_profiler_init();
void   cpu_profiler_clean();
double get_cpu_usage();

#endif

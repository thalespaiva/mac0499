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

#ifndef SORTBENCH_H
#define SORTBENCH_H

#define RUN_TIME_INTERVAL   3
#define MAX_BENCHNAME       20
#define MAX_ARRAY_SIZE      10000000

#define Mw100_IP            "200.18.98.206"
#define MW100_PORT          34318
#define MW100_CHANNEL       9
#define MW100_TIME_INTERVAL 0.5

void sort(double array[], int array_size);

#endif

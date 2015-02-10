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

#ifndef MW100_RECORDER_H
#define MW100_RECORDER_H

typedef struct _mw100_record_info {
    double elapsed_time;
    double average_power;
    double total_energy;
} mw100_record_info;

void mw100_recorder_init(char mw100ip4[], int mw100port, double time_interval, int channel);
void mw100_recorder_start(int verbose);
void mw100_recorder_stop(int verbose);
void mw100_get_recorded_info(mw100_record_info *p_user_info);
void mw100_enable_power_dump(char filename[]);

#endif

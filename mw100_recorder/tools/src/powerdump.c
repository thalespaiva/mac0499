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

int main(int argc, char *argv[]) {
    int   total_time;
    FILE *p_out;

    if (argc <= 1 || argc > 3) {
        perror("[-] Usage: powerdump <total_time> [out_file]\n");
        exit(1);
    }

    total_time = atoi(argv[1]);
    if (argc == 3) {
        p_out = fopen(argv[2], "w");
        if (!p_out) {
            perror("[-] Couldn't open file.");
            exit(1);
        }
        fprintf(p_out, "%d\n", total_time);
        fclose(p_out);
    }
    else
        fprintf(stdout, "%d\n", total_time);

    mw100_recorder_init(Mw100_IP, MW100_PORT, MW100_TIME_INTERVAL, MW100_CHANNEL);
    if (argc == 3)
        mw100_enable_power_dump(argv[2]);
    else
        mw100_enable_power_dump("");
    mw100_recorder_start(0);
    sleep(total_time);
    mw100_recorder_stop(0);

    return 0;
}


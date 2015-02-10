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

#include <stdlib.h>

void wo_non_short_circuit();

int main(int argc, char *argv[]) {
    long i, n;

    n = atoi(argv[1]);
    for (i = 0; i < n; i++)
        wo_non_short_circuit();
    return 0;
}

void wo_non_short_circuit() {
    int a, b;

    a = rand();
    b = rand();
    if ((a < b) && (b > a)) {
        a += b;
        return;
    }
    b += a;
    return;
}

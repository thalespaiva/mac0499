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
#include <string.h>

void redundant_call();

int main(int argc, char *argv[]) {
    long i, n;

    n = atoi(argv[1]);
    for (i = 0; i < n; i++)
        redundant_call();
    return 0;
}

void redundant_call() {
    int i, z;
    char s[] = "Some meaningless chars array to call strlen.";

    for (i = 0, z = 0; i < strlen(s); i++)
        z++;

    return;
}

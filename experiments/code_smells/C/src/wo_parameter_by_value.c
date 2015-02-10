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

#define DATA_SIZE 100

typedef struct _some_struct {
    char data[DATA_SIZE];
} SomeStruct;


void wo_parameter_by_value(SomeStruct *some_struct);
void init_some_struct(SomeStruct *some_struct);

int main(int argc, char *argv[]) {
    long i, n;
    SomeStruct some_struct;

    init_some_struct(&some_struct);
    n = atoi(argv[1]);
    for (i = 0; i < n; i++)
        wo_parameter_by_value(&some_struct);
    return 0;
}

void init_some_struct(SomeStruct *some_struct) {
    int i;

    for (i = 0; i < DATA_SIZE; i++)
        some_struct->data[i] = rand() % 256;
}

void wo_parameter_by_value(SomeStruct *some_struct) {
    char a;

    a = some_struct->data[rand()%DATA_SIZE];
}

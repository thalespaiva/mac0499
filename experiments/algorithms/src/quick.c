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

#define MAX_STACK_SIZE 1000

void swap(double* this, double* that) {
    double tmp;

    tmp   = *this;
    *this = *that;
    *that = tmp;
}

double partition(double array[], int left, int right) {
    int i, j;

    i = left;
    for (j = left + 1; j <= right; ++j) {
        if (array[j] < array[left]) {
            ++i;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[left], &array[i]);

    return i;
}

void iterative_quicksort(double array[], int array_size) {
    double stack[MAX_STACK_SIZE];
    int top, start, end, pivot;

    top = -1;
    stack[++top] = 0;
    stack[++top] = array_size - 1;
    while (top >= 0) {
        end   = stack[top--];
        start = stack[top--];
        pivot = partition(array,start,end);
        if (pivot - 1 > start) {
            stack[++top] = start;
            stack[++top] = pivot - 1;
        }
        if (pivot + 1 < end) {
            stack[++top] = pivot + 1;
            stack[++top] = end;
        }
    }
}

void sort(double array[], int array_size) {
    iterative_quicksort(array, array_size);
}

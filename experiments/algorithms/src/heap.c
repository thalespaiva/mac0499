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

/* From http://rosettacode.org/wiki/Sorting_algorithms/Heapsort#C */

#include <stdlib.h>

void sift_down(double *array, int start, int count);

void swap(double* this, double* that) {
    double tmp;

    tmp   = *this;
    *this = *that;
    *that = tmp;
}

void heapsort(double *array, int count) {
    int start, end;

    for (start = (count - 2)/2; start >= 0; start--) {
        sift_down(array, start, count);
    }

    for (end = count - 1; end > 0; end--) {
        swap(&array[end], &array[0]);
        sift_down(array, 0, end);
    }
}

void sift_down(double *array, int start, int end) {
    int root = start;

    while (root*2+1 < end ) {
        int child = 2*root + 1;
        if ((child + 1 < end) && (array[child] < array[child+1])) {
            child += 1;
        }
        if (array[root] < array[child]) {
            swap(&array[child], &array[root]);
            root = child;
        }
        else
            return;
    }
}

void sort(double array[], int array_size) {
    heapsort(array, array_size);
}

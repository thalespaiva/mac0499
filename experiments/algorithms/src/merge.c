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

#define data_type double

void merge_sort(data_type vec[], int vec_size);

void merge(data_type vec[], int vecSize) {
    int mid, i, j, k;
    data_type *tmp;

    tmp = malloc(vecSize * sizeof(*tmp));
    if (tmp == NULL)
        exit(1);
    mid = vecSize / 2;
    i = 0;
    j = mid;
    k = 0;
    while (i < mid && j < vecSize) {
        if (vec[i] <= vec[j])
            tmp[k] = vec[i++];
        else
            tmp[k] = vec[j++];
        k++;
    }
    if (i == mid)
        while (j < vecSize)
            tmp[k++] = vec[j++];
    else
        while (i < mid)
            tmp[k++] = vec[i++];
    for (i = 0; i < vecSize; ++i)
        vec[i] = tmp[i];
    free(tmp);
}

void merge_sort(data_type vec[], int vec_size) {
    int mid;

    if (vec_size > 1) {
        mid = vec_size/2;
        merge_sort(vec, mid);
        merge_sort(vec + mid, vec_size - mid);
        merge(vec, vec_size);
    }
}

void sort(double array[], int array_size) {
    merge_sort(array, array_size);
}

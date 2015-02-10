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
#include <math.h>

#define PROP_OF_BUCKETS 0.8
#define MAX_ARRAY_SIZE  100000000

typedef struct _node {
    double data;
    struct _node *next;
} * Node;

typedef Node Bucket;

Bucket ArrayOfBuckets[MAX_ARRAY_SIZE];

Node gen_new_node(double data) {
    Node res;

    res = malloc(sizeof(*res));
    res->data = data;
    res->next = NULL;

    return res;
}

void insert_on_bucket(Bucket *bucket, double value) {
    Node new_node, xnode, tmp_node;

    new_node = gen_new_node(value);

    if (*bucket == NULL || (*bucket)->data > value) {
        new_node->next  = *bucket;
        *bucket         = new_node;
    }
    else {
        for (xnode = *bucket; xnode->next != NULL && xnode->next->data <= value; xnode = xnode->next);
        tmp_node       = xnode->next;
        xnode->next    = new_node;
        new_node->next = tmp_node;
    }
}

void bucketsort(double array[], int array_size) {
    int i, pos, nbuckets, bucket_index;
    double max, min, bucketize;
    Node   xnode, oldnode;

    nbuckets = ceil(PROP_OF_BUCKETS*array_size);
    /*buckets  = malloc(nbuckets*sizeof(*buckets));*/
    for (i = 0; i < nbuckets; i++)
        ArrayOfBuckets[i] = NULL;

    max = array[0];
    min = array[0];
    for (i = 0; i < array_size; i++) {
        max = array[i] > max ? array[i] : max;
        min = array[i] < min ? array[i] : min;
    }

    bucketize = nbuckets/(1.0 + max - min);

    for (i = 0; i < array_size; i++) {
        bucket_index = floor((array[i] - min)*bucketize);
        insert_on_bucket(&(ArrayOfBuckets[bucket_index]), array[i]);
    }

    pos = 0;
    for (i = 0; i < nbuckets; i++) {
        for (xnode = ArrayOfBuckets[i]; xnode != NULL; xnode = xnode->next) {
            array[pos++] = xnode->data;
        }
    }
    for (i = 0; i < nbuckets; i++) {
        oldnode = NULL;
        for (xnode = ArrayOfBuckets[i]; xnode != NULL; xnode = xnode->next) {
            if (oldnode != NULL)
                free(oldnode);
            oldnode = xnode;
        }
        if (oldnode != NULL)
            free(oldnode);
    }
}

void sort(double array[], int array_size) {
   bucketsort(array, array_size);
}

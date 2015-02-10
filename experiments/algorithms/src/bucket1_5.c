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

#define PROP_OF_BUCKETS 1.5

typedef struct _node {
    double data;
    struct _node *next;
} * Node;

typedef Node Bucket;

void insert_on_bucket(Bucket *bucket, Node node) {
    Node xnode, tmp_node;

    if (*bucket == NULL || (*bucket)->data > node->data) {
        node->next  = *bucket;
        *bucket     = node;
    }
    else {
        for (xnode = *bucket; xnode->next != NULL && xnode->next->data <= node->data; xnode = xnode->next);
        tmp_node    = xnode->next;
        xnode->next = node;
        node->next  = tmp_node;
    }
}

void bucketsort(double array[], int array_size) {
    int i, pos, nbuckets, bucket_index;
    double max, min, bucketize;
    Bucket *buckets;
    Node   xnode;
    struct _node *allnodes;

    nbuckets = ceil(PROP_OF_BUCKETS*array_size);
    buckets  = malloc(nbuckets*sizeof(*buckets));
    allnodes = malloc(array_size*sizeof(*allnodes));
    if (buckets == NULL || allnodes == NULL) {
        perror("[-] malloc error...\n");
        exit(-1);
    }

    for (i = 0; i < nbuckets; i++)
        buckets[i] = NULL;
    max = array[0];
    min = array[0];
    for (i = 0; i < array_size; i++) {
        max = array[i] > max ? array[i] : max;
        min = array[i] < min ? array[i] : min;
    }

    bucketize = nbuckets/(1.0 + max - min);

    for (i = 0; i < array_size; i++) {
        bucket_index = floor((array[i] - min)*bucketize);
        allnodes[i].data = array[i];
        insert_on_bucket(&(buckets[bucket_index]), &(allnodes[i]));
    }
    pos = 0;
    for (i = 0; i < nbuckets; i++) {
        for (xnode = buckets[i]; xnode != NULL; xnode = xnode->next) {
            array[pos++] = xnode->data;
        }
    }
    free(allnodes);
    free(buckets);
}

void sort(double array[], int array_size) {
   bucketsort(array, array_size);
}

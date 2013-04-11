//
//  vector-sort.c
//  cppobjs
//
//  Created by Maxthon Chan on 13-4-11.
//  Copyright (c) 2013年 myWorld Creations. All rights reserved.
//

#include <stdio.h>
#include <vector.h>

comparison_result int_compare(const int *i1, const int *i2)
{
    int a = *i1, b = *i2;
    if (a < b)
        return compare_ascending;
    else if (a > b)
        return compare_descending;
    else
        return compare_same;
}

int main(void)
{
    int ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int ints2[] = {1, 4, 2, 8, 5, 7, 3, 6, 9, 10};
    vector_t vec = vector_init(ints2, sizeof(int), 10);
    
    size_t size = 10;
    
    vector_sort(vec, (comparator_t)int_compare);
    
    if (memcmp(ints, vec -> data, size * sizeof(int)))
    {
        vector_fini(vec);
        return 5;
    }
    
    vector_fini(vec);
    return 0;
}
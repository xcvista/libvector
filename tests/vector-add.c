//
//  vector-add.c
//  cppobjs
//
//  Created by Maxthon Chan on 13-4-11.
//  Copyright (c) 2013年 myWorld Creations. All rights reserved.
//

#include <stdio.h>
#include <vector.h>

int main(void)
{
    vector_t vec = vector_init_empty(sizeof(int), 5);
    int ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = 10;
    
    for (int i = 0; i < size; i++)
    {
        vector_append(vec, &ints[i]);
    }
    
    if (memcmp(ints, vec -> data, size * sizeof(int)))
    {
        vector_fini(vec);
        return 5;
    }
    
    if (vector_count(vec) != size)
    {
        vector_fini(vec);
        return 5;
    }
    
    vector_fini(vec);
    return 0;
}
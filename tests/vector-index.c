//
//  vector-index.c
//  cppobjs
//
//  Created by Maxthon Chan on 13-4-11.
//  Copyright (c) 2013年 myWorld Creations. All rights reserved.
//

#include <stdio.h>
#include <vector.h>

int main(int argc, char **argv)
{
    int ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector_t vec = vector_init(ints, sizeof(int), 10);
    
    int *buf = vector_alloc_object(vec);
    
    for (size_t i = 0; i < vector_count(vec); i++)
    {
        assert(vector_objectat(vec, buf, i));
        
        if (*buf != i + 1)
        {
            if (argc > 1)
                printf("Expecting: %ld get: %d\n", i + 1, *buf);
            vector_fini(vec);
            return 5;
        }
    }
    
    for (size_t i = 0; i < vector_count(vec); i++)
    {
        *buf = (int)(i + 1);
        size_t r;
        
        if (i != (r = vector_indexof(vec, buf, vector_binary_compare())))
        {
            //if (argc > 1)
            {
                printf("*buf:%d i:%ld r:%ld ints[i]:%d\n", *buf, i, r, ints[i]);
            }
            vector_fini(vec);
            return 6;
        }
    }
    
    free(buf);
    
    vector_fini(vec);
    return 0;
}
//
//  vector-shrink.c
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
    
    size_t size = 5;
    
    while (vector_count(vec) > size)
    {
        vector_removeat(vec, size);
    }
    
    if (memcmp(ints, vec -> data, size * sizeof(int)))
    {
        vector_fini(vec);
        return 5;
    }
    
    if (vector_count(vec) != size)
    {
        vector_fini(vec);
        return 6;
    }
    
    vector_compact(vec);
    
    if (vec -> alloc_size != vec -> count * vec -> element_size)
    {
        vector_fini(vec);
        return 7;
    }
    
    vector_fini(vec);
    return 0;
}

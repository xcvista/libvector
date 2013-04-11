//
//  collector.c
//  cppobjs
//
//  Created by Maxthon Chan on 13-4-10.
//  Copyright (c) 2013年 myWorld Creations. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main(int argc, char **argv)
{
    int tests = 0, passes = 0, xpasses = 0, fails = 0, xfails = 0, skips = 0;
    clock_t runtime = 0;
    
    char *linebuf = malloc(BUFSIZ);
    
    assert(linebuf);
    
    printf("\nmyWorld simple C unit test kit 1.0\n\n");
    
    for (int i = 1; i < argc; i++)
    {
        printf("test %s ", argv[i]);
        for (int x = 0; x < 30 - strlen(argv[i]); x++)
            putchar('.');
        putchar(' ');
        fflush(stdout);
        snprintf(linebuf, BUFSIZ, "./%s", argv[i]);
        tests++;
        pid_t fpid = fork();
        if (!fpid)
        {
            char *buf2 = malloc(BUFSIZ);
            snprintf(buf2, BUFSIZ, "killall -KILL %s", argv[i]);
            sleep(1);
            system(buf2);
            exit(0);
        }
        clock_t stime = clock();
        int rv = system(linebuf);
        clock_t etime = clock();
        kill(fpid, SIGKILL);
        runtime += (etime - stime);
        printf("time: %.3lfms, ", (double)(etime - stime) / CLOCKS_PER_SEC * 1000.0);
        int status = rv % 256;
        rv /= 256;
        if (status)
        {
            printf("fail (%s%s)\n", strsignal(status), (status == SIGKILL) ? ", timeout?" : "");
        }
        else
        {
            switch (rv)
            {
                case 0:
                    passes++;
                    printf("pass\n");
                    break;
                case 1:
                    passes++;
                    xpasses++;
                    printf("pass (unexpected)");
                    fflush(stdout);
                    snprintf(linebuf, BUFSIZ, "./%s -v", argv[i]);
                    system(linebuf);
                case 2:
                    skips++;
                    printf("skip\n");
                    break;
                case 3:
                    fails++;
                    xfails++;
                    printf("fail (3: expected)\n");
                    break;
                default:
                    fails++;
                    printf("fail (%d)\n", rv);
                    if (status > 4)
                    {
                        fflush(stdout);
                        snprintf(linebuf, BUFSIZ, "./%s -v", argv[i]);
                        system(linebuf);
                    }
                    break;
            }
        }
    }
    
    free(linebuf);
    
    printf("tests:  %d\n"
           "passes: %d (%d unexpected)\n"
           "fails:  %d (%d expected)\n"
           "skips:  %d\n"
           "time:   %.3lfms\n\n",
           tests,
           passes, xpasses,
           fails, xfails,
           skips,
           (double)(runtime) / CLOCKS_PER_SEC * 1000.0);
    return EXIT_SUCCESS;
}
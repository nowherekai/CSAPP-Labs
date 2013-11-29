
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#define MAXLINE 1024*1024
int  main(int argc, char *argv[])
{
    int base = 16;
    char *endptr;
    long val;
    char str[3] = {0};
    char *buf = (char *) malloc(MAXLINE);

    errno = 0;    /* To distinguish success/failure after call */
    if (fgets(buf, MAXLINE - 1, stdin) != NULL)
    {
        int i;
        for (i = 0; i <= strlen(buf) - 1; i += 2)
        {
            memcpy((void *)str, (void *)&buf[i], 2);
            str[2] = '\0';
            val = strtol(str, &endptr, base);
            /* Check for various possible errors */

            if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
                perror("strtol");
                exit(EXIT_FAILURE);
            }

            if (endptr == str) {
                fprintf(stderr, "No digits were found\n");
                exit(EXIT_FAILURE);
            }

            /* If we got here, strtol() successfully parsed a number */
            /*printf("strtol() returned %ld\n", val);*/

            if (write(STDOUT_FILENO, &val, 1) != 1)
            {
                fprintf(stderr, "write error\n");
            }
            if (*endptr != '\0')        /* Not necessarily an error... */
                printf("Further characters after number: %s\n", endptr);
        }
    }
    exit(EXIT_SUCCESS);
}




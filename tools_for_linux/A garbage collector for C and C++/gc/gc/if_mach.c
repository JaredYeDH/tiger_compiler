/* Conditionally execute a command based on machine and OS from config.h */
/* Boehm, November 21, 1994 1:40 pm PST */
# include "config.h"
# include <stdio.h>

int main(argc, argv, envp)
int argc;
char ** argv;
char ** envp;
{
    if (argc < 4) goto Usage;
    if (strcmp(MACH_TYPE, argv[1]) != 0) return(0);
    if (strcmp(OS_TYPE, "") != 0 && strcmp(argv[2], "") != 0
        && strcmp(OS_TYPE, argv[2]) != 0) return(0);
    execvp(argv[3], argv+3);
    perror("Couldn't execute");
    
Usage:
    fprintf(stderr, "Usage: %s mach_type os_type command\n", argv[0]);
    fprintf(stderr, "Currently mach_type = %s, os_type = %s\n",
    	    MACH_TYPE, OS_TYPE);
    return(1);
}


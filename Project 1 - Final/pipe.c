#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int p[2];

    if (pipe(p) == -1)
    {
        perror("pipe call"); 
        exit(1);
    }

    switch (fork())
    {
    case -1:
        perror("fork call");     
        exit(2);
    case 0:     // if 0 then the child writes to pipe
        close(1);
        dup(p[1]);     
        close(p[0]);     
        close(p[1]);
        execl("./pre", "pre", (char *)0);    // call execl() to execute pre.c
        perror("execl() failed (pre.c)!");
        return(EXIT_FAILURE);
    default:     // next the parent reads from pipe
        {
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        execl("./sort", "sort", (char *)0);    // call execl() to execute sort.c
        return(EXIT_FAILURE);
        }
    }
    return(EXIT_FAILURE);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFER 160
#define TOKENS 100  //using tokens to "tokenize" the input strings
int exepipe(char **argv1, char **argv2)
{
    int fd[2];
    pipe(fd);
    int i;
    pid_t pid = fork();
    if (pid == -1)
    { //error
        printf("forking error!\n");
        return 1;
    }
    if (pid == 0)
    { // This will be the child
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execvp(argv2[0], argv2); // This runs the command
        return 0;
    }
    else
    { // This will be the parent
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execvp(argv1[0], argv1); // this runs the command
        return 0;
    }
};

int main(int argc, char **argv)
{
    char *delim = " \n";
    char *tok;
    char s[BUFFER];
    char *tokens[TOKENS];
    static const char prompt[] = "shhh> ";
    FILE *infile;
    int fd[2];
    //STRING FLAGS
    int in = 0;
    int out = 0;
    int pipe = 0;
    //int test = 0;
    infile = stdin;

    while (1)
    {
        in = out = pipe = 0; //resets variables each loop
        for (int i = 0; i < TOKENS; i++)
            tokens[i] = NULL;

        // prompt for input, if interactive input
        if (infile == stdin)
        {
            printf(prompt);
        }

        //tokenize the lines read

        // read input
        char *status = fgets(s, BUFFER - 1, infile);

        // exit if ^d or "exit" entered
        if (status == NULL || strcmp(s, "exit\n") == 0)
        {
            if (status == NULL && infile == stdin)
            {
                printf("\n");
            }
            exit(0);
        }

        // break input line into tokens
        char *rest = s;
        int i = 0;

        tok = strtok_r(rest, delim, &rest);

        while (tok != NULL && i < TOKENS)
        {
            tokens[i] = tok;
            //puts(&tok[i]);   ////////TESTING HERE////////
            if (strcmp(tok, "<") == 0)
            {
                in = i; //indicates that < has been detected
                i--;
            }
            else if (strcmp(tok, ">") == 0)
            {
                out = i; //indicates that > has been detected
                i--;
            }
            else if (strcmp(tok, "|") == 0)
            {
                pipe = i; //indicates that | has been detected
                i--;
            }
            i++;
            tok = strtok_r(NULL, delim, &rest);
        }
        tokens[i] = NULL;

        // do nothing if no tokens found in input
        if (i == 0)
        {
            continue;
        }
        //fork process
        pid_t cpid = fork(), cpidstatus; //fork and get pid
        if(cpid == -1)
            {
            fprintf(stderr, "fork failed\n");
            exit(1);
            }
        else if (cpid == 0)
        {
            //puts(tokens[in]);
            //puts(tokens[out]); THESE ARE FOR TESTING AND VERIFYING OUTPUT
            //puts(tokens[pipe]);

            if (in)
            {
                //puts(tokens[in]);
                //puts(tokens[pipe]);
                if ((fd[0] = open(tokens[in], O_RDONLY, 0)) == -1)
                {
                    perror(tokens[in]);
                    exit(EXIT_FAILURE);
                }
                dup2(fd[0], 0);
                close(fd[0]);
                tokens[in] = NULL;
            }
            if (out)
            {
                if ((fd[1] = open(tokens[out], O_WRONLY | O_CREAT | O_TRUNC | O_CREAT,
                                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
                {
                    perror(tokens[out]);
                    exit(EXIT_FAILURE);
                }
                dup2(fd[1], 1);
                close(fd[1]);
                tokens[out] = NULL;
            }
            if (pipe)
            {
                char *argv1[] = {tokens[0], NULL};
                char *argv2[] = {tokens[pipe], NULL};
                exepipe(argv1, argv2);
            }
            /*{ THIS IS AN OLD METHOD THAT WAS VERY BUGGY AND DID NOT WORK
                char *argv[] = {tokens[0], NULL};
                switch(fork())
                {
                case -1:
                    perror("Bad Fork Call");
                    exit(2);
                case 0:
                    //dup(fd[1]);
                    //close(fd[0]);
                    //puts(tokens[0]);
                    //close(fd[1]);
                    //puts("Pipe Initiated");
                    close(fd[1]);
                    dup2(fd[0], 0);
                    execvp(tokens[0], argv);
                default:
                    //puts("This worked!!!!!!");
                    argv[0] = tokens[1];
                    //puts(tokens[1]);
                    //dup(fd[0]);
                    //close(fd[0]);
                    //close(fd[1]);
                    //puts("This also worked");
                    close(fd[1]);
                    dup2(fd[1], 1);
                    execvp(tokens[1], argv); // call execl() to execute sort.c
                    return (EXIT_FAILURE);
                }
            }*/
            //puts(tokens[0]);
            //puts(tokens[1]);
            // child process: run the command indicated by tokens[0]
            execvp(tokens[0], tokens);
            /* if execvp returns than an error occurred */
            printf("shhh: %s: %s\n", tokens[0], strerror(errno));
        }
        else
        {
            // parent process: wait for child to terminate
            while (wait(&cpidstatus) != cpid)
            {
                continue;
            }
        }
    }
}
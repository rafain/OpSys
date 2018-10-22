
/*********************************************
Lab #: 7
Team #: 2 
Name1: Rafaín Rodríguez San Millán
ID1: A01372976
Name2: Lenin Silva Gutierrez
ID2: A01373214
Program Title:  Shell
Brief Description: This program emulates a working shell so you can execute commands and background process
Compilation command: gcc -o shell shell.c
Execution command: ./shell
*********************************************/


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */
#define BUUFER_SIZE 80  /*Max size of the commands*/
#define buffer "\nShell Command History: \n"

char history[10][BUUFER_SIZE]; /* Array to store the last 10 commands */
int count = 0; /* Counter for  the commands */

/*
 * setup() reads in the next command line, separating it into distinct tokens
 * using whitespace as delimiters. setup() sets the args parameter as a 
 * null-terminated string.
 */

/* Function to show last 10 commands */
void handle_SIGINT()
{
    if(count>0){
        printf("\nCommand History:\n");
        
        int i;
        int j = 0;
        int insC = count;
        
        for(i = 0; i<10; i++)
        {
            printf("%d ", insC); /* Prints the numer of command */
            while (history[i][j] != '\n' && history[i][j] != '\0')  /* Loops through all the command and prints until \n or \0 */
            {
                printf("%c", history[i][j]);
                j++;
            }
            printf("\n");
            j = 0;   /* Reset char counter*/
            insC--;
            if (insC <= 0){
                break; /* Exit if there are less tahn 10 commans */
            }
        }
        printf("\n");
    }
    else
        printf("No history recorded\n");
}


void setup(char inputBuffer[], char *args[],int *background)
{
    int length, /* # of characters in the command line */
        i,      /* loop index for accessing inputBuffer array */
        start,  /* index where beginning of next command parameter is */
        ct;     /* index of where to place the next parameter into args[] */
    
    ct = 0;
    
    /* read what the user enters on the command line */
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);  

    start = -1;
    if (length == -1)
        exit(0);            /* ^d was entered, end of user command stream */
    if (length < -1){
        perror("error reading the command");
        exit(-1);           /* terminate with error code of -1 */
    }

    /* examine every character in the inputBuffer */
    for (i=0;i<length;i++) { 
        switch (inputBuffer[i]){
        case ' ':
        case '\t' :               /* argument separators */
        if(start != -1){
                    args[ct] = &inputBuffer[start];    /* set up pointer */
            ct++;
        }
                inputBuffer[i] = '\0'; /* add a null char; make a C string */
        start = -1;
        break;

            case '\n':                 /* should be the final char examined */
        if (start != -1){
                    args[ct] = &inputBuffer[start];     
            ct++;
        }
                inputBuffer[i] = '\0';
                args[ct] = NULL; /* no more arguments to this command */
        break;

        default :             /* some other character */
        if (start == -1)
            start = i;
                if (inputBuffer[i] == '&'){
            *background  = 1;
                    inputBuffer[i] = '\0';
        }
    } 
     }    
     args[ct] = NULL; /* just in case the input line was > 80 */
    
    if(strcmp(args[0],"r") == 0) /* If the first command is r whe execute a previous command*/
    {
        int insC = count - atoi(args[1]); /* Get the difference between the number and the wanted execution */
        //printf("%s", history[insC]);
        if (insC < 10)    /* Verify you can only Call for last 10 commands*/
        {
            strcpy(inputBuffer, history[insC]);    /* Copy to the inputBuffer */
            char *x =  NULL;
            args[1] = x;
            

        }else{
            printf("You can only use the last 10 commands. \n");
        }
    }
    
    for(i = 9; i>0; i--) /* Move the elements of history one place up */
    {
        strcpy(history[i],history[i-1]);  /* Copying that elements one place up */
    }
    
    strcpy(history[0], inputBuffer);  /*Copying the new command at the beginning of the array*/
    count++;
} 

int main(void)
{
    struct sigaction handler;
    handler.sa_handler = handle_SIGINT;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGINT, &handler, NULL);
    
    
    char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
    int background;             /* equals 1 if a command is followed by '&' */
    char *args[MAX_LINE/+1];/* command line (of 80) has max of 40 arguments */
    

    while (1){            /* Program terminates normally inside setup */
        background = 0;
        //showHis();
        printf("COMMAND->");
        fflush(stdout);
        setup(inputBuffer,args,&background);       /* get next command */
        
        int pid;
        pid = fork();    /* Generates the child process that will execute the commands*/
        if (pid == 0){
            execvp(args[0], args);   /* The child recieves the arguments and execute them */
            exit(0);
        }else{
            if (background == 0){
                wait(&pid);         /* If background is 0 we have to wait for child to finish */
            }
    }

    /* the steps ar
     (1) fork a child process using fork()
     (2) the child process will invoke execvp()
     (3) if background == 0, the parent will wait, 
        otherwise returns to the setup() function. */
    }
}

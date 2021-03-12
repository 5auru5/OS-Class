#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define BUFSIZE 512 not needed, thought I would have to use it but i didn't
struct student{
     char name[20];
     float gpa;
};

int main(int argc, char* argv[]){
   setbuf(stdout, NULL); //fixes some buffering issues when calling this in pipe.c
   FILE *inputfile;
   struct student students[20];
   int i;
   char *line = NULL;
   size_t len = 0;
   int count = 0;
   if (argc==1)  //given no arguments, you will have to enter names by hand
   {
      //printf("No arguments have been entered! Switching to Manual Entry Mode\n");
      //printf("Enter name and gpa scores to stop press Ctrl+D :\n");
      for(i = 0; i<20; i++){
         if (getline(&line, &len, stdin) != -1){
            sscanf(line,"%s %f",students[i].name,&students[i].gpa);
            count++;       
         }
         else {
            break;
         }
     
      }
   }
   if (argc == 2)  //given 1 argument (a text file) you will be able to inport names. 
   {
      // printf("File Given! Switching to Automated Entry Mode\n");
      char *valid = "txt";
      char *ext = strrchr(argv[1], '.');
      int isValid = strcmp(ext+1,valid);
      // DEBUG printf("%d\n", isValid);  //shows compare value
      // DEBUG printf("%s\n", ext +1); //prints out file ext
      if (isValid != 0) {  //checks the extension type
        // printf("ERROR: Please use a valid extension (.txt) for your file\n");
        exit(0);
      }
      if (isValid == 0) {
         inputfile = fopen(argv[1], "r");  //opens file
          // printf("Correct file extension given!(%s)\n", ext + 1); this messes with the buffer :(
         for(i = 0; i<20; i++){
            fscanf(inputfile, "%s %f", students[i].name,&students[i].gpa);  //gets input data and stores to array
            count++;
         }
      fclose(inputfile);
      }
   }
   //fflush(stdout); //testing to see if flushing the buffer helps here
   for (i = 0; i < count; i++) {
		if (students[i].gpa >= 3.0) {
			printf("%s\n",students[i].name);
		}
}
}
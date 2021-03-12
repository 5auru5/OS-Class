#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct student{  //Student storage
     char name[20];
};

int main(int argc, char* argv[]){

   struct student students[20]; //storeing students
   int i,j;  //loop counters for sorting
   char *line = NULL;
   size_t len = 0;
   int count = 0;
   struct student temp_students;  //temp student struct for sotring student during sorting 
if (argc==1)  //given no arguments, you will have to enter names by hand
   {
   // printf("Enter names of students to stop press Ctrl+D :\n");
   for(i = 0; i<20; i++){
      if (getline(&line, &len, stdin) != -1){ 
         sscanf(line,"%s",students[i].name); //get name of students. 
         count++;       
      }
      else {
         break;
      }
     
   }
}
if (argc == 2)  //given 1 argument (a text file) you will be able to inport names. 
{ 
    for(i = 0; i<20; i++){
    if (getline(&line, &len, stdin) != -1){ 
         sscanf(line,"%s",students[i].name); //get name of students. 
    count++;    
        }
    }
}
   for (i = 0; i<count; i++){  //standard sorting functio
       for(j=i; j<count; j++){ //this should reorder the orginal array 
           if (strcmp(students[i].name,students[j].name) > 0){
               strcpy(temp_students.name ,students[i].name);
               strcpy(students[i].name,students[j].name);
               strcpy(students[j].name,temp_students.name);

           }
       }
      
   }
   for (i = 0; i<count; i++){  //print out sorted student names
       printf("%s\n",students[i].name);
   }
   
return 0;
}

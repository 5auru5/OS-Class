 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>

 #define ARGUMENTS 5


 int main(int argc,char *argv[])
 {
 pid_t child_pid[ARGUMENTS];
 int status[ARGUMENTS];
 int i;
printf("%s\n", "============Here is the OverView Status of the Commands you entered=============");
switch(fork())
{
  case 0:
  for(i=1;i<argc;i++)  //runs through each arg
  {
 child_pid[i]=vfork();
 switch(child_pid[i])  //gets pid status
 {
   case -1:  //if child was not created
      printf("Error: Child not created!\n");
      abort();
      break;
   case 0: 
         if(argv[i]==NULL)
         break;
     else
     status[i]=execl(argv[i],argv[i],(char*)NULL);
     if(status[i]==-1)
         exit(-1);
     break;
   default :  //printing funciton
      printf("command : %s \n pid : %d\n status=%d\n",argv[i],child_pid[i],status[i]);  //prints out names and pids
      break;
   }
  }
 }
 }
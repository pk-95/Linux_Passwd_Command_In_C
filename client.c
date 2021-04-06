 #include<stdio.h>
 #include<string.h>
 #include<conio.h>
 #include <stdlib.h>
 #include "server.h"
 #define BUFFER_SIZE 1000

char oldWord[100], newWord[100];
char buffer[BUFFER_SIZE];

int main()
 {
 	printf("****Implementation of 'passwd' Linux command. Enter 'passwd' followed by user name to continue****\n\n");
 	char c[30];
 	gets(c);
 	char* command = strtok(c," "); //Extracting command
 	char* user=strtok(NULL," "); //Extracting user 
 	int check=strcmp(c,"passwd");
 	if(check!=0)
 	{
	 printf("\nIncorrect command/syntax. Program terminated.");
 	 return 0;
	 }
	FILE *pwd=fopen("passwd.txt","r");
	char line[256];
	int flag1=0;
	while (fgets(line, sizeof(line),pwd))  //Checking if user exists
	{
		char* name=strtok(line,":");
		if(strcmp(name,user)==0){
			flag1=1;
			break;
		}
	}
	if(flag1==0){
		printf("\nUser not found. Program terminated. (Refer User List file to see existing users)");
		return 0;
	}
	fclose(pwd);
	printf("Changing password for %s\n",user);
	printf("Current password:");
	char* cp = getpass();
	FILE *shad=fopen("shadow.txt","r");
	char* ep;
	while (fgets(line, sizeof(line),shad)) //extracting current password
	{
		ep=strtok(line,":");
		if(strcmp(ep,user)==0){
			ep=strtok(NULL,":");
			break;
		}
	}
	fclose(shad);
	if(strcmp(cp,decrypt(ep,strlen(ep)))==0){  //comparing if correct password is entered
		printf("\nEnter new password:");
		char* np=getpass(); //np=new password
		printf("\nRe-enter new password:");
		char* rnp=getpass(); //rnp= re entered new password
		if(strcmp(np,rnp)==0){ //Checking if entered and re entered password is the same
			char* nep=encrypt(np,strlen(np)); //nep=new encrypted password
			FILE *fTemp=fopen("replace.txt","w");
			FILE *shad=fopen("shadow.txt","r");
			    while ((fgets(buffer, BUFFER_SIZE, shad)) != NULL)  //storing contents of shadow into a buffer
    			{
             		replaceAll(buffer, ep, nep);        //replacing password in buffer
        			fputs(buffer, fTemp);   //tranferring contents of buffer to temp file
    			}
			fclose(shad);
    		fclose(fTemp);
    		remove("shadow.txt");
    		rename("replace.txt", "shadow.txt");
    		printf("\n passwd: password successfully updated");  //replacing shadow with temp file after having updated password
			
		}
		else{
			printf("\nRe-entered password does not match. Program Terminated.");
		}
	}
	else{
		printf("\nIncorrect password. Prgram Terminated.");
	}
	
	
 	return 0;
 }

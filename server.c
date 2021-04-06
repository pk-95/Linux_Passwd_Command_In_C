#include<stdio.h>
 #include<string.h>
 #include<conio.h>
 #include <stdlib.h>
 #define BUFFER_SIZE 1000
 #include "server.h"
char x[25]=""; 
char y[25]="";
char str[20]=""; 
char oldWord[100], newWord[100];
char buffer[BUFFER_SIZE];


char* encrypt(char* a, int n) //function to encrypt password
 {
 	int i=0;char c;int e;
	strcpy(x,"");
 	for(i=0;i<n;i=i+1)
 	{
 	 	
	 c=a[i];
	 e=(int)c;
	 e=e+4; //updates ASCII by 4 of each character
	 c=(char)e;
	 strncat(x,&c,1);
	
	 
	 }
	 
	 return(x);
 }
 
 char* decrypt(char* b, int n) //function to decrypt password
 {
 	int i=0;char c;int e;
	strcpy(y,"");
 	for(i=0;i<n;i=i+1)
 	{
 	 	
	 c=b[i];
	 e=(int)c;
	 e=e-4; //Decreases ASCII by 4 to decrypt
	 c=(char)e;
	 strncat(y,&c,1);
	
	 
	 }
	 
	 return(y);
 }
 
 char* getpass(){  //used to input password such that it is not visible on user screen
 	strcpy(str,"");
	char c;
	int i=0;
	while (i<=20)
	{
    	str[i]=getch();
    	c=str[i];
    	if(c==13) break;
    	else printf("*"); //instead, asterisks are shown for security
    	i++;
	}
	str[i]='\0';
	return(str);
	
 }
 
 
 void replaceAll(char *str, const char *oldWord, const char *newWord) //function to replace old password with new password
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);
    while ((pos = strstr(str, oldWord)) != NULL) //finding old password in buffer
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord); //replacing it with new password
        strcat(str, temp + index + owlen);
    }
}
 

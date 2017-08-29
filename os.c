#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<dirent.h>
#include<string.h>
char input[1005][1005];
char inp[10005];
char cwd[1024];
char pwd[1024];
char *input2[1024];
int cnt=0,len=0;
#include "echo.h"
#include "pinfo.h"
#include "cd.h"
#include "ls.h"
#include "execute.h"



int getwords(char *inpt){
    cnt=0;
    char *ch = strtok (inpt,"\" \t");
    while (ch != NULL){
        //printf("%s",input2[cnt]);
        strcpy(input[cnt++],ch);
        ch = strtok (NULL, " \"\t");
    }
    return cnt;
}


void verify_cmd(char *inpt){
    cnt = getwords(inpt);
    if (strcmp(input[0], "cd")==0){
        implement_cd();
    }
    else if (strcmp(input[0],"echo")==0) 
        echo();
    else if (strcmp(input[0],"pwd")==0){
        char temp[1023] = {'\0'};
        getcwd(temp,sizeof (temp));
        printf("%s\n",temp);
    }
    else if (strcmp(input[0],"ls")==0){
        ls();
    }
    else if(strcmp(input[0],"pinfo")==0){
        if(strlen(input[1])==0){
            pin(1);
        }
        else{
            pin(0);
        }
    }
    else{
        execute(cnt);
    }
}

int main (){
    char hostname[1024];
    hostname[1023] = '\0';
    cwd[1023] = '\0';
    gethostname(hostname, 1023);//sys_name
    struct passwd *hello;
    hello=getpwuid(getuid());//user_name
    getcwd(cwd,sizeof (cwd));
    int cwdlen=strlen(cwd);
    int k=20;
    while(1){
        pwd[1023] = '\0';
        getcwd(pwd,sizeof (pwd));
        int pwdlen=strlen(pwd);
        if (pwdlen>=cwdlen)
            printf("<%s@%s:~%s>$ ",hello->pw_name,hostname,pwd+cwdlen);
        else
            printf("<%s@%s:%s>$ ",hello->pw_name,hostname,pwd);
        memset(inp,0,sizeof(inp));
        char x=getchar();
        if (x=='\n')
            scanf("%[^\n]s",inp);
        else{
            inp[0]=x;
            scanf("%[^\n]s",inp+1);
        }
        if (inp[strlen(inp)-1]!=';') inp[strlen(inp)]=';';
        cnt=0;
        char *string=inp;
        char *cmd = strchr(string,';');
        while (cmd != NULL){
        memset(input,0,sizeof(input));
            *cmd++='\0';
            char *temp=string;
            verify_cmd(temp);
            string=cmd;
            cmd = strchr (string,';');
        }
    }
    return 0;
}

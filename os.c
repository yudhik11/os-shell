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
#include<fcntl.h>
#include<math.h>
char input[1005][1005];
char inp[10005];
char cwd[1024];
char pwd[1024];
char *input2[1024];
char paths[1023]={'\0'};
int cnt=0,len=0;
#include "echo.h"
#include "pinfo.h"
#include "cd.h"
#include "execute.h"
#include "ls.h"
#include "verifycmd.h"
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
#define KBLU  "\x1B[34m"

int calculte(char *arr,int l){
    int i,val=0,count=0,pwr=1;;
    for (i = l-2; i>=0; i--)
    {
        val+=(arr[i]-'0')*pwr;
		pwr*=10;
    }
    return val;
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
    int k=20,l;
    int fd = creat("pid", 0600);
    close(fd);
    strcpy (paths,cwd);
    strcat(paths,"/pid");
    while(1){
        FILE *fp = NULL;
        fp = fopen(paths,"r+");
        while(1){
            char st[1024];
            fgets(st,200,fp);
            if(feof(fp)) break;
           // printf("%s",st);
            if(st[0]=='z') continue;
            int l = strlen(st);
            int val = calculte(st,l);
            if(kill(val,0)!=0){
                printf("[%d] has exited\n",val);
                fseek(fp,-l,SEEK_CUR);
                fputc('z',fp);
                fseek(fp,(l-1),SEEK_CUR);
            }
        }
        fclose(fp);
        pwd[1023] = '\0';
        getcwd(pwd,sizeof (pwd));
        if (strstr(pwd,cwd)!=NULL)            
            printf("%s<%s@%s:%s~%s>%s$ ",KGRN,hello->pw_name,hostname,KBLU,pwd+cwdlen,KWHT);
        else
            printf("%s<%s@%s:%s%s>%s$ ",KGRN,hello->pw_name,hostname,KBLU,pwd,KWHT);
        memset(inp,0,sizeof(inp));
        char x=getchar();
        if (x=='\n')
            scanf("%[^\n]s",inp);
        else{
            inp[0]=x;
            scanf("%[^\n]s",inp+1);
        }
//		printf("string:\"%s\"",inp);
        if (strlen(inp)<=0) continue;
	   	if ( inp[strlen(inp)-1]!=';') inp[strlen(inp)]=';';
        cnt=0;
        char *string=inp;
        char *cmd = strchr(string,';');
        while (cmd != NULL){
        	memset(input,0,sizeof(input));
            *cmd++='\0';
            char *temp=string;
			if (strlen(temp)==0) continue;
            verify_cmd(temp);
            string=cmd;
            cmd = strchr (string,';');
        }
    }
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
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
#include<setjmp.h>
#include<signal.h>
char input[1005][1005];
char inp[10005];
char cwd[1024];
char pwd[1024];
char *input2[1024];
char paths[1023]={'\0'};
int cnt=0,len=0;
int in;
int out;
#include "echo.h"
#include "pinfo.h"
#include "cd.h"
//#include "redirection.h"
#include "execute.h"
#include "ls.h"
#include "jobs.h"
#include "verifycmd.h"
#include "pipeslin.h"
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
#define KBLU  "\x1B[34m"
sigjmp_buf ctrlc_buf;
void handle_signals(int signo)
{
    if (signo == SIGINT)
    {
        printf("\n");
        //printf("You pressed Ctrl+C\n");
        siglongjmp(ctrlc_buf, 1);
    }
}
int calculte(char *arr,int l){
    int i,val=0,count=0,pwr=1;;
    for (i = l-2; i>=0; i--)
    {
        val+=(arr[i]-'0')*pwr;
        pwr*=10;
    }
    return val;
}
void sighandler(int sig_num)
{
    // Reset handler to catch SIGTSTP next time
    signal(SIGTSTP, sighandler);
    printf("\n");
    fflush(stdout);
}
void child_handler(int sig)
{
        pid_t pid;
        int status;
        while((pid = waitpid(-1, &status, WNOHANG)) > 0);
}
int main (){
    in = dup(0);
    out = dup(1);
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
    
    if (signal(SIGINT, handle_signals) == SIG_ERR) {
        printf("failed to register interrupts with kernel\n");
    }
    while ( sigsetjmp( ctrlc_buf, 1 ) != 0 );
    signal(SIGTSTP, sighandler);
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = child_handler;
    sigaction(SIGCHLD, &sa, NULL);
    
    
    while(1){
        FILE *fp = NULL;
        fp = fopen(paths,"r+");
        while(1){
            char st[1024];
            fgets(st,200,fp);
            if(feof(fp)) break;
            // printf("%s",st);
            int l = strlen(st+1);
            char store[1024] = {'\0'};
            for(int i=1;st[i]!=' ';i++){
                store[i-1] = st[i];
            }
            int val = calculte(store,strlen(store)+1);
            if(kill(val,0)!=0){
                printf("[%s] has exited\n",store);
                fseek(fp,-l-1,SEEK_CUR);
                fputc('0',fp);
                fseek(fp,(l),SEEK_CUR);
            }
        }
        fclose(fp);
        pwd[1023] = '\0';
        getcwd(pwd,sizeof (pwd));
        if (strstr(pwd,cwd)!=NULL)            
            fprintf(stderr,"%s<%s@%s:%s~%s>%s$ ",KGRN,hello->pw_name,hostname,KBLU,pwd+cwdlen,KWHT);
        else
            fprintf(stderr,"%s<%s@%s:%s%s>%s$ ",KGRN,hello->pw_name,hostname,KBLU,pwd,KWHT);
        memset(inp,0,sizeof(inp));
        char x=getchar();


        if (x==EOF){
            printf("\n");
            continue;
        }

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
        //		for(int i=0;i<1005;i++) input[i] = (char *)malloc(sizeof(char) * 1005);
        char *string=inp;
        //if(strstr(inp,"|")==NULL){
        char *cmd = strchr(string,';');
        while (cmd != NULL){
            memset(input,0,sizeof(input));
            *cmd++='\0';
            char *temp=string;
            if (strlen(temp)==0) continue;
            if(strstr(temp,"|")==NULL) verify_cmd(temp);
            else pipeLoop(temp);
            dup2(0,in);
            dup2(1,out);
            string=cmd;
            cmd = strchr (string,';');
        }
        //}
        //else pipeLoop(string);
    }
    return 0;
}

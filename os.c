#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<pwd.h>
#include<string.h>
char *input[10005];
int cnt=0;
void getwords(char inp[]){
    cnt=0;
    char * pch = strtok (inp,"\" ,.-");
    while (pch != NULL){
        input[cnt++]=pch;
        pch = strtok (NULL, " \",.-");
    }
}
void echo(){
        for (int i=1;i<cnt;i++) {
            if (input[i][0]=='$'){
                const char* s = getenv(input[i]+1);
                printf("%s\n",(s!=NULL)? s : "");
            }
            else
                printf("%s ",input[i]);
        }
}

int main (){
    char hostname[1024];
    hostname[1023] = '\0';
    char cwd[1024];
    cwd[1023] = '\0';
    gethostname(hostname, 1023);//sys_name
    struct passwd *hello;
    hello=getpwuid(getuid());//user_name
    getcwd(cwd,sizeof (cwd));
    int cwdlen=strlen(cwd);
    int k=2;
    for (int i=0;i<k;i++){
        char pwd[1024];
        pwd[1023] = '\0';
        getcwd(pwd,sizeof (pwd));
        int pwdlen=strlen(pwd);
        if (pwdlen>=cwdlen)
            printf("<%s@%s:~%s>$ ",hello->pw_name,hostname,pwd+cwdlen);
        else
            printf("<%s@%s:%s>$ ",hello->pw_name,hostname,cwd+pwdlen);
        char inp[10005]={'\0'};
        if (i>0) getchar();
        scanf("%[^\n]s",inp);
        printf("%s\n",inp);
        getwords(inp);
       // if (strcmp(input[0],"echo")==0) 
            echo();
        printf("\n");

    }

    return 0;
}

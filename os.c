#include<stdio.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<pwd.h>
#include<string.h>
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
//        char inp[10005]={'\0'};
//        getchar();
//        scanf("%[^\n]s",inp);
//        printf("%s\n",inp);

    }

    return 0;
}

#include<stdio.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<pwd.h>
int main (){
    char hostname[1024];
    char cwd[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);//sys_name
    struct passwd *hello;
    hello=getpwuid(getuid());//user_name
    getcwd(cwd,sizeof (cwd));

    printf("<%s@%s:%s>\n",hello->pw_name,hostname,cwd);
    return 0;
}

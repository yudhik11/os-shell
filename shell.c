#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<pwd.h>
#include<string.h>
char input[1005][1005];
char inp[10005];
char inp2[10005];
char cwd[1024];
char pwd[1024];
int cnt=0;
void getwords(char inp[]){
    cnt=0;
    char * pch = strtok (inp,"\" \t");
    while (pch != NULL){
        strcpy(input[cnt++],pch);
        pch = strtok (NULL, " \"\t");
    }
}
int implement_cd(){
 	char ch[100]={'\0'};
	strcpy(ch,input[1]);
    char save[1024];
	save[1023] = '\0';
   	if(strlen(ch)==0){
		chdir(cwd);
		return 0;
	}
	if(ch[0]=='~'){
		strcpy(save,cwd);
		strcat(save,"/");
		strcat(save,ch+1);
		chdir(save);
		return 0;
	}
    getcwd(save,sizeof(save));
    if(ch[0]!='/'){
        strcat(save,"/");
        strcat(save,ch);
        chdir(save);
    }
    else{
        chdir(ch);
    }
}
void echo(){
    for (int i=1;i<cnt;i++) {
        if (input[i][0]=='$'){
            const char* s = getenv(input[i]+1);
            printf("%s",(s!=NULL)? s : "");
        }
        else
            printf("%s ",input[i]);
    }
}
void verify_cmd(){
    getwords(inp);
    if (strcmp(input[0], "cd")==0){
        implement_cd();
    }
    if (strcmp(input[0],"echo")==0) 
        echo();
    if (strcmp(input[0],"pwd")==0){
        char temp[1023] = {'\0'};
        getcwd(temp,sizeof (temp));
        printf("%s\n",temp);
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
    for (int i=0;i<k;i++){
    memset(input,0,sizeof(input));
        pwd[1023] = '\0';
        getcwd(pwd,sizeof (pwd));
        int pwdlen=strlen(pwd);
        if (pwdlen>=cwdlen)
            printf("<%s@%s:~%s>$ ",hello->pw_name,hostname,pwd+cwdlen);
        else
            printf("<%s@%s:%s>$ ",hello->pw_name,hostname,pwd);
        memset(inp,0,sizeof(inp));
        memset(inp2,0,sizeof(inp2));
        if (i>0) getchar();
        scanf("%[^\n]s",inp);
        verify_cmd();
    }
    return 0;
}

#include<stdio.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<pwd.h>
#include<string.h>

char cwd[1024];
char pwd[1024];
int implement_cd(char *ch){
	ch = strtok(NULL," \t");
	if(ch==NULL){
		chdir(cwd);
		return 0;
	}
	char save[1024];
	save[1023]= '\0';
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
/*
   if(ch==NULL) chdir(cwd);
   if(strcmp(ch,".")==0) return 0;
   if(strcmp(ch,"..")==0){
   getcwd(pwd,sizeof(pwd));
   }
   char chanwd[1024];
   while(ch!=NULL){
   */		

int main (){
	char hostname[1024];
	hostname[1023] = '\0';
	cwd[1023] = '\0';
	gethostname(hostname, 1023);//sys_name
	struct passwd *hello;
	hello=getpwuid(getuid());//user_name
	getcwd(cwd,sizeof (cwd));
	int cwdlen=strlen(cwd);
	int k=10;
	for (int i=0;i<k;i++){
		pwd[1023] = '\0';
		getcwd(pwd,sizeof (pwd));
		int pwdlen=strlen(pwd);
		if (pwdlen>=cwdlen)
			printf("<%s@%s:~%s>$ ",hello->pw_name,hostname,pwd+cwdlen);
		else
			printf("<%s@%s:%s>$ ",hello->pw_name,hostname,pwd);
		char inp[10005]={'\0'};
		if (i>0) getchar();
		scanf("%[^\n]s",inp);
		char *ch = strtok(inp, " \t");
		if(strcmp(ch, "cd")==0){
			implement_cd(ch);
		}
	}

	return 0;
}

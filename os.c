#include "header.h"

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
	while(1){
		FILE *fp = NULL;
		fp = fopen(paths,"r+");
		if(fp==NULL){
			perror("does not exist");
		}
		while(1){
			char st[1024],stor[1024];
			fgets(st,200,fp);
			if(feof(fp)) break;
			if(st[0]=='0') continue;
			int l = strlen(st+1);
			char store[1024] = {'\0'};
			for(int i=1;st[i]!=' ';i++){
				store[i-1] = st[i];
			}
			int val = calculater(store,strlen(store)+1);
			char save[1024] = "/proc/";
			strcat(save,store);
			strcat(save,"/status");
			FILE *fil = fopen(save,"r");
			if(st[0]=='0' || fil==NULL){
				fclose(fil);
				continue;
			}
			else if(fil==NULL){
				fprintf(stderr,"[%s] has exited\n",store);
				fseek(fp,-l-1,SEEK_CUR);
				fputc('0',fp);
				fseek(fp,(l),SEEK_CUR);
				fclose(fil);
			}
			else{
				while(1){
					fgets(stor,200,fil);
					if(feof(fil)) break;
					if(strstr(stor,"State") != NULL){
						if(strstr(stor,"Z")){
							fprintf(stderr,"[%s] has exited\n",store);
							fseek(fp,-l-1,SEEK_CUR);
							fputc('0',fp);
							fseek(fp,(l),SEEK_CUR);
							break;
						}
					}
				}
				fclose(fil);
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

#ifndef za
#define za  

int implement_cd(){
    char ch[100]={'\0'};
    strcpy(ch,input[1]);
    char save[1024];
    save[1023] = '\0';
    if(strlen(ch)==0){
		int val = chdir(cwd);
		if(val < 0){
			perror("cd failed");
		}
        return 0;
    }
    if(ch[0]=='~'){
        strcpy(save,cwd);
        strcat(save,"/");
        strcat(save,ch+1);
        int val = chdir(save);
		if(val < 0){
			perror("cd failed");
		}
        return 0;
    }
    getcwd(save,sizeof(save));
    if(ch[0]!='/'){
        strcat(save,"/");
        strcat(save,ch);
		int val = chdir(save);
			if(val < 0){
				perror("cd failed");
			}
    }
    else{
		int val = chdir(ch);
		if(val < 0){
			perror("cd failed");
		}
    }
}
#endif

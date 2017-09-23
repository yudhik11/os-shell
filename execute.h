#ifndef ba
#define ba  

void background_proc(){
    int pid = fork();
    if(pid==0){
        int p = fork();
        if(p==0){
            fprintf(stderr,"[%d]\n",getpid());
            int fd = open(paths,O_RDWR | O_APPEND);
            char save[1024] = {'\0'};
            int i=0;
			char store[1024] = {'\0'};
			while(input2[i]!=NULL){
				strcat(store,input2[i++]);
				strcat(store," ");
			}
			sprintf(save,"1%d %s[%d]\n",getpid(),store,getpid());
            write(fd,save,strlen(save));
            close(fd);
			int val = execvp(input2[0],input2);
			if(val < 0){
				perror("Execution failed");
			}
        }
		else exit(0);
	}
    else{
        wait(NULL);
    }
}

void foreground_proc(){
    int pid = fork();
    if(pid==0){
        int val = execvp(input2[0],input2);
            if(val < 0){
                perror("Execution failed");
            }
    }
   else{
        wait(NULL);
    }
}

void execute(int len){
    for(int i=0;i<len;i++){
        if(input[i][0]=='&'){
            input2[i] = NULL;
            background_proc();
            //cont=0;
            return;
        }
        else{
            input2[i] = input[i];
        }
    }
    input2[len] = NULL;
    foreground_proc();
}
#endif

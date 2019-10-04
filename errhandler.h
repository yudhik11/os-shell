void handle_signals(int signo)
{
	if (signo == SIGINT)
	{   
		printf("\n");
		//printf("You pressed Ctrl+C\n");
		siglongjmp(ctrlc_buf, 1); 
	}   
}
void sighandler(int sig_num)
{
	// Reset handler to catch SIGTSTP next time
	if (pname!=0){
		kill(pname,SIGTSTP);
        int fd = open(paths,O_RDWR | O_APPEND);
        char save[1024] = {'\0'};
        int i=0;
        char store[1024] = {'\0'};
        while(input2[i]!=NULL){
            strcat(store,input2[i++]);
            strcat(store," ");
        }
        sprintf(save,"1%d %s[%d]\n",pname,store,pname);
        write(fd,save,strlen(save));
        close(fd);
		pname=0;
		kill(pname,SIGCONT);
	}
}
void child_handler(int sig)
{
	pid_t pid;
	int status;
	while((pid = waitpid(-1, &status, WNOHANG)) > 0); 
}

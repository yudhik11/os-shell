int pipeLoop(char *inpt) {
    cnt = getwords(inpt);
    char *comms[1024];
    int cntr=0;
    for(int i=0;i<1024;i++){
        comms[i] = (char *)malloc(sizeof(char) * 1024);
        memset(comms[i],0,sizeof(comms[i]));
    }
    for(int i=0;i<cnt;i++){
        if(input[i][0]!='|'){
            char buff[105]={'\0'};
            sprintf(buff," %s",input[i]);
            strcat(comms[cntr],buff);
        }
        else{
            cntr++;
        }
    }
    int status; 
    int statusArr[cntr+1];
    int pipeFdSize = (cntr) * 2; 
    int pipes[pipeFdSize];

    pid_t waitresult;
    pid_t forkArr[cntr+1];
    int return_value = -1;

    for (int i = 0; i < pipeFdSize; i += 2)  pipe(pipes + i);
    
    for (int i = 0; i < cntr+1; i++) {
        if ((forkArr[i] = fork()) == -1) {
            perror("Pipes fork error ");
            exit(-1);
        }
        if (forkArr[i] == 0) {
            if (i == 0) {
                dup2(pipes[1], 1);
            } else if (i == cntr) {
                dup2(pipes[2 * cntr - 2], 0);
            } else {
                dup2(pipes[2 * (i - 1)], 0);
                dup2(pipes[(2 * i) + 1], 1);
            }
            for(int i=0;i<pipeFdSize;i++) close(pipes[i]); 
            verify_cmd(comms[i]);
            exit(return_value);
        }
    }
    for(int i=0;i<pipeFdSize;i++) close(pipes[i]); 
    for (int i = 0; i < cntr+1; i++) {
        waitresult = waitpid(forkArr[i], &status, WUNTRACED);
        statusArr[i] = status;
    }
    if (statusArr[cntr] == 0) {
        return_value = 0;
    }
    return 0;
}

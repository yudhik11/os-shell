// Handles piping.
// The input is 2d vector of commands 
// i.e : [ls],[cat],[grep,shell.cpp],[cut,-d,1-2]
int pipeLoop(char *inpt) {
  // Need this for recording the status of each child.
  cnt = getwords(inpt);
  char *comms[1024];
  int counter=0;
  for(int i=0;i<1024;i++){
	  comms[i] = (char *)malloc(sizeof(char) * 1024);
  	  memset(comms[i],0,sizeof(comms[i]));
  }
  for(int i=0;i<cnt;i++){
	  if(input[i][0]!='|'){
		  char buff[105]={'\0'};
		  sprintf(buff," %s",input[i]);
		  strcat(comms[counter],buff);
	  }
	  else{
//		  fprintf(stderr,"%s\n",comms[counter]);
		  counter++;
	  }
  }
//  fprintf(stderr,"%s \n",comms[counter]);		  
  int status; 
  int statusArr[counter+1];
 
  // Initialize the pipes.
  // File descriptor size should be (n-1)*2 because there are 2 ends
  // in each pipe (write(1) and read(0)). i.e A  B  C
  // STD_IN : 0, STD_OUT : 1, STD_ERR : 2
  int pipeFdSize = (counter) * 2; 
  int pipes[pipeFdSize];
 
  // Wait for each child.
  pid_t waitresult;
 
  //Initilize the fork() array depending on the size of the commands.
  pid_t forkArr[counter+1];
 
  // 0 : success , -1 : error 
  int return_value = -1;
 
  // Create the pipes. Notice here that we are offsetting by 2. 
  // because a pipe has two ends which requires two slots in the array.
  for (int i = 0; i < pipeFdSize; i += 2) {
    pipe(pipes + i);
  }
 
  // Now the annoying part.
  for (int i = 0; i < counter+1; i++) {
    // Call fork() and check error.
    if ((forkArr[i] = fork()) == -1) {
      perror("Pipes fork error ");
      exit(-1);
    }
 
    // Child process should execute the commands. Before we do that
    // we have to put a pipe between the parent process and the
    // child process. We will use dup2 because it allows us to set
    // STD_OUT and STD_IN for a specified process.
    if (forkArr[i] == 0) {
      // We need to take care of the special cases : first pipe
      // and last pipe. The pipes in the middle have same behavior.
      // i.e : ABCDE
      if (i == 0) {
        // First pipe. Duplicate a file descriptor to STD_OUT.
        // A  B and A's out is set to the pipe's write.
        dup2(pipes[1], 1);
      } else if (i == counter) {
        // Last index. AB...D and the last's command needs to read
        // from the pipe. Thus, we set the last pipe's read to STD_IN
        // from previous command.
        dup2(pipes[2 * counter - 2], 0);
      } else {
        // Middle pipes. A...C...E We want to read the STD_OUT from B
        // to the pipe before C and write STD_IN to the pipe for the next
        // command.
        dup2(pipes[2 * (i - 1)], 0);
        dup2(pipes[(2 * i) + 1], 1);
      }
      // Always make sure to close the pipes. So then, the parent knows if
      // the child has reached to the end of file.
  	  for(int i=0;i<pipeFdSize;i++) close(pipes[i]); 
      // Execute the command
      verify_cmd(comms[i]);
      exit(return_value);
    }
  }
 
  // This is the parent process.
  for(int i=0;i<pipeFdSize;i++) close(pipes[i]); 
  // Check the status of each child and wait for finishing the execution.
  for (int i = 0; i < counter+1; i++) {
    waitresult = waitpid(forkArr[i], &status, WUNTRACED);
    statusArr[i] = status;
  }
 
  // Last status should indicate the success of the piping.
  if (statusArr[counter] == 0) {
    return_value = 0;
  }
 
  return 0;
}


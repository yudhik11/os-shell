
#ifndef ajsi
#define ajsi
int getwords(char *inpt){
	cnt=0;
	char *ch = strtok (inpt,"\" \t");
	while (ch != NULL){
		//printf("%s",input2[cnt]);
		strcpy(input[cnt++],ch);
		ch = strtok (NULL, " \"\t");
	}
	return cnt;
}

void verify_cmd(char *inpt){
	cnt = getwords(inpt);
	int fd,i,pos1 =(-1),pos2=(-1);
	int fl = cnt;
	for(i=0;i<cnt;i++)
	{
		if(input[i][0] == '<')
		{
			fd=open(input[i+1], O_RDONLY);
			if(fd < 0)
			{
				perror("fd error");
				return ;
			}
			if(dup2(fd,0) == -1)
			{
				perror("dup error");
				return ;
			}
			close(fd);
			pos1 = i;
			if(pos1 < fl) fl = pos1;
		}
		else if(input[i][0] == '>')
		{
			if(input[i][1] == '>') fd=open(input[i+1],O_CREAT | O_WRONLY |O_APPEND, 0666);
			else{
				fd=open(input[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			}
			if(fd < 0)
			{
				perror("fd error");
				return ;
			}
			if(dup2(fd,1) == -1)
			{
				perror("dup error");
				return ;
			}
			close(fd);
			pos2 = i;
			if(pos2 < fl) fl = pos2;
		}
	}
	if(pos1 != -1) memset(input[pos1],0,sizeof(input[pos1]));
	if(pos2 != -1) memset(input[pos2],0,sizeof(input[pos2]));
	cnt = fl;
	if (strcmp(input[0], "cd")==0){
		implement_cd();
	}
	else if (strcmp(input[0],"c")==0) {
        strcpy(input[0],"clear");execute(cnt);
    }
	else if (strcmp(input[0],"echo")==0)
		echo();
	else if (strcmp(input[0],"pwd")==0){
		char temp[1023] = {'\0'};
		getcwd(temp,sizeof (temp));
		printf("%s\n",temp);
	}
	else if (strcmp(input[0],"ls")==0){
		ls();
	}
	else if(strcmp(input[0],"pinfo")==0){
		if(strlen(input[1])==0){
			pin(1);
		}
		else{
			pin(0);
		}
	}
	else if(strcmp(input[0],"quit")==0){
		exit(0);
	}
	else if(strcmp(input[0],"setenv")==0){
		if(cnt!=2 && cnt!=3){
			perror("input error");
			return;
		}
		else setenv(input[1],input[2],1);
	}
	else if(strcmp(input[0],"unsetenv")==0){
			if(cnt!=2){
				perror("input error");
				return;
			}
			else unsetenv(input[1]);
	}
	else if(strcmp(input[0],"jobs")==0){
		jobs();
	}
	else if(strcmp(input[0],"overkill")==0){
		overkill();
	}
	else if(strcmp(input[0],"kjob")==0){
		if(cnt!=3){
			perror("invalid input format");
			return;
		}
		kjob();
	}
	else if(strcmp(input[0],"fg")==0){
		fg();
	}
	else {
		execute(cnt);
	}
	dup2(in,0);
	dup2(out,1);
}
#endif

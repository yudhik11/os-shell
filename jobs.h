#ifndef gh
#define gh

int calculater(char *arr,int l){
	int i,val=0,count=0,pwr=1;;
	for (i = l-2; i>=0; i--)
	{
		val+=(arr[i]-'0')*pwr;
		pwr*=10;
	}
	return val;
}
void jobs(){
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	int counter = 1;
	while(1){
		char st[1024];
		fgets(st,200,fp);
		if(feof(fp)) break;
		// printf("%s",st);
		int l = strlen(st+1);
		char store[1024] = {'\0'};
		for(int i=1;st[i]!=' ';i++){
			store[i-1] = st[i];
		}
		if(st[0]=='0'){
			printf("[%d]\tStopped\t%s",counter++,st+strlen(store)+2);
		}
		else printf("[%d]\tRunning\t%s",counter++,st+strlen(store)+2);
	}
	fclose(fp);
}

void kjob(){
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	int counter = 0;
	while(1){
		char st[1024];
		fgets(st,200,fp);
		counter++;
		if(feof(fp)) break;
		// printf("%s",st);
		int l = strlen(st+1);
		char store[1024] = {'\0'};
		for(int i=1;st[i]!=' ';i++){
			store[i-1] = st[i];
		}
		int val = calculater(store,strlen(store)+1);
		if(counter==input[1][0]-'0' && strlen(input[1])==1){
			if(strlen(input[2])==1) kill(val,input[2][0]-'0');
			break;
		}
	}
	if(counter != input[1][0]-'0'){
		perror("invalid no of inputs");
	}
	fclose(fp);
}

void overkill(){
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	while(1){
		char st[1024];
		fgets(st,200,fp);
		if(feof(fp)) break;
		// printf("%s",st);
		if(st[0]=='0') continue;
		int l = strlen(st+1);
		char store[1024] = {'\0'};
		for(int i=1;st[i]!=' ';i++){
			store[i-1] = st[i];
		}
		int val = calculater(store,strlen(store)+1);
		if(kill(val,9)==0){
			printf("[%s] has exited\n",store);
			fseek(fp,-l-1,SEEK_CUR);
			fputc('0',fp);
			fseek(fp,(l),SEEK_CUR);
		}
	}
	fclose(fp);
}

void fg(){
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	int counter = 0,status;
	while(1){
		char st[1024];
		fgets(st,200,fp);
		counter++;
		if(feof(fp)) break;
		// printf("%s",st);
		int l = strlen(st+1);
		char store[1024] = {'\0'};
		for(int i=1;st[i]!=' ';i++){
			store[i-1] = st[i];
		}
		int val = calculater(store,strlen(store)+1);
		if(counter==input[1][0]-'0'){
			printf("inside\n");
			kill(val,SIGCONT);
			waitpid(val,&status,0);
			break;
		}
	}
	if(counter != input[1][0]-'0'){
		perror("invalid no of inputs");
	}
	fclose(fp);
}


#endif

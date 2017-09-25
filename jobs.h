#ifndef gh
#define gh
void jobs(){
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	int counter = 1;
	while(1){
		char st[1024];
		fgets(st,200,fp);
		if(st[0]=='0') continue;
		if(feof(fp)) break;
		int l = strlen(st+1);
		char store[1024] = {'\0'};
		for(int i=1;st[i]!=' ';i++){
			store[i-1] = st[i];
		}
		int val = calculater(store,strlen(store)+1);
		char save[1024] = "/proc/",stor[1024]={'\0'};
		strcat(save,store);
		strcat(save,"/status");
		FILE *fil = fopen(save,"r");
//		printf("%s\n",save);
		if(fil==NULL){
			perror("File not opened");
			return;
		}
		if(st[0]=='0'){
			continue;
		}
		else{
			counter++;
			FILE *fil = fopen(save,"r");
			while(1){
				fgets(stor,200,fil);
				if(strstr(stor,"State") != NULL){
					if(strstr(stor,"stopped")){
						printf("[%d]\tStopped\t%s\n",counter,st+1+strlen(store));
					}
					else{
						printf("[%d]\tRunning\t%s\n",counter,st+1+strlen(store));
					}
					break;
				}
			}
			fclose(fil);
		}
	}
	fclose(fp);
}

#endif

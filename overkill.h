#ifndef over
#define over

void overkill(){
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	while(1){
		char st[1024];
		fgets(st,200,fp);
		if(feof(fp)) break;
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
#endif

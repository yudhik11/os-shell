#ifndef kj
#define kj

void kjob(){
	FILE *fp = NULL;
	fp = fopen(paths,"r+");
	int counter = 0;
	while(1){
		char st[1024];
		fgets(st,200,fp);
		st[0]!=0?counter++:counter;
		if(feof(fp)) break;
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
#endif
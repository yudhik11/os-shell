#ifndef xa
#define xa 
void echo(){
    for (int i=1;i<cnt;i++) {
        for(int j=0;j<1005;j++) if(input[i][j]==0) break;
		if (input[i][0]=='$'){
			const char* s = getenv(input[i]+1);
            printf("%s",(s!=NULL)? s : "");
        }
        else
            printf("%s ",input[i]);
    }
    printf("\n");
}
#endif

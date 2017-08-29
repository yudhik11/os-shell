void echo(){
    for (int i=1;i<cnt;i++) {
        if (input[i][0]=='$'){
            const char* s = getenv(input[i]+1);
            printf("%s",(s!=NULL)? s : "");
        }
        else
            printf("%s ",input[i]);
    }
    printf("\n");
}

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
    if (strcmp(input[0], "cd")==0){
        implement_cd();
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
    else{
        execute(cnt);
    }
}
#endif

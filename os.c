#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<dirent.h>
#include<string.h>
char input[1005][1005];
char inp[10005];
char cwd[1024];
char pwd[1024];
char *input2[1024];
int cnt=0,len=0;
void background_proc(){
    int pid = fork();
    if(pid==0){
        int p = fork();
        if(p==0){
            fprintf(stderr,"[%d]\n",getpid());
            execvp(input2[0],input2);
        }
        else exit(0);
    }
    else{
        wait(NULL);
    }
}
void fz(char *sz,long int val){
    if (!val) return ;
    len--;
    fz(sz,val/10);
    int x=val%10;
    sz[++len]=x+48;
}
void ls(){
    int hide=0,det=0,files=0;
    for (int i=1;i<cnt;i++){
        if (input[i][0]=='-'){
            for(int j=0;j<strlen(input[i]);j++){
                if (input[i][j]=='a') hide=1;
                if (input[i][j]=='l') det=1;
            }
        }
        else files++;
    }
    DIR *mydir,*mydir1;
    struct dirent *myfile;
    struct stat mystat;

    char buf[512];
    long int mx=0;
    int total=0;
    if (files==0){
        mydir = opendir(".");
        while((myfile = readdir(mydir)) != NULL){
            char *temp=myfile->d_name;
            if (temp[0]=='.' && !hide) continue;
            sprintf(buf, "%s/%s", ".", myfile->d_name);
            stat(buf, &mystat);
            mx=mx>mystat.st_size?mx:mystat.st_size;
            total+=mystat.st_blocks;
        }
        if (det) printf("total %d\n",total/2);
        int ln=0;
        while(mx){
            ln++;
            mx/=10;
        }
        ln=ln>6?ln:6;
        mydir = opendir(".");
        while((myfile = readdir(mydir)) != NULL){
            char *temp=myfile->d_name;
            if (temp[0]=='.' && hide==0) continue;
            if (det){
                sprintf(buf, "%s/%s", ".", myfile->d_name);
                stat(buf, &mystat);
                printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
                printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
                printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
                printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
                printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
                printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
                printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
                printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
                printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
                printf( (mystat.st_mode & S_IXOTH) ? "x " : "- ");

                nlink_t hdlink=mystat.st_nlink;
                printf("%lu ",hdlink);

                struct passwd *pw = getpwuid(mystat.st_uid);
                struct group  *gr = getgrgid(mystat.st_gid);
                printf("%s %s ", pw->pw_name, gr->gr_name);

                char *date=ctime(&mystat.st_mtime);
                len=strlen(date);
                for(int i=0;i<9;i++)
                    date[len-1-i]='\0';
                long int val=mystat.st_size;

                char sz[20];
                memset(sz,' ',sizeof(sz));
                sz[20]='\0';

                len=19;
                fz(sz,val);
                printf("%s %s ",sz+20-ln,date+4);
                printf(" %s\n", myfile->d_name);
            }
            else printf("%s ", myfile->d_name);
        }
        if (!det) printf("\n");
        closedir(mydir);
    }
    else {
        for (int i=1;i<cnt;i++)
            if (input[i][0]!='-'){
                int flag=0;
                mydir = opendir(".");
                while((myfile = readdir(mydir)) != NULL){
                    char *temp=myfile->d_name;
                    if (strcmp(temp,input[i])!=0) continue;
                    if (temp[0]=='.' && hide==0) continue;
                    flag=1;
                    if (det){
                        sprintf(buf, "%s/%s", ".", myfile->d_name);
                        stat(buf, &mystat);
                        printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
                        printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
                        printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
                        printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
                        printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
                        printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
                        printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
                        printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
                        printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
                        printf( (mystat.st_mode & S_IXOTH) ? "x " : "- ");

                        nlink_t hdlink=mystat.st_nlink;
                        printf("%lu ",hdlink);

                        struct passwd *pw = getpwuid(mystat.st_uid);
                        struct group  *gr = getgrgid(mystat.st_gid);
                        printf("%s %s ", pw->pw_name, gr->gr_name);

                        char *date=ctime(&mystat.st_mtime);
                        len=strlen(date);
                        for(int i=0;i<9;i++)
                            date[len-1-i]='\0';
                        long int val=mystat.st_size;

                        char sz[20];
                        memset(sz,' ',sizeof(sz));
                        sz[20]='\0';

                        len=19;
                        fz(sz,val);
                        printf("%s %s ",sz+20-10,date+4);
                        printf(" %s\n", myfile->d_name);
                    }
                    else printf("%s ", myfile->d_name);
                    break;
                }
                if (flag==0)
                    printf("ls: cannot access '%s': No such file or directory\n",input[i]);
                closedir(mydir);
            }
        if (!det) printf("\n");
    }
}

void foreground_proc(){
    int pid = fork();
    if(pid==0){
        execvp(input[0],input2);
    }
    else{
        wait(NULL);
    }
}

void execute(int len){
    //int cont=0;
    for(int i=0;i<len;i++){
        if(input[i][0]=='&'){
            input2[i] = NULL;
            printf("background\n");
            background_proc();
            //cont=0;
            return;
        }
        else{
            input2[i] = input[i];
        }
    }
    input2[len] = NULL;
    //	if(cont > 0){
    printf("foreground\n");
    //	}
    foreground_proc();
}

int getwords(char inp[]){
    cnt=0;
    char *ch = strtok (inp,"\" \t");
    while (ch != NULL){
        //printf("%s",input2[cnt]);
        strcpy(input[cnt++],ch);
        ch = strtok (NULL, " \"\t");
    }
    return cnt;
}
int implement_cd(){
    char ch[100]={'\0'};
    strcpy(ch,input[1]);
    char save[1024];
    save[1023] = '\0';
    if(strlen(ch)==0){
        chdir(cwd);
        return 0;
    }
    if(ch[0]=='~'){
        strcpy(save,cwd);
        strcat(save,"/");
        strcat(save,ch+1);
        chdir(save);
        return 0;
    }
    getcwd(save,sizeof(save));
    if(ch[0]!='/'){
        strcat(save,"/");
        strcat(save,ch);
        chdir(save);
    }
    else{
        chdir(ch);
    }
}
void pin(int self){
	if(self==1){
		FILE * fp;
		char save[1024]={'\0'};
		char str[1024] = "/proc";
		char pid[20];
		sprintf(pid,"/%d",getpid());
		strcat(str,pid); // /proc/<pid>
		strcpy(save,str); // /proc/<pid>
		strcat(save,"/status"); // /proc/<pid>/status
//		fprintf(stderr,"save:%s\n",save);
		fp = fopen(save,"r");
		char store[200],scanner[200],proc_status[200],virt_mem[200];;
		int len = 0;
		while(1){
			fgets(store,200,fp);
		//	len = strlen(store);
//			printf("store:%s\n",store);

			if(strstr(store,"State") != NULL){
				fscanf(fp,"%s %s",scanner,proc_status);
			}
			else if(strstr(store,"VmPeak") != NULL){
				fscanf(fp,"%s %s",scanner,virt_mem);
				break;
			}
		}
		printf("pid -- %d\n",getpid());
		printf("Process Status -- %s\n",proc_status);
		printf("Virtual Memory -- %s\n",virt_mem);
		printf("Executable Path -- ~/a.out\n");
		fclose(fp);
	}
	else{
		FILE *fp;
		char save[1024]={'\0'};
		char str[1024] = "/proc";
		char pid[20];
		char buff[2000];

		sprintf(pid,"/%s",input[1]);
		strcat(str,pid); // /proc/<pid>
		strcpy(save,str); // /proc/<pid>
		strcat(save,"/status"); // /proc/<pid>/status
		strcat(str,"/exe"); // str = /proc/<pid>/exe
//		fprintf(stderr,"save:%s\n",save);
		fp = fopen(save,"r");
		char store[200],scanner[200],proc_status[200],virt_mem[200];;
		int len = 0;
		while(1){
			fgets(store,200,fp);
//			printf("store:%s\n",store);

			if(strstr(store,"State") != NULL){
				fscanf(fp,"%s %s",scanner,proc_status);
			}
			else if(strstr(store,"VmPeak") != NULL){
				fscanf(fp,"%s %s",scanner,virt_mem);
				break;
			}
		}
		ssize_t ret = readlink(str, buff, 512);
		if (ret < 0){
		  perror("readlink");
		}
		else buff[ret] = 0;
		printf("pid -- %d\n",getpid());
		printf("Process Status -- %s\n",proc_status);
		printf("Virtual Memory -- %s\n",virt_mem);
		printf("Executable Path --%s\n",buff);
	}

}


void echo(){
    for (int i=1;i<cnt;i++) {
        if (input[i][0]=='$'){
            const char* s = getenv(input[i]+1);
            printf("%s",(s!=NULL)? s : "");
        }
        else
            printf("%s ",input[i]);
        printf("\n");
    }
}
void verify_cmd(){
    cnt = getwords(inp);
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

int main (){
    char hostname[1024];
    hostname[1023] = '\0';
    cwd[1023] = '\0';
    gethostname(hostname, 1023);//sys_name
    struct passwd *hello;
    hello=getpwuid(getuid());//user_name
    getcwd(cwd,sizeof (cwd));
    int cwdlen=strlen(cwd);
    int k=20;
    for (int i=0;i<k;i++){
        memset(input,0,sizeof(input));
        pwd[1023] = '\0';
        getcwd(pwd,sizeof (pwd));
        int pwdlen=strlen(pwd);
        if (pwdlen>=cwdlen)
            printf("<%s@%s:~%s>$ ",hello->pw_name,hostname,pwd+cwdlen);
        else
            printf("<%s@%s:%s>$ ",hello->pw_name,hostname,pwd);
        memset(inp,0,sizeof(inp));
        if (i>0) getchar();
        scanf("%[^\n]s",inp);
        verify_cmd();
    }
    return 0;
}

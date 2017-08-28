#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
int len;
void fz(char *sz,long int val){
    if (!val) return ;
    len--;
    fz(sz,val/10);
    int x=val%10;
    sz[++len]=x+48;
}
int main(int argc, char* argv[])
{
    DIR *mydir,*mydir1;
    struct dirent *myfile;
    struct stat mystat;

    char buf[512];
    mydir = opendir(".");
    mydir1 = opendir(".");
    long int mx=0;
    int total=0;
    while((myfile = readdir(mydir1)) != NULL){
        sprintf(buf, "%s/%s", ".", myfile->d_name);
                stat(buf, &mystat);
        mx=mx>mystat.st_size?mx:mystat.st_size;
        total+=mystat.st_blocks;
    }
    printf("total %d\n",total/2);
    int ln=0;
    while(mx){
        ln++;
        mx/=10;
    }
    while((myfile = readdir(mydir)) != NULL){
        char *temp=myfile->d_name;
        if (temp[0]=='.'){
            printf("hidden\n");
        //    continue;
        }
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
        //char date[100];
        //strftime(date, 20,"%d-%m-%y", localtime(&(mystat.st_ctime)));
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
    closedir(mydir);
}

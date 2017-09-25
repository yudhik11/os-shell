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
#include<fcntl.h>
#include<math.h>
#include<signal.h>
char input[1005][1005];
char inp[10005];
char cwd[1024];
char pwd[1024];
char *input2[1024];
char paths[1023]={'\0'};
int cnt=0,len=0;
int in;
int out;
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
#define KBLU  "\x1B[34m"

int calculater(char *arr,int l);

int calculater(char *arr,int l){
	int i,val=0,count=0,pwr=1;;
	for (i = l-2; i>=0; i--)
	{
		val+=(arr[i]-'0')*pwr;
		pwr*=10;
	}
	return val;
}

#include "echo.h"
#include "pinfo.h"
#include "cd.h"
#include "execute.h"
#include "ls.h"
#include "jobs.h"
#include "fgbg.h"
#include "overkill.h"
#include "kjob.h"
#include "verifycmd.h"
#include "pipeslin.h"


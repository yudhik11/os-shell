#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "signal.h"
#include "sys/dir.h"
#include "time.h"
#include "dirent.h"
#include "pwd.h"
#include "grp.h"
#include "wait.h"
#include "signal.h"
#include "setjmp.h"
#include "all.h"

#define clear() printf("\033[H\033[J")
#define GRE   "\x1B[32m"
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"
#define BLU  "\x1B[34m"
#define BLD  "\x1B[1m"

char host[500],user[500],initialdir[500];

sigjmp_buf ctrlc_buf;

// void  INThandler(int sig)
// {
//      char  c;
//
//      signal(sig, SIG_IGN);
//     //  printf("OUCH, did you hit Ctrl-C?\n"
//     //         "Do you really want to quit? [y/n] ");
//     //  c = getchar();
//      if (c == 'y' || c == 'Y')
//           exit(0);
//      else
//           signal(SIGINT, INThandler);
//     // getchar(); // Get new line character
// }

int checkInfile(char *tokens)
{

    char *temp[100]={NULL} ;

    divideToken(tokens,temp,"<");
    if(temp[1]!=NULL)
    {
        char *temp1[100]={NULL};
        divideToken(temp[1],temp1," ");
        return open(temp1[0],O_RDONLY);
    }
    return 0;
}

int checkOutfile(char *tokens)
{
	int app = 0,i=0;
	while(tokens[i+1]!='\0')
	{
		if(tokens[i]=='>' && tokens[i+1] == '>')
			app = 1;
		i++;
	}
    char *temp[100]={NULL} ;
    divideToken( tokens , temp , ">" );
    if(temp[1]!=NULL)
    {
        char *temp1[100]={NULL};
        divideToken( temp[1],temp1," ");
        if(app == 1){
        	return open(temp1[0],O_WRONLY|O_APPEND, S_IRWXU);
        }
        return open(temp1[0],O_TRUNC|O_WRONLY|O_CREAT, S_IRWXU);
    }	
    return 1;

}


void handle_signals(int signo)
{
  if (signo == SIGINT)
  {
    printf("\n");
    //printf("You pressed Ctrl+C\n");
    siglongjmp(ctrlc_buf, 1);
  }
}

int main()
{
	//signal(SIGINT, INThandler);
  clear();
  if (signal(SIGINT, handle_signals) == SIG_ERR) {
   printf("failed to register interrupts with kernel\n");
  }

	char currdir[1000];
	gethostname(host,500);
	getlogin_r(user,500);
	getcwd(currdir,1000);
	strcpy(initialdir,currdir);
 	while ( sigsetjmp( ctrlc_buf, 1 ) != 0 );
	while(1)
	{
		// if ( signal(SIGINT,INThandler) == 0 )
		//  {
    //  	continue;
		//  }
		char input[500],final[500];
		char* allpipe[50] = {NULL};

		memset(final,'\0', sizeof(final));
		memset(currdir,'\0', sizeof(currdir));
		memset(host,'\0', sizeof(host));
		memset(user,'\0', sizeof(user));
		memset(allpipe,'\0', sizeof(allpipe));

		gethostname(host,500);
		getlogin_r(user,500);
		getcwd(currdir,1000);
		tildacorrect(currdir,initialdir,final);

		printf(BLD RED "<%s@%s"RESET BLD ":" BLU "%s> " RESET,user,host,final);
		fgets(input,500,stdin);
		input[strlen(input)-1] = '\0';

		if(input[0] == '\0')
			continue;

		divideToken(input,allpipe,";"); // sadva sadf; sdsavas asvasv vsa ;svfv;

		int i=0;
		while(allpipe[i]!=NULL)
		{	
			char* allcomds[100] = {NULL};
			int p=0,pipearr[2];
			int stdin = dup(0);
			int stdout = dup(1);
			divideToken(allpipe[i],allcomds,"|");
			while(allcomds[p]!=NULL)
			{
				pipe(pipearr);
				getcwd(currdir,1000);
				char* command[10] = {NULL};
				char* command1[10] = {NULL};
				char* command2[10] = {NULL};
				char fullcmd[100];
				char fullcmd1[100];

				// memset(fullcmd,'\0',sizeof(fullcmd));
				strcpy(fullcmd,allcomds[p]);
				strcpy(fullcmd1,allcomds[p]);
				int flagval=0;

				divideToken(allcomds[p],command1,">");
				divideToken(command1[0],command2,"<");
				divideToken(command2[0],command," \n\t");
				int INFILE = checkInfile(fullcmd);
				int OUTFILE = checkOutfile(fullcmd1);
				// printf("%d%d\n",INFILE,OUTFILE);

			    if(INFILE != 0)
		        {
		            dup2(INFILE,0);
		            close(INFILE);
		        }
		        if(OUTFILE != 1)
		        {
		        	// printf("lolol\n");
		            dup2(OUTFILE,1);
		            close(OUTFILE);
				}
				// if(INFILE==0 && OUTFILE == 1)
				// {
					flagval+=checkPWD(command);
					flagval+=checkEcho(command);
					flagval+=checkCd(command,initialdir);
					flagval+=checkClear(command);
					flagval+=checkLs(command);
					flagval+=checkExit(command);
					flagval+=checkPinfo(command,initialdir);
				// }

				if(flagval == 0)
				{
					execute(command,INFILE,OUTFILE,initialdir);
				}
				p++;
				INFILE=pipearr[0];
                close(pipearr[1]);
			}
			dup2(stdin,0);
			dup2(stdout,1);
			i++;
	    }
	}   
	return 0;
}

#include "overkill.h"
void overkill(){
    int i;
    if(bgcount>1)
        for(i=bgcount-1;i>0;i--)
        {
            kill(job[i].pid,9);
            signal(SIGCHLD,sig_handler);
        }
    else
        printf("No Background Jobs detected.\n");
    bgcount=1;
}

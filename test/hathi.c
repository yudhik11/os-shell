int kjob(char **args)
{
        if(args[1]==NULL || args[2] ==NULL)
        {
                fprintf(stderr, "Usage: kjob <jobid> <signal>\n");
                return 0;

        }

        int jbid = atoi(args[1]);
        if(jbid > max)
        {
                fprintf(stderr, "Error job number does not exist\n");
                return 0;
        }

        int sig=atoi(args[2]);
        kill(backgrund_process[jbid].pid,sig);
        backgrund_process[jbid].state=-1;
        return 1;
}


int fg(char **args)
{

        if(args[1]==NULL)
        {
                fprintf(stderr, "Usage: fg <jobid>\n");
        }
        pid_t wpid;
        int jbid=atoi(args[1]);
        printf("%s\n",backgrund_process[jbid].command);
        int status;
        backgrund_process[jbid].state=1;
        kill(backgrund_process[jbid].pid,SIGCONT);

        do {
                wpid = waitpid(backgrund_process[jbid].pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        return 1;
}


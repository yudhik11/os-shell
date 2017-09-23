#include<stdio.h>
#include<unistd.h>

int main(){
	char *argv[1024];
	argv[0] = "firefox";
	argv[1] = NULL;
	argv[2] = "emacs";
	argv[3] = NULL;
	execvp(argv[0],argv);
}

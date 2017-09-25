#include "unsetenv.h"
void unset_env(char* arg[1000]){
	if(getenv(arg[1])==NULL)printf(RED "No such enviorment variable" RESET "\n");
	else if(unsetenv(arg[1])!=0)printf(RED "Unidentified error" RESET "\n");
}
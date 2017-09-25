#include "setenv.h"
void set_env(char* args[1000]){
	if(getenv(arg[1])==NULL)setenv(arg[1],"",1);
	if(arg[2][0]==' ')setenv(arg[1],"",1);
	else setenv(arg[1],arg[2],1);
}

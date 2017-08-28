#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv ){
	const char *target = "/home/anvesh/../..";
	char directory[1024];

	getcwd(directory, sizeof(directory));
	printf("In %s\n", directory);

	if(chdir(target) == 0) {
		getcwd(directory, sizeof(directory));
		printf("In %s\n", directory);
	}
	return 0;
}

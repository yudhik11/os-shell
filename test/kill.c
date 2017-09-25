#include<stdio.h>
#include <signal.h>
int main(){
	int i,j;
	scanf("%d%d",&i,&j);
	kill(i,j);
	return 0;
}

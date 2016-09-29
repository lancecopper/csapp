#include "csapp.h"

int foo();

int main(){
	printf("%d\n", foo());
}

int foo(){
	exit(1024);
}



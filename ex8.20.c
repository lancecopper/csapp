#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[], char *envp[]){
	char *columns;
	char name[20] = "COLUMNS";
	columns = getenv(name);
	printf("  ...output is %s colunms wide\n", columns);
	return 1;
}



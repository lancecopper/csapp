#include <unistd.h>

int main(int argc, char *args[], char *envp[])
{
    execve("/bin/ls", args, envp);
    return 0;
}



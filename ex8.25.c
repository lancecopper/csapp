/*
fgets的定义如下：
char *fgets(char *buf, int bufsize, FILE *stream);
参数：
*buf: 字符型指针，指向用来存储所得数据的地址。
bufsize: 整型数据，指明buf指向的字符数组的大小。
*stream: 文件结构体指针，将要读取的文件流。

这个应该是用alarm发送信号给自己，然后在信号处理程序里面做文章。
显然，在tfgets里一开始需要调用fgets。然而，因为五秒时间到了，
fgets还没有返回，所以我们必须在处理程序里直接跳转到某个地方进行tfgets的NULL返回。
这就需要用到非本地跳转。

*/

// #include <csapp.h>
#include <stdio.h>
#include <stlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

sigjmp_buf env;

void tfgets_handler(int sig){
	signal(SIGALRM, SIG_DFL);
	siglongjmp(env, 1);
}

char *tfgets(char *buf, int bufsize, FILE *stream){
	static const int TimeLimitSecs = 5
	signal(SIGALRM, tfgets_handler);
	alarm(TimeLimitSecs);
	int rc = sigsetjmp(env, 1);
	if(rc == 0)
		return fgets(buf, bufsize, stream);
	else
		return NULL;
}















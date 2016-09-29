#include <stdio.h>  
#include <unistd.h>  
#include <signal.h>  
  
int sleep_with_restart(int second);  
void signal_handler_int(int s);  
 
void signal_handler_alarm(int s);   
  
int sleep_with_restart(int second)  {  
	int left;  

	left = second;  

	#if 0 //case 1, sleep can be wake up by alarm or Ctrl + C, and the function will exit  
		left = sleep(left);//sleep()被中断之后会返回剩余的秒数  
	#endif  
  
 	#if 1 //case 2, sleep can be wake up by alarm or Ctrl + C, but we can restart it! because the sleep function will return the left second after be wake up!      
    
    while (left > 0){  
     	fprintf(stdout, "Restarting sleep(%d) .../n", left);  
     	left = sleep(left);//sleep()<strong><span style="color:#ff0000;">被中断之后会返回剩余的秒数
     }  
 	#endif  
  
	return 0;  
	}  
  
void signal_handler_int(int s){
	fprintf(stdout,"Caught signal SIGINT %d .../n", s);  
	}   
  
void signal_handler_alarm(int s)  {  
	fprintf(stdout,"Caught signal SIGALRM %d .../n", s);  
	}   
  
int main(int argc, char **argv){  
	signal(SIGINT, signal_handler_int);  
	signal(SIGALRM, signal_handler_alarm);  

	alarm(3);  
	sleep_with_restart(10);  
	return 0;  
}  



int readcnt;
sem_t mutex, w, wt;

void reader(void){
	while (1){

		P(&mutex);
		if (readcnt == 0)
			P(&w);
		readcnt++;
		V(&mutex);


		P(&mutex);
		readcnt++;
		if (readcnt == 1) /* First in */
			P(&w);
		V(&mutex);

		P(&mutex);
		readcnt--;
		if (readcnt == 0) /* Last out */
			V(&w);
		V(&mutex);
		
	}
}

void writer(void){
	while (1){
		P(&wt);
		P(&w);

		/* Critical section */
		/* Writing happens */

		V(&w);
		V(&wt);
	}
}











int readcnt;
sem_t mutex, w, wr, r;

void reader(void){
	while (1){
		P(&r);
		P(&wr);
		V(&wr);
		V(&r);

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
		P(&wr);
		P(&w);

		/* Critical section */
		/* Writing happens */

		V(&w);
		V(&wr);
	}
}










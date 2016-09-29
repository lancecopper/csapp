int readcnt;
define N 100;

sem_t mutex, w, wr;

void reader(void){
	while (1){


		P(&mutex);
		readcnt++;

		if (readcnt == 1)
			P(&w);


/*
 * 		while(readcnt >N)
 *			pass;
 */
		if (readcnt >= N){
			V(&mutex);
			P(&wr);
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
			V(&wr);
		}
		else
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







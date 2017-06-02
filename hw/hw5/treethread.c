#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

// parameters passed to each thread
// need to keep track of threadnum to print, and which layer we are at in the binary tree
struct args {
	int tnum;
	int layer;
};

int numlayers = 0;

void reportError(char * msg) {
	printf("ERROR: %s\n", msg);
	exit(1);
}

void * thread(void *params) {
	struct args arg = * (struct args *) params;
	int threadLayer = arg.layer;
	if (threadLayer == numlayers) { //we done!
		printf("Thread %i done\n", arg.tnum);
		return NULL;
	} else {
		struct args ch1args, ch2args;

		ch1args.tnum = (2 * arg.tnum) + 1;
		ch2args.tnum = (2 * arg.tnum) + 2;
		
		ch1args.layer = threadLayer + 1;
		ch2args.layer = threadLayer + 1;

		pthread_t tid1, tid2;

		if (pthread_create(&tid1, 0, thread, &ch1args))
			reportError("cannot create thread");	
		if (pthread_create(&tid2, 0, thread, &ch2args))
			reportError("cannot create thread");	
			
		if (pthread_join(tid1, NULL) )
			reportError("cannot join thread");	
		if (pthread_join(tid2, NULL))
			reportError("cannot join thread");	

		printf("Thread %i done\n", arg.tnum);;
		return NULL; 
	}
}

int main(int argv, char ** argc) {
	numlayers = atoi(argc[1]);
    int numthreads = pow(2, numlayers) - 2;
    int threadNum = 0;
    //main thread should either create two more leafs, or create 0 leafs.
    if (numthreads == 0)  // no need to spawn more threads
       printf("Thread %i done\n", threadNum); 
    else {
		//child thread args
		int ch1 = (2 * threadNum) +1;
		int ch2 = (2 * threadNum) +2;

		struct args ch1args, ch2args;

		ch1args.tnum = ch1;
		ch1args.layer = 2;

		ch2args.tnum = ch2;
		ch2args.layer = 2;

		pthread_t tid1, tid2;

		if (pthread_create(&tid1, 0, thread, &ch1args))
			reportError("cannot create thread");	
		if (pthread_create(&tid2, 0, thread, &ch2args))
			reportError("cannot create thread");	
			
		if (pthread_join(tid1, NULL) )
			reportError("cannot create thread");	
		if (pthread_join(tid2, NULL))
			reportError("cannot create thread");	

		printf("Thread %i done\n", threadNum);
    }

    return(0);
}

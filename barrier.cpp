#include <semaphore.h>
#include "barrier.h"

namespace synchronization {
    //Constructor, Initialize all variables 
    barrier::barrier(int numberOfThreads) {
        countThreads = 0;
        totalThreads = numberOfThreads;
        sem_init(&mutualEx, 0, 1);
        sem_init(&turnstileBlock, 0, 0);
        sem_init(&turnstileReset, 0, 0);
    }
    
    //Destructor, Destroy all Semaphores
    barrier::~barrier() {
        sem_destroy(&mutualEx);
        sem_destroy(&turnstileBlock); 
        sem_destroy(&turnstileReset);
    }

    void barrier::arriveAndWait( void ) {
        //Block until all threads arrive
        sem_wait(&mutualEx);
        countThreads++;
        if (countThreads == totalThreads) {
            for (int i = 0; i < totalThreads; i++) {
                sem_post(&turnstileBlock);
            }
        }
        sem_post(&mutualEx);
        sem_wait(&turnstileBlock);


        //Reset for the next usage
        sem_wait(&mutualEx);
        countThreads--;
        if (countThreads == 0) {
            for (int i = 0; i < totalThreads; i++) {
                sem_post(&turnstileReset);
            }
        }
        sem_post(&mutualEx);
        sem_wait(&turnstileReset);
    }

}
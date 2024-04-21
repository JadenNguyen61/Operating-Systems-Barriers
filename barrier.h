#ifndef BARRIER_H
#define BARRIER_H

#include <semaphore.h>

namespace synchronization {

    class barrier {
    private:
        int countThreads; // Count # of threads arrived 
        int totalThreads; // # of threads to reach the barrier before released
        sem_t mutualEx; //Mutual Exclusion when updating count
        sem_t turnstileBlock, turnstileReset; // First semaphore for blocking threads until all have arrived and then release, and Second for resetting of the barrier.

    public:
        // Constructor
        barrier(int numberOfThreads);

        // Destructor
        ~barrier();

        // Function to wait at the barrier until all threads have reached the barrier
        void arriveAndWait( void );
    };

}

#endif // BARRIER_H

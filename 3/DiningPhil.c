#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

//The states
#define THINKING 0
#define HUNGRY 1
#define EATING 2

//Left and right checkers
#define LEFT (i-1)%5
#define RIGHT (i+1)%5

//Mutex variable
sem_t mutex;

//Lise of semaphores, here 5
sem_t S[5];

int state[5];
int thePhils[] = {0,1,2,3,4};

//Functions to be called
void think(int);
void get_forks(int);
void eat(int);
void put_forks(int);
void *phil(void *i);
void checkNeighbour(int);


//Function so philosopher 'i' pickup forks
void *phil(void *i){
    while (1){
        int *n = i;
        sleep(1);
        get_forks(*n);
        sleep(0);
        put_forks(*n);
    }
}

//Commands them to think
void think(int i){
    int think_duration = abs(rand()*100) % 4 + 5;
    printf("Philosopher %d is thinking for %d seconds. \n", thePhils[i], think_duration);
    sleep(think_duration);
}

//Commands them to eat
void eat(int i){
    int eat_duration = abs(rand()*100) % 7 + 1;
    printf("Philosopher %d is eating for %d seconds.\n", thePhils[i], eat_duration);
    sleep(eat_duration);
}

//Check ig neighbours are eating
void checkNeighbour(int i){
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
        state[i] = EATING;
        eat(i);
        sem_post(&S[i]);
    }
}

//Command them to eating if hungry
void get_forks(int i){
    sem_wait(&mutex);
    state[i] = HUNGRY;
    printf("Philospher %d is hungry.\n", thePhils[i]);
    checkNeighbour(i);
    sem_post(&mutex);
    sem_wait(&S[i]);
}

//Command the phil to stop eating and start thinking again
void put_forks(int i){
    sem_wait(&mutex);
    state[i] = THINKING;
    think(i);
    checkNeighbour(LEFT);
    checkNeighbour(RIGHT);
    sem_post(&mutex);
}



int main(){
    int i;
    pthread_t threads[5];
    sem_init(&mutex, 0, 1);

    for(i = 0; i < 5; i++){
        sem_init(&S[i], 0, 0);
    }
    for(i = 0; i < 5; i++){
        pthread_create(&threads[i], NULL, phil, &thePhils[i]);
        think(i);
    }
    for(i = 0; i < 5; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}
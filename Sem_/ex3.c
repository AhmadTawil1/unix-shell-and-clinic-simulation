#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N 10 
#define SIZE_OF_SOFA 4
#define NUMBER_OF_DEN 3

int standing[N]; // Queue for patients standing
int sitting[SIZE_OF_SOFA]; // Queue for patients sitting
int waiting = 0; // Number of patients waiting to enter
int working_den = 0; // Number of working dentists

// Semaphores for synchronization
sem_t mutex;
sem_t sofa;
sem_t patients;
sem_t den_hygienist;
sem_t treatment_chairs;
sem_t paying;
sem_t payed;
sem_t cashbox;


// Functions prototype
void* enter_clinic(void*);
void wait_to_sit(int);
void sit_on_sofa(int);
void get_treatment(int);
void payment(int);
void give_treatment(int);
void take_payment(int);
void* den_sleep(void*);

int main()
{
	int i;
	pthread_t patients_t[N + 2];
	pthread_t den_t[NUMBER_OF_DEN];

	// Initialize semaphores
	sem_init(&mutex, 0, 1);
	sem_init(&sofa, 0, SIZE_OF_SOFA);
	sem_init(&patients, 0, N);
	sem_init(&den_hygienist, 0, 0);
	sem_init(&treatment_chairs, 0, NUMBER_OF_DEN);
	sem_init(&paying, 0, 0);
	sem_init(&payed, 0, 0);
	sem_init(&cashbox, 0, 1);

	// Create patient threads
	for (i = 0; i < N + 2; i++)
	{
		int* id = malloc(sizeof(int));
		*id = i + 1;
		pthread_create(&patients_t[i], NULL, enter_clinic, id);

	}

	// Create dentist threads
	for (i = 0; i < NUMBER_OF_DEN; i++)
	{
		int* id = malloc(sizeof(int));
		*id = i + 1;
		pthread_create(&den_t[i], NULL, den_sleep, id);

	}

	// Join patient threads
	for ( i = 0; i < N+2; i++)
	{
		pthread_join(patients_t[i], NULL);
	}

	// Join dentist threads
	for (i = 0; i < N + 2; i++)
	{
		pthread_join(den_t[i], NULL);
	}

	return 0;
}

// Function for patients entering the clinic
void* enter_clinic(void* id)
{
	int currentId = *(int*)id;
	while (1)
	{
		if (waiting == N)
		{
			printf("I'm Patient #%d, I'm out of clinic\n", currentId);
		}
		sem_wait(&patients);
		sem_wait(&mutex);
		waiting++;
		printf("I'm Patient #%d, I got into the clinic\n", currentId);
		sem_post(&mutex);
		sleep(1);
		if (sitting[SIZE_OF_SOFA - 1] != 0)
		{
			wait_to_sit(currentId);
		}
		sit_on_sofa(currentId);
	}
}

// Function for patients waitnig to sit on the sofa
void wait_to_sit(int id)
{
	int i;
	sem_wait(&mutex);
	for (i = 0; i < N; i++)
	{
		if (standing[i] == 0)
		{
			standing[i] = id;
			break;
		}
	}
	sem_post(&mutex);

	while (standing[N - 1] != id);
	while (sitting[SIZE_OF_SOFA - 1] != 0);

	sem_wait(&mutex);
	for (i = 0; i < N; i++)
	{
		if (standing[i] == id)
		{
			standing[i] = 0;
			break;
		}
	}
	sem_post(&mutex);
}

//Function for patients sitting on the sofa
void sit_on_sofa(int id)
{
	int i;
	sem_wait(&sofa);

	sem_wait(&mutex);
	for (i = 0; i < SIZE_OF_SOFA; i++)
	{
		if (sitting[i] == 0)
		{
			sitting[i] = id;
			break;
		}
	}

	printf("I'm Patient #%d, I'm sitting on the sofa\n", id);
	sem_post(&mutex);
	sleep(1);

	while (sitting[SIZE_OF_SOFA - 1] != id);
	get_treatment(id);
}

// Function for patients getting treatment
void get_treatment(int id)
{
	int i;
	while (working_den == NUMBER_OF_DEN);
	
	sem_wait(&treatment_chairs);
	sem_wait(&mutex);
	for ( i = 0; i < SIZE_OF_SOFA; i++)
	{
		if (sitting[i] == id)
		{
			sitting[i] = 0;
			break;
		}
	}

	sem_post(&sofa);
	printf("I'm Patient #%d, I'm getting treatment\n", id);
	sem_post(&den_hygienist);
	sem_post(&mutex);
	sleep(1);

	payment(id);
}

// Function for patients making payment
void payment(int id)
{
	sem_wait(&paying);
	sem_wait(&cashbox);
	sem_wait(&mutex);
	printf("I'm Patient #%d, I'm paying now\n", id);
	sem_post(&payed);
	sem_post(&mutex);
	sleep(1);
}

// Function for dentists sleeping until a patient arrives
void* den_sleep(void* id)
{
	int currentId = *(int*)id;
	while (1)
	{
		sleep(1);
		sem_wait(&den_hygienist);
		give_treatment(currentId);
	}
}

// Function for dentists giving treatment
void give_treatment(int id)
{
	sem_wait(&mutex);
	working_den++;
	printf("I'm Dental Hygienist #%d, I'm working now\n", id);
	sem_post(&paying);
	sem_post(&mutex);
	take_payment(id);
}

// Function for dentists taking payment
void take_payment(int id)
{
	sem_wait(&payed);
	sem_wait(&mutex);
	printf("I'm Dental Hygienist #%d, I'm getting a payment\n", id);
	working_den--;
	waiting--;
	sem_post(&cashbox);
	sem_post(&patients);
	sem_post(&treatment_chairs);
	sem_post(&mutex);
	sleep(1);
}


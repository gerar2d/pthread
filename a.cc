#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <time.h> 

//Global variables
int shared_data_buffer[4]; //shared data buffer for readers and writers
int reader_count = 0; //number of reader processes
int writer_count = 0; //number of writer processes
int reader_pc[3]; //program counter for reader processes
int writer_pc[2]; //program counter for writer processes

//Binary semaphore
bool binary_semaphore = true; //using boolean flag 

//Counting semaphore
int counting_semaphore = 0; //using integer counter

//Function to randomly select a process
int select_process() { 
	srand(time(0)); 
	return rand() % 7; 
}

//Reader process
void reader(int reader_id) { 
	
	//Check if binary semaphore is free
	if(binary_semaphore) {
		
		//Set binary semaphore to busy
		binary_semaphore = false;
		
		//Increase reader count
		reader_count++;
		
		//Check if there are any other readers or writers
		if(reader_count > 1 || writer_count > 0)
			printf("Reader %d entering critical section. There are %d readers and %d writers.\n", reader_id, reader_count-1, writer_count);
		else
			printf("Reader %d entering critical section. There are no other readers or writers.\n", reader_id);
		
		//Read data from shared data buffer
		int data = shared_data_buffer[reader_id];
		printf("Reader %d read data: %d.\n", reader_id, data);
		
		//Decrease reader count
		reader_count--;
		
		//Set binary semaphore to free
		binary_semaphore = true;
		
	}
	
	//If binary semaphore is busy
	else {
		printf("Panic! Reader %d was denied access to its critical section.\n", reader_id);
		reader_pc[reader_id]--; //rollback program counter
	}
	
}

//Writer process
void writer(int writer_id) { 
	
	//Check if binary semaphore and counting semaphore are free
	if(binary_semaphore && counting_semaphore == 0) {
		
		//Set binary semaphore and counting semaphore to busy
		binary_semaphore = false;
		counting_semaphore = -1;
		
		//Increase writer count
		writer_count++;
		
		//Check if there are any other readers or writers
		if(reader_count > 0 || writer_count > 1)
			printf("Writer %d entering critical section. There are %d readers and %d writers.\n", writer_id, reader_count, writer_count-1);
		else
			printf("Writer %d entering critical section. There are no other readers or writers.\n", writer_id);
		
		//Write data to shared data buffer
		int data = rand() % 10; //generate random data
		shared_data_buffer[writer_id] = data;
		printf("Writer %d wrote data: %d.\n", writer_id, data);
		
		//Decrease writer count
		writer_count--;
		
		//Set binary semaphore and counting semaphore to free
		binary_semaphore = true;
		counting_semaphore = 0;
		
	}
	
	//If binary semaphore and counting semaphore are busy
	else {
		printf("Panic! Writer %d was denied access to its critical section.\n", writer_id);
		writer_pc[writer_id]--; //rollback program counter
	}
	
}

int main() { 
	
	//Initializing program counters
	for(int i = 0; i < 4; i++)
		reader_pc[i] = 0;
	for(int i = 0; i < 3; i++)
		writer_pc[i] = 0;
	
	//Loop until all processes complete execution
	while(reader_pc[0] < 2 || reader_pc[1] < 2 || reader_pc[2] < 2 || reader_pc[3] < 2 ||
		  writer_pc[0] < 2 || writer_pc[1] < 2 || writer_pc[2] < 2) {
		
		//Randomly select a process
		int process_id = select_process();
		
		//Execute the process
		if(process_id < 4)
			reader(process_id);
		else
			writer(process_id-4);
		
		//Update program counter of selected process
		if(process_id < 4)
			reader_pc[process_id]++;
		else
			writer_pc[process_id-4]++;
		
	}
	
	return 0; 
}

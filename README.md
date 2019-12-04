



*John Taylor*
# PES-Project-6: FreeRTOS
## Introduction
This repository includes software for the KL25Z that:

- Generates a sin wave using built in math functions
- Outputs the sin wave data onto the DAC
- Captures the DAC data into the ADC
- Performs analysis of the Data read from the ADC

This functionality is implemented using FreeRTOS tasks

## Observations
I Initially tried to copy the adc queue to another queue upon receiving 64 samples. I had to first make the queue structure visible by placing it in the .h file and changing QueueHandle_t from a void* to a xQUEUE*. However, since the queue structure is just pointers I was copying pointers to the same memory, which wasn't the intent.

What I ended up doing was copying the values in the queue to an array using DMA
## Design Decisions
In my implementation I decided to combine the two programs into one with the use of preprocessor #ifdefs. This is what we have been doing all semester and I'm used to it. Program 2 directly uses Program 1 so it just makes sense.

For the extra credit I decided to use the FreeRTOS queue structure instead of my Project 5 RingBuffer code. I also used a semaphore to block the LED usage.

My code creates 3 tasks initially:

- update_time
- update_dac
- read_adc

I have given the update_dac function the highest priority so that the sin wave is generated with the correct period, next is the read_adc task and finally the update_time task has the lowest priority since it is just for reference.

 Another task is called do_dsp generated inside the read_adc task when the ADC has acquired 64 samples. This task analyses the data and then suspends itself

- 
## Build Notes
1. Pull the repo from github
2. Import it into MCUXpresso IDE
3. You should be able to run the project easily since we aren't doing any weird cross compilation
### Modes
To run Program 1
~~~
//#define DB
//#define APPLICATION
~~~
To run Program 2
~~~
//#define DB
#define APPLICATION
~~~
uncomment DB to run debug alongside any other mode

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <memory.h>

typedef struct{
    int num_of_obj;
    unsigned long *arr_of_num;
    unsigned long *array_sum;
    int start;
    int end;
    int thread_id;

}thread_data;

//sums up all values exept its own for a certain range
void *sum(void *data)
{
    thread_data *t_data = (thread_data*)data;
    for(int start = t_data->start; start < t_data->end; start++)
    {
        unsigned long sum = 0;
        for(int i = 0; i < t_data->num_of_obj; i++)
        {
            if(i != start)
            {
                sum = sum + t_data->arr_of_num[i];
            }
        }
        t_data->array_sum[start] = sum;
    }
    return 0;
}

// returns array of chucksizes with max size diff = 1
int *get_sizes_of_chunk(int number_of_threads, int number_of_objects)
{
    int *chunk_sizes = (int *)malloc(number_of_threads * sizeof(int));
    int normal_chunk_size = number_of_objects / number_of_threads;
    int rest = number_of_objects % number_of_threads;

    for(int i = 0; i < number_of_threads; i++)
    {
        chunk_sizes[i] = normal_chunk_size;
        if(rest > 0)
        {
            chunk_sizes[i]++;
            rest--;
        }
    }
    return chunk_sizes;
}

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        puts("ERROR: wrong number of argument. Should be three");
        exit(EXIT_FAILURE);
    }

    // get command line arguments
    int number_of_objects = atoi(argv[1]);
    int number_of_iterations = atoi(argv[2]);
    int number_of_threads = atoi(argv[3]);
    unsigned long *array_of_numbers = (unsigned long*)malloc(number_of_objects * sizeof(unsigned long));
    unsigned long *array_of_sum_of_numbers = (unsigned long*)malloc(number_of_objects * sizeof(unsigned long));
    int *chunk_sizes = get_sizes_of_chunk(number_of_threads, number_of_objects);
    srand(time(NULL));
    int number = rand();
    pthread_t *threads = (pthread_t*)malloc(number_of_threads * sizeof(pthread_t));

    for(int i = 0; i < number_of_objects; i++)
    {
        number = rand() % 100;
        array_of_numbers[i] = number;
        //printf("%d ",number);
    }
    //puts("\n");

    thread_data* thread_data_arr = (thread_data*)malloc(number_of_threads * sizeof(thread_data));
    for(int j = 0; j < number_of_iterations; j++)
    {
        int start = 0;
        int end  = 0;
        
        // calculate data for threads
        for(int i = 0; i < number_of_threads; i++)
        {
            start = end;
            end = start + chunk_sizes[i];
            thread_data_arr[i].end = end;
            thread_data_arr[i].start = start;
            thread_data_arr[i].num_of_obj = number_of_objects;
            thread_data_arr[i].array_sum = array_of_sum_of_numbers;
            thread_data_arr[i].arr_of_num = array_of_numbers;
            thread_data_arr[i].thread_id = i;
        }

        //create n threads 
        for(int i = 0; i < number_of_threads; i++)
        {
            pthread_create(&threads[i],NULL,sum, &thread_data_arr[i]);
        }
        for(int i= 0; i < number_of_threads; i++)
        {
            pthread_join(threads[i],NULL);
        }
        memcpy(array_of_numbers, array_of_sum_of_numbers,number_of_objects * sizeof(unsigned long));
    }

    // free all arrays
    free(array_of_numbers);
    free(array_of_sum_of_numbers);
    free(thread_data_arr);
    free(chunk_sizes);
    free(threads);
    return EXIT_SUCCESS;
}


// ./a.out 1000 10000 1 25.41s
// ./a.out 1000 10000 2 26.90s
// ./a.out 1000 10000 4 36.64s

#include <stdio.h>

int main()
{
    unsigned long max = 1000;

    unsigned long primes[max];
    unsigned long next_space_in_primes = 0;
    for(unsigned long counter = 8 ;next_space_in_primes < max; counter++)
    {
        if(!(counter % 2 == 0 || counter % 3 == 0 || counter % 7 == 0 || counter %  5 == 0))
        {
            primes[next_space_in_primes] = counter;
            next_space_in_primes++;
        }
    }
    printf("1 2 3 5 7 ");
    for(int i = 0; i < 1000; i++)
    {
        printf("%lu ", primes[i]);
    }
}

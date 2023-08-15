#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

enum guess_state
{
    REPEAT,
    WIN
};

int generate_rand_num()
{
    int min = 1;
    int max = 10;

    return (rand() % (max - min + 1)) + min;
}

int is_number_match(int generated_num, int number_chosen)
{
    enum guess_state result;
    if (generated_num == number_chosen)
    {
        result = WIN;
        printf("You guessed the number!\n");
    }
    else if (number_chosen > generated_num)
    {
        printf("The number you've choosen is too much high!\n");
        result = REPEAT;
    }
    else
    {
        printf("The number you've chosen is too much low!\n");
        result = REPEAT;
    }
    return result;
}

void start_app()
{
    srand(time(0));

    int generated_num = generate_rand_num();
    int user_num_chosen;
    int result;

    while (result != WIN)
    {
        printf("Please enter a number from 1-10:\t");
        scanf(" %d", &user_num_chosen);

        if (user_num_chosen < 1 || user_num_chosen > 10)
        {
            printf("Invalid input!\n");
            break;
        }

        result = is_number_match(generated_num, user_num_chosen);
    }
}

int main()
{
    start_app();
    return 0;
}
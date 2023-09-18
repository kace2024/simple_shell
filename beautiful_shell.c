#include "shell.h"

/**
 * add_numbers - Adds two numbers
 * @num1: First number
 * @num2: Second number
 * Return: Sum of the two numbers
 */
int add_numbers(int num1, int num2)
{
    return num1 + num2;
}

/**
 * main - Entry point of the program
 * Return: Always 0 (Success)
 */
int main(void)
{
    int result;

    result = add_numbers(3, 4);
    printf("The sum is: %d\n", result);

    return 0;
}

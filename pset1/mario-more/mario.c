#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    //defines amount of rows
    for (int i = 1; i <= n; i++)
    {
        //adds spaces in the beginning
        for (int j = 0; j < n - i; j++)
        {
            printf(" ");
        }
        //inserts bricks to the left side
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        //adds a gap between bricks
        printf("  ");
        //inserts bricks to the right side
        for (int m = 0; m < i; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}

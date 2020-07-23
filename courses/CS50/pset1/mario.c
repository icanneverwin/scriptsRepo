#include <stdio.h>
#include <cs50.h>

//int main(void)
//{
//    int times;
//    do
//    {
//        times = get_int("Height: ");
//    }
//    while (times < 1 || times > 8);
//
//    if (times == 1)
//    {
//        printf("#\n");
//    }
//    else
//    {
//        for (int i = 1; i < times + 1; i++)
//        {
//            for (int j = 0; j < times - i; j++)
//            {
//                printf(" ");
//            }
//            for (int k = 0; k < i; k++)
//            {
//                printf("#");
//            }
//            printf("\n");
//        }
//    }
//}

int main(void)
{
    int times;
    do
    {
        times = get_int("Height: ");
    }
    while (times < 1 || times > 8);
    if (times == 1)
    {
        printf("#  #\n");
    }
    else
    {
        for (int i = 1; i < times + 1; i++)
        {
            for (int j = 0; j < times - i; j++)
            {
                printf(" ");
            }
            for (int k = 0; k < i; k++)
            {
                printf("#");
            }
            printf("  ");

            for (int n = 0; n < i; n++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
}
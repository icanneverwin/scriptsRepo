#include <stdio.h>
#include <cs50.h>
#include <string.h>

//************************//
//* Function Declaration *//
//************************//

int string_to_int(string s);
int check_numeric(string str);
char caesar_alg(int shift, char character);

//************//
//*** MAIN ***//
//************//

int main (int argc, string argv[])
{
    string input_word;
    int i, len;

    //input parameter checks
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    if (string_to_int(argv[1]) < 1)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    if (check_numeric(argv[1]) == 1)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    input_word = get_string("plaintext: ");
    printf("ciphertext: ");
    len = strlen(input_word);
    for (i = 0; i < len; i++)
    {
        //printf("source: %i-%c, dest: %i-%c; ", input_word[i], input_word[i], caesar_alg(argc, input_word[i]), caesar_alg(argc, input_word[i]) );
        printf("%c", caesar_alg(string_to_int(argv[1]), input_word[i]));
    }
    printf("\n");
}

int string_to_int(string str)
{
    int i, len;
    int result = 0;

    len = strlen(str);

    for (i = 0; i < len; i++)
    {
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

int check_numeric(string str)
{
    int i, len, cnt_check;
    cnt_check = 0;
    len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] < 48 || str[i] > 57)
        {
            cnt_check += 1;
        }
    }
    if (cnt_check == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

char caesar_alg(int shift, char character)
{
    int temp_val = 0;
    shift = shift % 26;
    if (character >= 65 && character <= 90)
    {
        if (character + shift > 90)
        {
            temp_val = shift - (90 - character);
            character = 64 + temp_val;
        }
        else
        {
            character = character + shift;
        }
    }
    else if (character >= 97 && character <= 122)
    {
        if (character + shift > 122)
        {
            temp_val = shift - (122 - character);
            character = 96 + temp_val;
        }
        else
        {
            character = character + shift;
        }
    }
    return character;
}

//string caesar_alg(int shift, string words)
//{
//    int i, len;
//    len = strlen(words);
//    shift = shift % 26;
//
//    for (i = 0; i < len; i++)
//    {
//        int temp_val = 0;
//        // go through upper case
//        if (words[i] >= 65 && words[i] <= 90)
//        {
//            if (words[i] + shift > 90)
//            {
//                temp_val = shift - (90 - words[i]);
//                words[i] = 64 + temp_val;
//
//            }
//            else
//            {
//                words[i] = words[i] + shift;
//            }
//        }
//        // go through lower case
//        else if (words[i] >= 97 && words[i] <= 122)
//        {
//            if (words[i] + shift > 122)
//            {
//                temp_val = shift - (122 - words[i]);
//                words[i] = 96 + temp_val;
//            }
//            else
//            {
//                words[i] = words[i] + shift;
//            }
//        }
//    }
//    return words;
//}
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//************************//
//* Function Declaration *//
//************************//

int check_alphabet(string str);
int check_char(string key);
char get_subs_char(char character, string cipher);

//************//
//*** MAIN ***//
//************//

int main(int argc, string argv[])
{
    int i, len_argv, len_input;
    string input_words;

    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    len_argv = strlen(argv[1]);
    if (len_argv != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (check_alphabet(argv[1]) == 1)
    {
        printf("Key must contain only alphabetic characters\n");
        return 1;
    }
    //validation per each character
    if (check_char(argv[1]) == 1)
    {
        printf("Key must not contain repeatable characters\n");
        return 1;
    }


    input_words = get_string("plaintext: ");
    len_input = strlen(input_words);

    printf("ciphertext: ");

    for (i = 0; i < len_input; i++)
    {
        printf("%c", get_subs_char(input_words[i], argv[1]));
    }
    printf("\n");
}

int check_alphabet(string str)
{
    int i, len, cnt_check;
    cnt_check = 0;
    len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if ((str[i] < 65 || str[i] > 90) && (str[i] < 97 || str[i] > 122))
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

int check_char(string key)
{
    int i, j, len, dist_count;
    len = strlen(key);
    dist_count = 0;

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < len; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                dist_count += 1;
            }
        }
    }
    if (dist_count == 26)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


char get_subs_char(char character, string cipher)
{
    int cur_pos;
    //char out_char;

    if ((character >= 65 && character <= 90) || (character >= 97 && character <= 122))
    {
        if (isupper(character) == 0) //lowercase
        {
            cur_pos = character - 97;
            //out_char = cipher[cur_pos];
            return tolower(cipher[cur_pos]);
        }
        else //uppercase
        {
            cur_pos = character - 65;
            return toupper(cipher[cur_pos]);
        }
    }
    else
    {
        return character;
    }
}


//string substitute_string(string user_input)
//{
//    int i, len, lower_count, upper_count;
//    len = strlen(user_input);
//    lower_count = 97;
//    upper_count = 65;
//
//    for (i = 0; i < len; i++)
//    {
//        if (user_input[i] >= 65 && user_input[i] <= 90)
//        {
//
//        }
//        else if (user_input[i] >= 97 && user_input[i] <= 122)
//        {
//
//        }
//    }
//}


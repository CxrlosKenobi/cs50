#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    float letters = 0;
    float words = 1;
    float sentences = 0;
    int index;

    string text = get_string("Text: ");

//Here we count the letters in the string
    for(int i = 0; i < strlen(text); i++)
    {
        if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
//Here we count the words in the string
        if(text[i] == ' ')
        {
            words++;
        }
//Here we count the sentences in the string
        if(text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

//Finally calculate the index
    index = round((0.0588 * (letters/words*100)) - (0.296 * (sentences/words*100)) - 15.8);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n",index);
    }
}

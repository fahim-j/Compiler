#include <stdio.h>
#include <string.h>

int main() 
{
    char line[500];
    char code[500] = {0};
    int singleComment = 0, multiComment = 0;

    while (1) //eof
    {
        fgets(line, sizeof(line), stdin);

        if (strncmp(line, "END", 3) == 0)
            break;

        strcat(code, line);
    }

   
    int len = strlen(code);

    int i = 0;
    while (i < len) 
    {
        // ---------- Single-line comment ----------
        if (code[i] == '/' && code[i+1] == '/') 
        {
            singleComment++;
            i += 2;
            while (i < len && code[i] != '\n') 
            {
                i++;
            }
        }
        // ---------- Multi-line comment ----------
        else if (code[i] == '/' && code[i+1] == '*') 
        {
            multiComment++;
            i += 2;
            while (i < len && !(code[i] == '*' && code[i+1] == '/'))
            {
                i++;
            }
            i += 2; // Skip '*/'
        }
        // ---------- Whitespace skip ----------
        else if (code[i] == ' ' || code[i] == '\t' || code[i] == '\n') 
        {
            i++;
        }
        // ---------- Normal characters ----------
        else 
        {
            putchar(code[i]);
            i++;
        }
    }
    printf("\n");
    printf("Single-line comments: %d\n", singleComment);
    printf("Multi-line comments : %d\n", multiComment);

    return 0;
}

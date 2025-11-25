#include <stdio.h>
#include <string.h>

char *keywords[] = {"if", "else", "while", "for", "int", "float", "return"};
int keywordCount = 7;

int Letter(char c) 
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int Digit(char c)
{
    return (c >= '0' && c <= '9');
}

int AlphaNum(char c) 
{
    return Letter(c) || Digit(c);
}

int Keyword(char *str) 
{
    for (int i = 0; i < keywordCount; i++)
        if (strcmp(str, keywords[i]) == 0) 
            return 1;
    return 0;
}

int Identifier(char *str) 
{
    if (!Letter(str[0]) && str[0] != '_') 
        return 0;
    for (int i = 1; str[i] != '\0'; i++)
        if (!AlphaNum(str[i]) && str[i] != '_') 
            return 0;
    return 1;
}

int Integer(char *str) 
{
    int i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!Digit(str[i])) 
        return 0;
    for (; str[i] != '\0'; i++)
        if (!Digit(str[i])) 
            return 0;
    return 1;
}

int Float(char *str) 
{
    int i = 0, dot = 0;
    if (str[i] == '+' || str[i] == '-') 
        i++;
    for (; str[i] != '\0'; i++) 
    {
        if (str[i] == '.') 
        {
            if (dot) 
                return 0;
            dot = 1;
        } 
        else if (!Digit(str[i])) 
            return 0;
    }
    return dot == 1;
}

int Operator(char *str) 
{
    char *ops[] = {"+","-","*","/","=","==","!=","<",">","<=",">=",";","(",")","{","}"};
    int total = 16;
    for (int i = 0; i < total; i++)
        if (strcmp(str, ops[i]) == 0) 
            return 1;
    return 0;
}

int Space(char c) 
{
    return c == ' ' || c == '\t' || c == '\n';
}

int main() 
{
    char input[1000];
    char token[100];
    int i = 0;

    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0') {
        int j = 0;

        // Skip whitespace
        if (Space(input[i])) { i++; continue; }

        // Multi-character operators
        if ((input[i]=='=' && input[i+1]=='=') ||
            (input[i]=='!' && input[i+1]=='=') ||
            (input[i]=='<' && input[i+1]=='=') ||
            (input[i]=='>' && input[i+1]=='=')) 
                {
                    token[j++] = input[i++];
                    token[j++] = input[i++];
                    token[j] = '\0';
                }
        // Single-character operators
        else if (strchr("+-*/=<>(){};", input[i])) 
        {
            token[j++] = input[i++];
            token[j] = '\0';
        }
        // Word or number
        else 
        {
            while (input[i] != '\0' && !Space(input[i]) && !strchr("+-*/=<>(){};", input[i])) 
            {
                token[j++] = input[i++];
            }
            token[j] = '\0';
        }

        // Classification
        if (Keyword(token)) 
            printf("%s → Keyword\n", token);
        else if (Identifier(token)) 
            printf("%s → Identifier\n", token);
        else if (Integer(token)) 
            printf("%s → Integer\n", token);
        else if (Float(token)) 
            printf("%s → Float\n", token);
        else if (Operator(token)) 
            printf("%s → Operator\n", token);
        else 
            printf("%s → Constant\n", token);
    }

    return 0;
}

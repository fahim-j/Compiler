#include <stdio.h>
#include <string.h>

char *keywords[] = {"if", "else", "while", "for", "int", "float", "return"};
//int keywordCount = 7;

int Keyword(char *str) 
{
    for (int i = 0; i < 7; i++)
        if (strcmp(str, keywords[i]) == 0) 
            return 1;
    return 0;
}

// int Identifier(char *str) 
// {
//     if (!((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z') || str[0] == '_'))
//         return 0;
//     for (int i = 1; str[i] != '\0'; i++)
//         if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || 
//               (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
//             return 0;
//     return 1;
// }
int Identifier(char *str) 
{
    // Check first character
    if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z') || str[0] == '_')
    {
        // Check remaining characters
        for (int i = 1; str[i] != '\0'; i++)
        {
            if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || 
                (str[i] >= '0' && str[i] <= '9') || str[i] == '_')
            {
                continue; // valid character, keep checking
            }
            else
            {
                return 0; // invalid character found
            }
        }
        return 1; // all characters valid
    }
    else
    {
        return 0; // first character invalid
    }
}

// int Integer(char *str) 
// {
//     int i = 0;
//     if (str[i] == '+' || str[i] == '-')
//         i++;
//     // if (!(str[i] >= '0' && str[i] <= '9'))
//     //     return 0;
//     for (; str[i] != '\0'; i++)
//         if (!(str[i] >= '0' && str[i] <= '9'))
//             return 0;
//     return 1;
// }
int Integer(char *str) 
{
    int i = 0;

    // Skip optional sign
    if (str[i] == '+' || str[i] == '-')
        i++;

    // Make sure at least one digit exists
    if (str[i] >= '0' && str[i] <= '9')
    {
        // Check remaining characters
        for (; str[i] != '\0'; i++)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                continue; // valid digit
            }
            else
            {
                return 0; // invalid character found
            }
        }
        return 1; // all characters valid digits
    }
    else
    {
        return 0; // first character after optional sign is not a digit
    }
}


// int Float(char *str) 
// {
//     int i = 0, dot = 0;
//     if (str[i] == '+' || str[i] == '-') 
//         i++;
//     for (; str[i] != '\0'; i++) 
//     {
//         if (str[i] == '.') 
//         {
//             if (dot) 
//                 return 0;
//             dot = 1;
//         } 
//         else if (!(str[i] >= '0' && str[i] <= '9')) 
//             return 0;
//     }
//     return dot == 1;
// }

int Float(char *str) 
{
    int i = 0, dot = 0;

    // Skip optional sign
    if (str[i] == '+' || str[i] == '-')
        i++;

    // At least one digit or dot must exist
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
    {
        for (; str[i] != '\0'; i++)
        {
            if (str[i] == '.')
            {
                if (dot == 0)
                {
                    dot = 1; // first dot is allowed
                }
                else
                {
                    return 0; // second dot → invalid
                }
            }
            else if (str[i] >= '0' && str[i] <= '9')
            {
                continue; // valid digit
            }
            else
            {
                return 0; // invalid character
            }
        }

        // Must have exactly one dot to be a float
        if (dot == 1)
            return 1;
        else
            return 0;
    }
    else
    {
        return 0; // first character after sign is neither digit nor dot
    }
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

int main() 
{
    char input[1000];
    char token[100];
    
    fgets(input, sizeof(input), stdin);

    int i = 0;
    while (input[i] != '\0') 
    {
        int j = 0;

        // Skip whitespace directly
        while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') 
            i++;

        if (input[i] == '\0') 
            break;

        // Multi-character operators
        if ((input[i]=='=' && input[i+1]=='=') || (input[i]=='!' && input[i+1]=='=') ||
            (input[i]=='<' && input[i+1]=='=') || (input[i]=='>' && input[i+1]=='=')) 
        {
            token[j++] = input[i++];
            token[j++] = input[i++];
            token[j] = '\0';
        }
        // Single-character operators
        else if (input[i]=='+' || input[i]=='-' || input[i]=='*' || input[i]=='/' || 
                 input[i]=='=' || input[i]=='<' || input[i]=='>' || input[i]==';' || 
                 input[i]=='(' || input[i]==')' || input[i]=='{' || input[i]=='}') 
        {
            token[j++] = input[i++];
            token[j] = '\0';
        }
        // Word or number
        else 
        {
            while (input[i] != '\0' && input[i] != ' ' && input[i] != '\t' && input[i] != '\n' &&
                   input[i]!='+' && input[i]!='-' && input[i]!='*' && input[i]!='/' &&
                   input[i]!='=' && input[i]!='<' && input[i]!='>' &&
                   input[i]!=';' && input[i]!='(' && input[i]!=')' &&
                   input[i]!='{' && input[i]!='}') 
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

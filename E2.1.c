#include<stdio.h>
#include<string.h>
int main()
{
    char a[100],b[100];
    int count=0;
    fgets(a, sizeof(a), stdin);

    float vowel=0, consonant=0, digit=0, special=0;
    int vowelCount[5]={0}; // a, e, i, o, u

    for (int i=0; a[i]!='\0'; i++)
    {
        if(a[i]>='0' && a[i]<='9')
        {
            digit++;
        }
        else if(a[i]=='A'||a[i]=='a'||a[i]=='E'||a[i]=='e'||a[i]=='I'||a[i]=='i'||
                a[i]=='O'||a[i]=='o'||a[i]=='U'||a[i]=='u')
        {
            vowel++;
            b[count++] = a[i];

            if(a[i]=='A'||a[i]=='a')      vowelCount[0]++;
            else if(a[i]=='E'||a[i]=='e') vowelCount[1]++;
            else if(a[i]=='I'||a[i]=='i') vowelCount[2]++;
            else if(a[i]=='O'||a[i]=='o') vowelCount[3]++;
            else if(a[i]=='U'||a[i]=='u') vowelCount[4]++;
        }
        else if((a[i]>='A' && a[i]<='Z') || (a[i]>='a' && a[i]<='z'))
        {
            consonant++;
        }
        else
        {
            special++;
        }
    }

    int len=strlen(a);
    printf("len:%d\n", len);
    printf("Vowel=%d\n", vowel);
    printf("Consonant=%d\n", consonant);
    printf("Digit=%d\n", digit);
    printf("Special=%d\n", special);
    printf("\n");

    printf("V:%.2f\n", (vowel*100)/len);
    printf("C:%.2f\n", (consonant*100)/len);
    printf("D:%.2f\n", (digit*100)/len);
    printf("S:%.2f\n", (special*100)/len);

    // Find the vowel with maximum occurrence
    char vowelList[5] = {'a','e','i','o','u'};
    int maxIndex = 0;
    for(int i=1; i<5; i++)
    {
        if(vowelCount[i] > vowelCount[maxIndex])
            maxIndex = i;
    }
    printf("\nMost Frequent Vowel: %c (%d times)\n", vowelList[maxIndex], vowelCount[maxIndex]);

    printf("%s\n", b);

    return 0;
}

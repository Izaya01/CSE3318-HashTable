#include <stdio.h>
#include <string.h>

#define HASHTABLESIZE 10

int MyHashFunction(char*key)
{
    unsigned int hash = 0;

    while (*key)
    {
        hash = hash *31 + (unsigned char)(*key);
        key++;
    }
    return hash % HASHTABLESIZE;
}

int main(void)
{
    char HashValue[100];

    printf("Enter value: ");
    fgets(HashValue, sizeof(HashValue),stdin);

    HashValue[strcspn(HashValue,"\n")] = '\0';

    printf("The hash value for %s is %d\n", HashValue, MyHashFunction(HashValue));

    return 0;
}
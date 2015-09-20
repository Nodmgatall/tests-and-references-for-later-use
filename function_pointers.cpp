#include <stdio.h>
#include <string.h>

void hello_world()
{
    printf("Hello World");
    printf("\n");
}

void another(const char *cstring)
{
    printf("%s",cstring);
}
int main()
{
    void (*fp1)(const char*);
    void (*fp2)(void);
    fp1 = another;
    fp2 = hello_world;
    fp1("TEST");
    fp2();
    return 0;
}

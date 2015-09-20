#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * append(const char* str1, const char* str2)
{
    int i = strlen(str1) + strlen(str2) + 1;
    char *test = (char*)calloc(i, sizeof(char));
    printf("%d\n",i);
    strcpy(test, str1);
    strcat(test, str2);
    strcat(test,"\n");
    return test;
}
int main()
{
    const char *test_string = "Welt";
    const char *test = "Hallo ";
    const char *ret_val = append(test, test_string);
    const char *equalq = "Hallo Welt";
    if(strcmp(ret_val, equalq))
    {
        puts("ITS TRUE");
    }
    printf("%s", ret_val);
    return 1;

}

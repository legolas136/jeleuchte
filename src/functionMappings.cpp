#include "functionMappings.h"

int add(int num1, int num2)
{
    return num1 + num2;
}
int sub(int num1, int num2)
{
    return num1 - num2;
}

std::map<std::string, std::function<int(int, int)>> funcMap =
    {{"add", add},
     {"sub", sub}};

int strToFunc(const char *functionName, int param1, int param2)
{
    return funcMap[functionName](param1, param2);
}

void example()
{
    strToFunc("add", 2, 2);
}
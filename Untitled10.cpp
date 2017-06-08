
#include <stdio.h>

#define DEBUG(...) { __VA_ARGS__ ;}

int main()
    {
    int i = 0;

    DEBUG (printf ("meow!"));

    return i;
    }

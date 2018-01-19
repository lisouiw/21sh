#include "../twenty.h"

int     if_only(char *s, char c)
{
    while (s && *s == c)
        ++s;
    if (!(*s))
        return (1);
    return (0);
}
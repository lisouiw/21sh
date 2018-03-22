#include "../twenty.h"

void    aggregation_out(char *t)
{
    if (t[2] == '\0')
        isnumber(t[1]) ? dup2(ft_atoi(t[1]), 1) : parsing_dup_out(t[1], 1, ex);
    else
        isnumber(t[2]) ? dup2(ft_atoi(t[2]), ft_atoi(t[0])) : parsing_dup_out(t[2], ft_atoi(t[0]), ex);
    
        // dup2(1,2);
    // // dup2(isnumber(spl[2]) ? ft_atoi(spl[2]) : parsing_dup_(spl[2]), ft_atoi(spl[0]));
    // free_tab(spl);
}

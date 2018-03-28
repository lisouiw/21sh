#include "../twenty.h"

void    aggregation_out(char **t, t_cmd *ex)
{
    if (t[2] == '\0')
        isnumber(t[1]) ? dup2(ft_atoi(t[1]), 1) : parsing_dup_out(t[1], 1, ex);
    else
        isnumber(t[2]) ? dup2(ft_atoi(t[2]), ft_atoi(t[0])) : parsing_dup_out(t[2], ft_atoi(t[0]), ex);
    free_tab(t);
}




void    aggregation_in(char **t, t_cmd *ex)
{
    // spl = ft_strsplit(ex->cmd, ' ');
    if (t[2] == '\0')
        isnumber(t[1]) ? dup2(0, ft_atoi(t[1])) : parsing_dup_in(t[1], 0, ex);
    else
        isnumber(t[2]) ? dup2(ft_atoi(t[0]), ft_atoi(t[2])) : parsing_dup_in(t[2], ft_atoi(t[0]), ex);
    free_tab(t);
}







//=======OUT===============
// spl = ft_strsplit(ex->cmd, ' ');
// if (spl[2] == '\0')
//     isnumber(spl[1]) ? dup2(ft_atoi(spl[1]), 1) : parsing_dup_out(spl[1], 1, ex);
// else
//     isnumber(spl[2]) ? dup2(ft_atoi(spl[2]), ft_atoi(spl[0])) : parsing_dup_out(spl[2], ft_atoi(spl[0]), ex);
// free(spl);

//==========IN============
// spl = ft_strsplit(ex->cmd, ' ');
// if (spl[2] == '\0')
//     isnumber(spl[1]) ? dup2(0, ft_atoi(spl[1])) : parsing_dup_in(spl[1], 0, ex);
// else
//     isnumber(spl[2]) ? dup2(ft_atoi(spl[0]), ft_atoi(spl[2])) : parsing_dup_in(spl[2], ft_atoi(spl[0]), ex);
// ree_tab(spl);
#include "../twenty.h"

int         main(void)
{
    t_froz  *fz;
    t_env   *env;
    t_edit  *ed;
    t_his   *hs;

    init_shell(&fz, &env, &ed, &hs);
    while (42)
    {
        read(0, &fz->buf, 4);
        printf("%i %i %i\n", fz->buf[0], fz->buf[1], fz->buf[2]);
        if (fz->buf[0] == 10)
            ;
        // env = treat_cmd();
        else
            ed = touch(ed, fz);
        init_data(&fz);
    }
}

void        init_shell(t_froz **fz, t_env **env, t_edit **ed, t_his **hs)
{
    set_up_term();
    *env = give_env(NULL);
    *ed = init_edit(NULL);
    *fz = init_fz(NULL);
    *hs = NULL;
}

t_froz      *init_fz(t_froz *fz)
{
    if (!(fz = (t_froz*)malloc(sizeof(t_froz))))
        return (NULL);
    fz->buf[0] = 0;
    fz->buf[1] = 0;
    fz->buf[2] = 0;
    return (fz);
}

void    init_data(t_froz **fz)
{
    (*fz)->buf[0] = 0;
    (*fz)->buf[1] = 0;
    (*fz)->buf[2] = 0;
}
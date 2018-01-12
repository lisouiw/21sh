#include "../twenty.h"

t_edit  *touch(t_edit *ed, t_froz *fz)
{
    if (fz->buf[1] == 0 && fz->buf[2] == 0)
    {
        if (fz->buf[0] > 0 && fz->buf[0] < 27)
            ed = ctrl_touch();
        else if (ccp->buf[0] == 127)
            ed = delete_ed();
        else
            ed = add_ed();
    }
    else
        ed = extern_touch();
    return (ed);
}
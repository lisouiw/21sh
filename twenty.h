#ifndef TWENTY_H
# define TWENTY_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>

///GLOBALE

struct termios		term;

typedef struct		s_num
{
	int				tb[3];
}					t_num;
t_num	*g_nb;

t_num	*g_nb;


///

typedef struct      s_froz
{
    int             mode[3];
    char            buf[3];
    char            *paste;
    char            *cmd;
}                   t_froz;

typedef struct		s_env
{
	char			*name;
	char			*ctn;
	struct s_env	*next;
}					t_env;

typedef struct      s_edit
{
    int             rpz[5];
    char            c[1];
    struct  s_edit  *next;
    struct  s_edit  *prev;
}                   t_edit;

typedef struct      s_his
{
    char            *cmd;
    struct  t_edit  *ed;
    struct  s_his   *next;
    struct  s_his   *prev;
}                   t_his;    

// main
t_num   *init_shell(t_froz **fz, t_env **env, t_edit **ed, t_his **hs);
t_froz      *init_fz(t_froz *fz);
void    init_data(t_froz **fz);

// term
int		init(void);
int		set_up_term(void);

//env
void	free_elem(t_env *tmp);
void	b_export(char *cut, t_env **env);
void	b_unset(char **cut, t_env **env, int i);
t_env	*add_env(char *environ, t_env *env, size_t one, size_t all);
t_env	*give_env(t_env *env);

//ed
void    modif_edit(t_edit **ed, t_edit **nw);
t_edit  *add_ed(t_edit *ed, char c, t_edit *nw);
t_edit  *init_edit(t_edit *init);
t_edit  *erase_ed(t_edit *ed);

//touch
t_edit  *touch(t_edit *ed, t_froz *fz);
t_edit  *ctrl_touch(t_edit *ed, t_froz *fz, char c);
t_edit  *extern_touch(t_edit *ed, t_froz *fz);

//print_shell
int		ft_put(int c);
void	my_tputs(t_edit *ed);
void    print_shell(t_edit *ed);
void	put_cursor(t_edit *ed);
void    init_cursor(t_edit *ed);
void	save_init(t_edit *ed);


#endif

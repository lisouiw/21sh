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

///

typedef struct      s_froz
{
    int             mode[4];
    //mode 0        copier
    //mode 1        couper
    //mode 2        histo
    //mode 3        // regular  0
                    // quote    1
                    // dquote   2
                    // pipe     3
                    // cmdand   4
                    // cmdor    5
                    // heredoc  6
    char            buf[3]; // buffer pour lire le char tape
    char            *paste; // la chaine a coller
    char            *cmd; // keep cmd car imcomplete
    int             nb[1]; // last position
}                   t_froz;

typedef struct		s_env
{
	char			*name;
	char			*ctn;
	struct s_env	*next;
}					t_env;

typedef struct      s_edit
{
    int             rpz[4];
    // 0: debut list
    // 1: fin list
    // 2: cursor position
    // 3: placement
    // 4: 
    char            c[1];
    struct  s_edit  *next;
    struct  s_edit  *prev;
}                   t_edit;

typedef struct      s_his
{
    char            *cmd;
    struct  s_his   *next;
    struct  s_his   *prev;
}                   t_his;    


//ctrl 
void    ctrl_de_test(t_edit *ed, t_froz *fz, char c, t_his *hs);
t_edit  *ctrl_touch(t_edit *ed, t_froz *fz, char c, t_his *hs);
t_edit  *move_word(t_edit *ed, char c);
t_edit  *up_down(t_edit *ed, char c);
t_edit  *home_end(t_edit *ed, char c, t_froz *fz);

//ed
void    modif_edit(t_edit **ed, t_edit **nw);
t_edit  *add_ed(t_edit *ed, char c, t_edit *nw);
t_edit  *init_edit(t_edit *init);
t_edit  *erase_ed(t_edit *ed);
// void    free_ed(t_edit **ed);
void    free_ed(t_edit **ed, t_froz *fz);

//env
void	free_elem(t_env *tmp);
void	b_export(char *cut, t_env **env);
void	b_unset(char **cut, t_env **env, int i);
t_env	*add_env(char *environ, t_env *env, size_t one, size_t all);
t_env	*give_env(t_env *env);

// exec
int		give_path(t_env *env, char **cut, int i, char **tab_env);
char	**list_to_tab(t_env *env, char **tab_env);
void	b_other(char **cut, t_env *env);
void	print_tab(char **ta, int i);

//giv_info
char    *ed_str(t_edit *cmd, char *s, int nb);

// init
t_num   *init_shell(t_froz **fz, t_env **env, t_edit **ed, t_his **hs);
t_froz  *init_fz(t_froz *fz);
void    init_data(t_froz **fz);
t_his   *init_hs(t_his *hs, t_his *next);
void    init_for_new(t_his **hs, t_froz **fz, t_edit **ed);

// main
void    cursor_end(t_edit *ed);

// parsing
int     parsing(t_edit *ed, t_froz **fz);


// print_shell
int		ft_put(int c);
void	my_tputs(t_edit *ed);
void	put_cursor(t_edit *ed);
// void	save_init(t_froz *fz);
void	save_init(t_edit *ed);
void    print_shell(t_edit *ed, t_froz *fz);

//prompt
void    put_prompt(t_froz *fz);
void    put_prompt_init(t_froz **fz);
int     giv_last(t_froz *fz);

// t 
void	free_list(t_env **env);
char	*t_strjoin(char *f, char *s, char *t);
void	free_tab(char **array);
int		free_for_exit(char *line, char **cut, t_env *env);

// term
int 		init(void);
int		set_up_term(void);

// tools
int     if_only(char *s, char c);

// touch
t_edit  *touch(t_edit *ed, t_froz **fz, t_his **hs);
t_edit  *extern_touch(t_edit *ed, t_froz **fz, t_his **hs);
t_edit  *left_right(t_edit *ed, t_froz *fz);
t_his   *histo(t_his *hs, char c, t_edit **ed, t_froz **fz);


// treatmt
t_env   *treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz);
t_env   *launchcmd(t_his **cmd, t_env *env);
t_env	*exec_giv(char *line, t_env *env, char **cut, int *i);
int     add_his(t_edit *cmd, t_his **hs, t_his *nw, t_froz *fz);

t_edit  *giv_position(t_edit *ed, int i);

#endif

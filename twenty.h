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
# include <dirent.h>
# include <limits.h>


void	sig_child(int sig);



#include <sys/types.h>
#include <sys/wait.h>

///GLOBALE
struct  s_his       *hs;
struct  termios		term;
struct  s_froz       *fz;
struct  s_edit      *ed;

typedef struct		s_num
{
	int				tb[3];
}					t_num;
t_num	*g_nb;

///

typedef struct      s_here
{
    char            *delim;
    char            *doc;
    int             ok[2];
    struct  s_here  *next;
    struct  s_here  *prev;
}                   t_here;

typedef struct      s_froz
{
    int             mode[4];
    //mode 0        copier
    //mode 1        couper
    //mode 2        histo
    //mode 3        prompt
        
    char            buf[3]; // buffer pour lire le char tape
    char            *paste; // la chaine a coller
    char            *cmd; // keep cmd car imcomplete
    // char            *cmd; // keep cmd car imcomplete
    int             nb[1]; // last position
    struct  s_here  *here;
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
    // 0: debut list
    // 1: fin list
    // 2: cursor position
    // 3: placement
    // 4: copier/ coller
    char            c[1];
    struct  s_edit  *next;
    struct  s_edit  *prev;
}                   t_edit;

typedef struct      s_his
{
    char            *cmd;
    // char            *cmd;
    struct  s_his   *next;
    struct  s_his   *prev;
}                   t_his;

typedef struct      s_cmd
{
    char            *cmd;
    int             type;   //cmd : 0
                            //ctrl op : 1
                            //=======
                            // quote    1
                            // dquote   2
                            // pipe     3
                            // cmdand   4
                            // cmdor    5
                            // heredoc  6
                            // Redirecting Input    7 ([n]<word)
                            // Redirecting Output   8 ([n]>word)
                            // Appending Redirected Output  9 ([n]>>word)
                            // Redirecting Standard Output and Standard Error [n]>&word)  10
                            // Duplicating File Descriptors 11 ([n]<&word   
                            // Moving File Descriptors  12 (n]<&digit-   [n]>&digit-)
                            // ;            s13
                            // only \n      14
                            // annule       15
    int             start; //index where the string were sub
    struct  s_cmd   *next;
    struct  s_cmd   *prev;
}                   t_cmd;

typedef struct      s_exec
{
    int             p[2];
    int             in;
    int             out;
    int             ok; // por les || , &&
    int             cmd;
}                   t_exec;

typedef struct      s_proc
{
    pid_t           pid;
    struct  s_proc  *next;
}                   t_proc;

typedef struct      s_varq
{
    char            *cmd;
    struct  s_varq  *next;
}                   t_varq;

// cd
void	cd_prev(t_env **env, char *buf);
void	cd_home(t_env **env, char *buf);
void	cd_name(t_env **env, char *cd, char *user, char *buf);
void	cd_simple(t_env **env, char *cd, char *buf, char *real);
void	b_cd(char *cd, t_env **env);

//  ctrl 
void    ctrl_touch(t_edit **ed, t_froz **fz, char c, t_his *hs);
void    ctrl_de_test(t_edit *ed, t_froz *fz, char c, t_his *hs);
t_edit  *move_word(t_edit *ed, char c);
t_edit  *up_down(t_edit *ed, char c);
t_edit  *home_end(t_edit *ed, char c, t_froz *fz);

//ed
void    modif_edit(t_edit **ed, t_edit **nw);
t_edit  *init_edit(t_edit *init);
t_edit  *erase_ed(t_edit *ed);
t_edit  *add_ed(t_edit *ed, char c, t_edit *nw, t_froz **t_froz);
void    free_ed(t_edit **ed, t_froz *fz);

//env
void	free_elem(t_env *tmp);
void	b_export(char *cut, t_env **env);
void	b_unset(char **cut, t_env **env, int i);
t_env	*add_env(char *environ, t_env *env, size_t one, size_t all);
t_env	*give_env(t_env *env);

//exec_tools
int		give_path(t_env *env, char **cut, int i, char **tab_env);
char	**list_to_tab(t_env *env, char **tab_env);
void	print_tab(char **ta, int i);

// exec
void	b_other(char **cut, t_env *env);
void	b_other_nf(char **cut, t_env *env);
int		give_path_nf(t_env *env, char **cut, int i, char **tab_env);

// execution



//free
void    free_ex(t_cmd **ex);
void    free_all_ex(t_cmd **ex);
void    free_pid_loop(t_proc *p, int i);
int    free_kill(t_proc **p);

//giv_str
char    *join_cmd_nw(char *cmd, t_edit *ed, t_froz *fz);
char    *ed_str(t_edit *cmd, char *s, int nb);
char    *join_cmd(char *cmd, t_edit *ed, t_froz *fz);

//heredoc
// void    add_here(t_froz *fz, char *s);
void    add_here(t_froz *fz, t_cmd *ex);



// init
t_num   *init_shell(t_froz **fz, t_env **env, t_edit **ed, t_his **hs);
t_froz  *init_fz(t_froz *fz);
void    init_data(t_froz **fz);
t_his   *init_hs(t_his *hs, t_his *next);
void    init_for_new(t_his **hs, t_froz **fz, t_edit **ed);
t_cmd   *init_ex(t_cmd *ex);
void    init_launch(t_exec *dot, t_cmd **ex);

//list_to_array
char    ***list_to_arr(t_cmd *ex, char ***arr, t_cmd *count) ;// prendre en compte les redirection
char    ***list_to_arr_zero(t_cmd **ex, char ****arr, t_cmd *count, int a); // prendre en compte les redirection


// main
void    cursor_end(t_edit *ed);
void    put_my_cur(int nb, char c);



// parsing_tools

int     isnumber(char *s);
void    print_ex(t_cmd *ex);
void    print_ex_up(t_cmd *ex);
int     isnumber_len(char *s);

// parsing_type_fct

t_cmd   *parse_redirec(t_cmd *ex, char *s);
t_cmd   *parse_ampersand(t_cmd *ex);
t_cmd   *parse_great_than(t_cmd *ex, char *s);
t_cmd   *parse_less_than(t_cmd *ex, char *s);
t_cmd   *parse_pipe_or(t_cmd *ex);

// parsing_type

t_cmd   *giv_type(t_cmd *ex, char *s);
t_cmd   *parse_op_int(t_cmd *ex, char *s);
int     parse_type(t_cmd **ex);
int     parse_synthaxe(t_cmd *ex);

// parsing_varq

char    *quote_variable(char *s, t_varq *v, t_env *env);
t_varq  *add_struct_varq(char *s, t_varq *v);
t_varq  *add_varq(char *s, int *i, t_varq *v, t_env *env);
t_varq  *add_varq_loop(char *s, t_varq *v, t_env *env);

// parsing_varq_fct.c
t_varq  *varq_simple_quote(char *s, int *i, t_varq *v);
t_varq  *varq_double_quote(char *s, int *i, t_varq *v, t_env *env);
t_varq  *varq_env(char *s, int *i, t_varq *v, t_env *env);

// parsing_varq_tools.c
void    print_varq(t_varq *tmp);
char    *search_var_env(char *sub, t_env *env);
char    *translate_dquote(char *s, t_env *env);
void    free_varq(t_varq *v);

// parsing
t_cmd   *sub_into_ex(char *s, int i, int in, t_cmd *ex);
t_cmd   *separate_cmd(char *s, int i, int in ,t_cmd *ex);
// int     parsing_op(char *s, t_cmd **ex, t_env *env);
int     parsing_quote(char *s);
int     parsing(t_edit *ed, t_froz *fz, t_cmd **ex, t_env *env);
void    join_redirecting(t_cmd **ex);
int     parsing_op(char *s, t_cmd **ex, t_env *env, t_froz *fz);

// pascutcopy
t_edit  *copy(t_edit *ed, t_froz **fz);
char    *keep_paste(t_edit **ed, char *s);
void    cut(t_edit **ed, t_froz **fz);
t_edit  *paste(t_edit *ed, t_froz **fz);

//  pipe
void       end_pipe(t_cmd **ex, t_exec **s);
int     pipe_on(t_cmd *ex);
t_env   *pipe_fct(t_exec *s, t_cmd **ex, t_env *env);
void    init_proc(t_proc *p);
t_proc  *add_pid(t_proc *p, pid_t pid);

// print_shell
int		ft_put(int c);
void	my_tputs(t_edit *ed, t_froz *fz);
void	put_cursor(t_edit *ed);
void	save_init(t_edit *ed);
void    print_shell(t_edit *ed, t_froz *fz);

//print
void    print_here(t_froz *fz);

//  prompt
void    put_prompt(t_froz *fz);
void    put_prompt_init(t_froz **fz);
int     giv_last(t_froz *fz);



//  redirecting_checking
int     redirection_check_create(t_cmd *ex);
void    redirection_file_create(t_cmd *ex);
int     redirection_file_check(t_cmd *ex);

//  redirecting
char    **give_seven(t_cmd *ex);
void    redirection(t_cmd **ex, t_env **env, t_exec *s);
void    redirection_fork(t_cmd **ex, t_env **env, t_exec *s);
void    redirecting_exec(t_cmd **ex, t_env **env, char **arr);



//  signal
// void	ls_signal(void);
void	sig_int(int sig);
void	sig_quite(int sig);
void	ls_signal(int i);


// t 
void	free_list(t_env **env);
char	*t_strjoin(char *f, char *s, char *t);
void	free_tab(char **array);
int		free_for_exit(char *line, char **cut, t_env *env);

// term
int 	init(void);
int		set_up_term(void);
int		set_up_term_prompt(void);

// tools
int     if_only(char *s, char c);
void	ecriture_info(t_env *lst);
char	*strjoin_free(char *nw, char *sub, int i);
int		white_space(char *s);
int     if_only_i(char *s, char c);


// touch
t_edit  *touch(t_edit **ed, t_froz **fz, t_his **hs);
t_edit  *extern_touch(t_edit *ed, t_froz **fz, t_his **hs);
t_edit  *left_right(t_edit *ed, t_froz *fz);
t_his   *histo(t_his *hs, char c, t_edit **ed, t_froz **fz);
t_edit  *giv_position(t_edit *ed, int i);


// treatmt
t_env   *treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz);
int     add_his(t_his **hs, t_his *nw, t_froz *fz);
t_env   *launchcmd(t_cmd *ex, t_env *env);
t_env	*exec_fct(char **ar, t_env *env);
char    **give_tab(char **ar, t_cmd **ex);
t_env	*exec_fct_nf(char **cut, t_env *env);


// void    redirecting_out_child(t_cmd **ex, t_env **env, int nw, pid_t *pid, t_exec *s);
// void    redirecting_in_child(t_cmd **ex, t_env **env, int nw, pid_t *pid, t_exec *s);



char    *change_w_varq(char *s, t_varq *v);

#endif

    // Redirecting Input 7
        // [n]<word
    // Redirecting Output 8
        // [n]>word
    // Appending Redirected Output 9
        //  [n]>>word
    // Redirecting Standard Output and Standard Error 10
        // &>word      >&word   :   >word 2>&1
    // Here Documents 6
        // <<[-]word
    // Duplicating File Descriptors 11
        // [n]<&word   [n]>&word
    // Moving File Descriptors 12
        // [n]<&digit-   [n]>&digit-
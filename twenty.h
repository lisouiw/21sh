/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:19:17 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 17:13:52 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_H
# define TWENTY_H

# include "libft/libft.h"
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct		s_num
{
	int				tb[3];
}					t_num;

typedef struct		s_here
{
	char			*delim;
	char			*doc;
	int				ok[2];
	struct s_here	*next;
	struct s_here	*prev;
}					t_here;

typedef struct		s_froz
{
	int				mode[4];
	char			buf[3];
	char			*paste;
	char			*cmd;
	int				nb[1];
	struct s_here	*here;
}					t_froz;

typedef struct		s_env
{
	char			*name;
	char			*ctn;
	struct s_env	*next;
}					t_env;

typedef struct		s_edit
{
	int				rpz[5];
	char			c[1];
	struct s_edit	*next;
	struct s_edit	*prev;
}					t_edit;

typedef struct		s_his
{
	char			*cmd;
	struct s_his	*next;
	struct s_his	*prev;
}					t_his;

typedef struct		s_cmd
{
	char			*cmd;
	int				type;
	int				start;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_exec
{
	int				p[2];
	int				in;
	int				out;
	int				err;
	int				ok;
	int				cmd;
}					t_exec;

typedef struct		s_proc
{
	pid_t			pid;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_varq
{
	char			*cmd;
	struct s_varq	*next;
}					t_varq;

struct s_num		*g_nb;
struct s_env		*g_env;
struct s_his		*g_hs;
struct s_froz		*g_fz;
struct s_edit		*g_ed;

int					add_delim(t_froz *g_fz, t_cmd *ex);
void				add_doc_s(t_froz *g_fz, char *s);
int					add_doc(t_froz *g_fz, char *s);
void				aggregation_out(char **t, t_cmd *ex);
void				aggregation_in(char **t, t_cmd *ex);
void				cd_prev(t_env **env, char *buf);
void				cd_home(t_env **env, char *buf);
void				cd_name(t_env **env, char *cd, char *user, char *buf);
void				cd_simple(t_env **env, char *cd, char *buf, char *real);
void				b_cd(char *cd, t_env **env);
void				ctrl_touch(t_edit **ed, t_froz **g_fz, char c);
t_edit				*home_end(t_edit *ed, t_froz *g_fz);
t_edit				*up_down(t_edit *ed, char c);
t_edit				*move_word_right(t_edit *ed);
t_edit				*move_word_left(t_edit *ed);
void				modif_ed_nw(t_edit **ed, t_edit **nw);
void				modif_edit(t_edit **ed, t_edit **nw);
t_edit				*add_ed(t_edit *ed, char c, t_edit *nw, t_froz **g_fz);
t_edit				*init_edit(t_edit *init);
t_edit				*erase_ed(t_edit *ed);
void				b_setenv(char **cut, t_env *env);
void				b_export(char *cut, t_env **env);
void				b_unset(char **cut, t_env **env, int i);
t_env				*add_env(char *environ, t_env *env, size_t one, size_t all);
t_env				*give_env(t_env *env);
void				lst_add_tenv(t_env **alst, t_env *new);
t_env				*t_env_tmp(t_env *env);
int					env_flags_check(char **cut);
void				set_new_env(char **cut, t_env *env, t_exec *s);
void				builtin_env(char **cut, t_env *env, t_exec *s);
int					error_syntax(t_froz *g_fz);
int					give_path(t_env *env, char **cut, int i, char **tab_env);
char				**list_to_tab(t_env *env, char **tab_env);
void				print_tab(char **ta, int i);
t_env				*exec_fct_nf(char **cut, t_env *env, t_cmd **ex, t_exec *s);
t_env				*exec_fct(char **cut, t_env *env, t_exec *s);
void				b_other(char **cut, t_env *env, t_exec *s);
void				b_other_nf(char **cut, t_env *env, t_exec *s);
int					give_path_nf(t_env *env, char **cut, int i, char **tab_env);
void				free_cut1(t_edit **ed, t_edit *tmp);
void				free_cut(t_edit **ed, t_froz *g_fz);
void				free_all_ex(t_cmd **ex);
void				free_init_g_fz(t_froz *g_fz);
void				free_for_hs(void);
void				free_for_exit(void);
void				free_elem(t_env *tmp);
void				free_ed(t_edit **ed, t_froz *g_fz);
void				free_list(t_env **env);
char				*t_strjoin(char *f, char *s, char *t);
void				free_tab(char **array);
char				*ed_str(t_edit *cmd, char *s, int nb);
char				*join_cmd_nw(char *cmd, t_edit *ed, t_froz *g_fz);
char				*join_cmd(char *cmd, t_edit *ed, t_froz *g_fz);
void				malloc_here(t_froz *g_fz);
void				add_here_struct(t_froz *g_fz, char *s);
int					check_struct(t_froz *g_fz);
void				histo_add(t_his *hs, t_edit **ed, t_froz **g_fz);
t_his				*histo(t_his *hs, char c, t_edit **ed, t_froz **g_fz);
t_his				*init_hs(t_his *hs, t_his *next);
t_num				*init_shell(t_froz **g_fz, t_env **env, t_edit **ed,
						t_his **hs);
t_froz				*init_g_fz(t_froz *g_fz);
void				init_data(t_froz **g_fz);
void				init_for_new(t_his **hs, t_froz **g_fz, t_edit **ed);
t_cmd				*init_ex(t_cmd *ex);
void				init_launch(t_exec *dot, t_cmd **ex);
void				join_ex(t_cmd **ex);
void				join_redirecting2(t_cmd **join, t_cmd **ex);
void				join_redirecting(t_cmd **ex);
void				cursor_end(t_edit *ed);
void				put_my_cur(int nb, char c);
int					parse_synthaxe_1(t_cmd *ex);
void				parse_synthaxe_2(t_cmd *ex);
int					parse_synthaxe(t_cmd *ex);
int					isnumber(char *s);
int					isnumber_len(char *s);
t_cmd				*parse_redirec(t_cmd *ex, char *s);
t_cmd				*parse_ampersand(t_cmd *ex);
t_cmd				*parse_great_than(t_cmd *ex, char *s);
t_cmd				*parse_less_than(t_cmd *ex, char *s);
t_cmd				*parse_pipe_or(t_cmd *ex);
t_cmd				*giv_type(t_cmd *ex, char *s);
t_cmd				*parse_op_int(t_cmd *ex, char *s);
int					parse_type(t_cmd **ex);
t_varq				*varq_simple_quote(char *s, int *i, t_varq *v);
t_varq				*varq_double_quote(char *s, int *i, t_varq *v, t_env *env);
t_varq				*varq_env(char *s, int *i, t_varq *v, t_env *env);
int					move_to_put_varq(char *s, int i, int o);
char				*change_w_varq(char *s, t_varq *v, int i, char *nw);
char				*search_var_env(char *sub, t_env *env);
char				*translate_dquote(char *s, t_env *env);
void				free_varq(t_varq *v);
t_varq				*add_struct_varq(char *s, t_varq *v);
t_varq				*add_varq(char *s, int *i, t_varq *v, t_env *env);
t_varq				*add_varq_loop(char *s, t_varq *v, t_env *env);
char				*replace_nwl_spc(char *s);
char				*quote_variable(char *s, t_varq *v, t_env *env);
int					parsing_op(char *s, t_cmd **ex, t_env *env, t_froz *g_fz);
int					parsing_quote(char *s);
int					parsing(t_edit *ed, t_froz *g_fz, t_cmd **ex, t_env *env);
t_edit				*paste(t_edit *ed, t_froz **g_fz);
t_edit				*copy(t_edit *ed, t_froz **g_fz);
void				cut(t_edit **ed, t_froz **g_fz);
int					give_paste_in(t_edit **ed);
char				*keep_paste(t_edit **ed, char *s);
void				end_pipe(t_cmd **ex, t_exec **s, int pp);
int					pipe_on(t_cmd *ex);
void				pipe_exec(t_exec *s, t_cmd **ex, t_env *env, int pp);
t_env				*pipe_fct(t_exec *s, t_cmd **ex, t_env *env);
int					ft_put(int c);
void				my_tputs(t_edit *ed, t_froz *g_fz);
void				print_shell(t_edit *ed, t_froz *g_fz);
void				put_cursor(t_edit *ed);
void				save_init(t_edit *ed);
void				put_prompt_init(t_froz **g_fz);
void				put_prompt(t_froz *g_fz);
int					giv_last(t_froz *g_fz);
int					parsing_dup_out(char *s, int n, t_cmd *ex);
int					parsing_dup_in(char *s, int n, t_cmd *ex);
int					redirection_check_create(t_cmd *ex);
void				redirection_file_create(t_cmd *ex);
int					redirection_file_check(t_cmd *ex);
void				redirection(t_cmd **ex, t_env **env, t_exec *s);
void				redirection_fork(t_cmd **ex, t_env **env, t_exec *s);
char				**give_seven(t_cmd *ex);
void				redirecting_exec(t_cmd **ex, t_env **env, char **arr,
						t_exec *s);
void				sub_into_ex_fct(char *s, int i, int in, t_cmd *ex);
t_cmd				*sub_into_ex(char *s, int i, int in, t_cmd *ex);
t_cmd				*separate_cmd_fct(char *s, int *i, int *in, t_cmd *ex);
t_cmd				*separate_cmd(char *s, int i, int in, t_cmd *ex);
void				sig_int(int sig);
void				sig_int3(int sig);
void				sig_int_here_2(void);
void				sig_int_here(int sig);
void				ls_signal(int i);
int					init(void);
int					set_up_term(void);
int					if_only_i(char *s, char c);
int					if_chr_ex(char *s, char c);
int					if_only(char *s, char c);
void				ecriture_info(t_env *lst);
int					white_space(char *s);
char				*strjoin_free(char *nw, char *sub, int i);
char				*strjoin_free_n(char *nw, char *sub, int i);
void				move_on(t_cmd **ex, int i);
t_edit				*touch(t_edit **ed, t_froz **g_fz, t_his **hs);
t_edit				*extern_touch(t_edit *ed, t_froz **g_fz, t_his **hs);
t_edit				*giv_position(t_edit *ed, int i);
t_edit				*left_right(t_edit *ed, t_froz *g_fz);
int					parsing_op_here(char *s, t_cmd **ex, t_env *env,
						t_froz *g_fz);
int					parsing_here(t_edit *ed, t_froz *g_fz, t_cmd **ex,
						t_env *env);
t_env				*treat_cmd_here(t_env *env, t_edit **cmd, t_his **hs,
						t_froz **g_fz);
t_env				*treat_cmd(t_env *env, t_edit **cmd, t_his **hs,
						t_froz **g_fz);
void				add_his(t_his **hs, t_his *nw, t_froz *g_fz);
void				redirection_no_cmd(t_cmd **ex, t_env **env, t_exec *s);
t_env				*exec_fct_re(t_cmd **ex, t_env *env, t_exec *s);
t_env				*launchcmd(t_cmd *ex, t_env *env);
t_froz				*init_fz(t_froz *fz);
void				free_init_fz(t_froz *fz);

#endif

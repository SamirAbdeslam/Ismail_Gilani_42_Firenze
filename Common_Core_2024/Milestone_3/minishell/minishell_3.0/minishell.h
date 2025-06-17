/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:21:28 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/12 19:31:36 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "my_libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <termios.h>
#include <term.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

extern volatile sig_atomic_t last_signal;

typedef enum
{
    ARGUMENT,
    AMB_REDI,
    PIPE,
    REDI_IN,
    REDI_OUT,
    HERE_DOC,
    APPEND,
}       tok_type;

typedef struct  s_env
{
    char			*e;
    struct s_env	*next;
}               t_env;

typedef struct  s_flist
{
    char            *s;
    bool            x_factor;
    bool            io_bool;
    bool            amb_redi;
    struct s_flist  *next;
}                   t_flist;

typedef struct  s_token
{
    char			*s;
    tok_type		type;
    struct s_token	*next;
	struct s_token	*prev;
}               t_token;

typedef struct s_cmd
{
    t_flist	*files;
    char	**args;
    bool    pipe_out;
    bool    pipe_in;
    int     in_fd;
    int     ou_fd;
    char    *path;
}			t_cmd;

typedef struct  s_data
{
    t_env        *env_data;
    t_cmd       *cmd_arr;
    t_token     *token;
    t_token     *last_token;
    char        *current_path;
    char        *old_path;
    char        *home_path;
    char        *input;
    int         **pipe;
    int         cmd_count;
    int         cmd_name;
    int         status;
    int         st_in;
    int         st_out;
}               t_data;

//cmd_array.c
void    make_cmd_array(t_data *data);
t_cmd    *add_cmd_to_arr(t_data *data);
void    add_files_to_arr(t_cmd *cmd, t_token **head, t_data *data);

//cmd_array_utils.c
void    get_args(t_cmd *cmd, t_token **curr);
void    add_file_node(t_flist **head, char *s, bool x, bool io);
void    remove_two(t_token **head, t_token **t, t_data *data);

//tokenization.c
void    tokenize_input(t_data *data);
void    add_pipe(t_data *data, int *idx);
void    add_redirect(t_data *data, char *s, int *idx, char c);
void    add_argument(t_data *data, char *s, int *idx);
int     argument_len(char *s);

//token_utils.c
void    add_token(char *s, tok_type type, t_data *data);
t_token *token_new(char *content, tok_type type);
tok_type    which_type(char c, int len);

//free_mem.c
void    free_token(t_token *token);
void    free_flist(t_flist *flist);
void    free_cmd_array(t_data *data);
void    free_env(t_env *node);
void    free_pipe(int **pipe, int n);

//utils.c
void    skip_spaces(char *s, int *i);
int is_space(char c);
int parse_syntax_errors(t_token *token);
void    reset_data(t_data *data);
int	is_quoted(char *s, char *to_check);

//print.c
void    print_tokens(t_token *token);
void    print_files(t_flist *list);
void    print_cmd_array(t_data *data);

//here_doc.c
bool    do_here_doc(t_token *tok, t_data *data);
char    *get_lines(char *s, t_data *data);
bool    is_limiter_quoted(char *s);

//expansion.c
char	*get_expanded_var(char *s, int *idx, t_data *data);
void	while_not_var(char *s, char *t, int *i, bool expand);
char *expand_dollar(char *s, t_data *data, bool expand);

//utils_2.c
char    *get_unquoted(char *s);
int len_wo_quotes(char *s);
int parse_quotes(char *input);
int tok_len(t_token *tok);

//manage_expansion.c
void    expand(t_token *tok, t_data *data);
void    tokenize_string(t_token **new, t_token **c, t_data *data);
void    tokenize_dollar(t_token **new, t_token **c, t_token **t, t_data *data);
void    handle_unquoted_expansion(t_token **tok, t_data *data);
void    add_to_token_struct(t_token **tok, t_data *data, t_token *new);

//new_tokens_utils.c
void    add_to_new(t_token **new, t_token **c, t_token **temp);
t_token *create_temp(char *s);
void    add_temp(char *content, t_token **first, tok_type type);
t_token *split_token(char *s);
void    fill_array(char *t, int *i, t_token  **r);

//utils_3.c
bool    is_dollar_quoted(char *s);
char    last_char(char *s);
int count_pieces(char *s);
void    while_string(char *s, int *i);
void    while_var(char *s, int *i);

//execution.c
pid_t    execute(t_cmd cmd, t_data *data);
void    do_execve(t_cmd *cmd, t_data *data);
bool    handle_fds(t_cmd *cmd, t_data *data);
char    *get_path(char *cmd, t_data *data);
void    wait_status(t_data *data, pid_t last_pid);

//fds.c
bool    do_open(t_cmd *cmd, t_data *data);
bool    open_in(t_flist *t, t_cmd *cmd, t_data *data);
bool    open_out(t_flist *t, t_cmd *cmd);
void    set_pipe(t_cmd *cmd, t_data *data);
int     create_temp_file(char *content, t_data *data);

//utils_4.c
char    **ft_matdup(char **mat);
void    free_all(t_data *data, t_cmd *cmd);
void    free_data(t_data *data);
bool    is_in_pipe(int fd, int **pipe, t_data *data);
bool    no_more_input(t_flist *t);
void    create_pipe_arr(t_data *data);

void	handle_sigint(int sig);
char    **copy_env(t_env *env);
char *ft_crazystring(char *s);

// env
t_env   *init_env(char **e, t_data *data);
t_env   *new_env_node(char *s);
char *check_env(t_data *data, char *var);
void update_env(t_data *data, char *var, char *str);
void delete_env(t_data *data, char *var);
void add_env(t_data *data, char *var);
char *get_var_name(char *var);

// builtin
void echo(t_data *data, t_cmd *cmd, char **args);
void cd(t_data *data, t_cmd * cmd, char **args);
void unset(t_data *data, char **var);
void env(t_data *data, t_cmd *cmd, char **input_array);
void pwd(t_data *data, t_cmd *cmd);
void export(t_data *data, char **args);
void exit_shell(t_data *data, t_cmd *cmd);

int	ft_strnncmp(char *s1, char *s2, int n1, int n2);

int define_input(t_data *data, t_cmd *cmd);
#endif
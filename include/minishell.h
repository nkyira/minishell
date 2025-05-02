/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   minishell.h                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/02 17:29:01 by jodavis        #+#    #+#                */
/*   Updated: 2025/05/02 17:29:03 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../printf/ft_printf.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <sys/stat.h>
# include <signal.h>
# include <linux/limits.h>
# define MINISHELL "./minishell"
# define SHELLEVEL "SHLVL"

enum e_type {
	ESPACE=1,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	CMD,
	PIPE,
};

enum e_status_quote {
	DEFAULT,
	SQUOTE,
	DQUOTE
};

typedef struct s_token{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
	int				index;
}	t_token;

typedef struct s_redirect{
	int					type;
	char				*file;
	struct s_redirect	*next;
}	t_redict;

typedef struct s_command{
	char				*command;
	char				**args;
	int					ofile;
	int					infile;
	t_redict			*outfile;
	t_redict			*inputfile;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data{
	int			sortie;
	int			pipefd[2];
	char		**env;
	char		**export;
	char		*input;
	char		oldpwd[PATH_MAX];
	t_token		*token;
	t_command	*command;
	pid_t		pid;
}	t_data;

/*				remplacer des quotes et du dollar	*/
int			replace(t_data *data);
int			init_size_path(char *path, char *str, int *taille, int size_word);
char		*copy_end_line(char *str, char *path, int size_word, char quote);
void		copy_chaine(char *str, char *val, int i, int n);
int			size_path(char *str, char caracter);
int			size_quote(char *str, char character);

/*							quote				*/
char		*replace_with_quote(char	*str, t_data *data,
				int *i, int *status);
char		*replace_quote(char	*str, char quote);

/*							Dollar				*/
char		*search_env(char *str, t_data *data, int n);
char		*replace_path(char *str, int *i, int size_word, t_data *data);
int			position_env(char *str, char **env, int n);

/*						Verification			*/

int			check_tokens(t_token *tokens);
int			quote_error(char *input);

/*						utils					*/
int			set_status(int status, char character);
int			special_character(int caractere);
int			ft_isspace(int c);
int			ft_max(int a, int b);
void		lastadd_command(t_command **command, t_command *newcommand);
void		lastadd_redirect(t_redict **redirect, t_redict *newredirect);
int			is_not_redirection(t_token *token);
void		check_token_again(t_token **token);
int			size_args(t_token *token);
void		lastadd_arg(char **str, char *word);
char		**ft_new_env(char **env, char *str, int *error);
char		**copy_env(char **env);
int			env_parcourt(char *str);
char		*change_var_env(char *str, char *var_env);

/*						parsing					*/
int			parsing_start(t_data *data);
int			separator(t_data *data, char *input, int status);
int			create_commands(t_command **command, t_token *token);
int			infile(t_token *token);
int			outfile(t_token *token);
char		*replace_dollar_squote(char *str, int *i, char quote);

/*					initialisation			*/
t_token		*init_token(int type, char *str, int size);
t_command	*init_args_command(t_command *command, t_token *token);
t_redict	*init_redirect(int type, char *file);
t_command	*init_command(void);
t_command	*init_file(t_command *command, t_token *token);
void		init_data(t_data *data, char *input);
void		lastadd_token(t_token **token, t_token *newtoken);

/*				liberation memoire			*/
void		free_tokens(t_token *token);
void		free_command(t_command *command);
void		free_commands(t_command *command);
void		free_arg(char **str);
void		free_data(t_data *data);
void		ft_exit(t_data *data, int status);
t_token		*free_search_token(t_token *token);

/*					commande					*/
char		*command_path(t_command *command, t_data *data);
int			append(int fd);
int			redirect_infile(int fd);

/*					execution					*/
void		execute(t_data *data);
void		execute_commande(t_data *data, t_command *command);
int			get_children(t_data *data, pid_t pid);
void		parent_process(int *prev_fd, t_data *data, t_command *cmd);
void		child_process(t_command *command, t_data *data, int prev_fd);
void		close_fds_one_builtin(t_command *command,
				int *stdoutfd, int *stdinfd);
void		exe_one_built(t_data *data, t_command *command,
				int *stdi, int *stdo);
int			export(char ***env, char *str);
void		execute_builtin(t_data *data, t_command *command);
/*					DEbug					*/
void		command_not_found(char *command);
int			check_dir(char *path, char *cmd, t_data *data);
int			posix_error(int c);
void		error_tube(void);
void		heredoc_warning(char *str);
void		error_export(char *str);
void		error_fork(t_data *data);
void		no_such_file(char *command);

/*				Signal					*/
void		signals_interactif(void);
void		signals_noninteractif(void);

/*				builtin				*/
int			is_builtin(char *command);
void		exit_builtin(t_data *data, char **argv);
void		pwd_builtin(t_data *data, char **argv);
void		cd_builtin(t_data *data, char **argv);
void		export_builtin(t_data *data, char **argv);
void		echo_builtin(char **argv);
void		unset_builtin(t_data *data, char **argv);
void		env_builtin(t_data *data, char **argv);

#endif

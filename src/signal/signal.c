/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:46:24 by fatsaa-m          #+#    #+#             */
/*   Updated: 2025/04/08 15:46:38 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* ignore_sigquit:
*
*ft_memset remet les bit a zero pour plus de securite
*SIG_INT ignore le signal;
*/
void	ignore_sigquit(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}

/* signal_print_newline:
*	Prints a newline for noninteractive signal handling.
*/
void	signal_print_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}

/* mets une nouvelle ligne avec un nouveau prompt grace a rl_on_new_line()
	reinitialise avec rl_replace_line("",0) 
	puis affiche le prompt avec rl_redisplay()*/

void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* signals_interactive:
*	
	lorsque l'utilisateur est en interaction avec le terminal;
	on ignore la commande ctrl-\ ensuite pour ctrl-D on cree un nouvea
	prompt a la ligne.
	ft_memset remet tous les bits a zero pour plus de securite;
*/
void	signals_interactif(void)
{
	struct sigaction	sig;

	ignore_sigquit();
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &sig, NULL);
}

/* signals_noninteractive:
*	
*	En mode ininteractif donc a l'execution
*	les commandes ctrl-C et ctrl-\ doivent quitter les processus
*	en cours si je peux le dire creer un nouveau prompt a la ligne.
*/
void	signals_noninteractif(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

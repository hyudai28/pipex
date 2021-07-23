#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
//  sig_ign();
//  sig_input();
# define STDERR 2
# define MINISHELL "MINISHELL$" 

void    sig_int_input(void)
{
    ft_putstr_fd("\b\b \b\n", STDERR);
    ft_putstr_fd(MINISHELL, STDERR);
}

void    sig_quit_input(void)
{
    ft_put_str_fd("\b\b \b\b", STDERR);
}

void    sig_input(void)
{
    if (signal(SIGINT, sig_int_input) == SIG_ERR)
    {
        ft_putstr_fd(strerror(errno), STDERR);
        exit(1);
    }
    if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
    {
        ft_putstr_fd(strerror(errno), STDERR);
        exit(1); 
    }
}

void    sig_ign(void)
{
    if (signal(SIGINT, SIG_IGN) == SIG_ERR)
    {
        ft_putstr_fd(strerror(errno), STDERR);
        exit(1);
    }
    if (signal(SIGQUIT, SIG_IGN == SIG_ERR))
    {
        ft_putstr_fd(strerror(errno), STDERR);
        exit(1);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/23 10:21:43 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    (void)envp;
    char *test = "testtest";
    char *two = ft_strdup(test);
    ft_printf("%s\n", two);
    return (0);
}

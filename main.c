/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:03:24 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/23 17:22:07 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include <stdio.h>
/*
char 	*ft_mini_lexer(char **line)
{

}
*/


int main(int argc, char **argv)
{
	int i = 0;
	while (i < argc)
	{
		printf("line[%d]=%s\n", i, argv[i]);
		i++;
	}
}

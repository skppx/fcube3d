/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:33:55 by repinat           #+#    #+#             */
/*   Updated: 2023/02/21 15:29:46 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_p(char *str)
{
	free(str);
	str = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		ft_free_p(tab[i]);
	free(tab);
}
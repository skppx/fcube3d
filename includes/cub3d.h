/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:09:52 by repinat           #+#    #+#             */
/*   Updated: 2023/02/21 15:19:18 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <../minilibx-linux/mlx.h>

typedef struct s_vars	t_vars;

struct s_vars
{
	// textures
	void	*wall_N;
	void	*wall_S;
	void	*wall_E;
	void	*wall_W;
	char	*ground;
	char	*sky;
	//map
	char	**map;
	size_t	size_map;
	int		count_l;
};

int		ft_parsing(int ac, char **av, t_vars *cub);
void	free_tab(char **tab);
// int		map_size(char **av, t_vars *cub);
int		closed_map(char	**map, t_vars *cub);



#endif
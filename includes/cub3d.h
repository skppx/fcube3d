/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:09:52 by repinat           #+#    #+#             */
/*   Updated: 2023/02/09 16:43:17 by repinat          ###   ########.fr       */
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
	void	*ground;
	void	*sky;
	//map
	char	**map;
};

int	ft_parsing_arg(int ac, char **av);


#endif
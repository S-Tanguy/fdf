/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstaes- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:41:21 by tstaes-           #+#    #+#             */
/*   Updated: 2017/04/06 14:31:59 by tstaes-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"
# include <fcntl.h>

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	char	*big_string;
	char	**coord;
	int 	x;
	int 	y;
}				t_env;

int		key_hook(int keycode, t_env *s)
{
	printf("Keycode = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(s->mlx, s->win);
		exit(0);
	}
	ft_putstr("lolilol");
	return (0);
}

void    line(int x0, int y0, int x1, int y1, t_env *s)
{
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2, e2;

  while (1){
	mlx_pixel_put(s->mlx, s->win, x0, y0, 0xFF0000);
	if (x0==x1 && y0==y1)
		break;
	e2 = err;
	if (e2 >-dx)
	{
		err -= dy;
		x0 += sx;
	}
	if (e2 < dy)
	{
		err += dx;
		y0 += sy;
	}
  }
}

void      init_coord(t_env *s)
{	s->mlx = NULL;
	s->win = NULL;
	s->big_string = NULL;
	s->coord = NULL;
	s->x = 0;
	s->y = 0;
}

/*void      make_coord(t_env *s, char *line)
{
	int		size;

	size = ft_strlen(line);
	s->coord += (char **)malloc(sizeof(char *) * 1)
	ft_putnbr(size);
	s->coord[s->y] = ft_strdup(line);
	s->y += 1;
}*/

char	*take_map(int fd)
{
	char		*line;
	char		*readder;
	char		*tmp;

	line = ft_strnew(0);
	while (get_next_line(fd, &readder) > 0)
	{
		tmp = readder;
		line = ft_strjoin(line, readder);
		ft_memdel((void **)&tmp);
		tmp = line;
		line = ft_strjoin(line, "\n");
		ft_memdel((void **)&tmp);
	}
	ft_memdel((void **)&readder);
	return (line);
}

int		main(int ac, char **av)
{
	int		fd;
	char	*string;
	t_env	s;

	(void)ac;
	if ((fd = open(av[1], O_RDONLY)) <= 0)
	{
		ft_putstr("Open() failed.\n");
		return (-1);
	}
	init_coord(&s);
	string = take_map(fd);
	return (0);
}

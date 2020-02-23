/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:22:00 by lsuardi           #+#    #+#             */
/*   Updated: 2020/02/23 16:16:37 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

void	ft_putstr(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}

int		ft_strpos(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int		ft_print_num(char *num, struct s_filelist *list)
{
	while (list)
	{
		if (ft_strcmp(num, list->number) == 0)
		{
			ft_putstr(list->word);
			ft_putstr(" ");
			return (SUCCESS);
		}
		list = list->next;
	}
	return (FAILURE);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*point;

	i = 0;
	while (str[i])
		i++;
	if(!(point = (char*)malloc(i + 1)))
		return (NULL);
	i = -1;
	while (str[++i])
		point[i] = str[i];
	point[i] = 0;
	return (point);
}

int		ft_open_file(int *fd, char *arg)
{
	*fd = open(arg, O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr("Dict Error\n");
		return(FAILURE);
	}
	return (SUCCESS);
}

int		ft_close_file(int *file)
{
	if (close(*file) == -1)
	{
		ft_putstr("Dict Error\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int		ft_get_words(char *arg, char *buf)
{
	int fd;
	int size;

	if (ft_open_file(&fd, arg) == FAILURE)
		return (FAILURE);
	size = read(fd, buf, BUF_SIZE);
	buf[size] = 0;
	if (ft_close_file(&fd) == FAILURE)
		return (FAILURE);
	return (size);
}

struct s_filelist	*ft_add_link(t_filelist *list, char *nb, char *wrd)
{
	t_filelist *tmp;

	tmp = malloc(sizeof(t_filelist));
	if (tmp)
	{
		tmp->number = ft_strdup(nb);
		tmp->word = ft_strdup(wrd);
		tmp->next = list;
	}
	return (tmp);
}

int		ft_init_list(struct s_filelist *sfile, char *buf)
{
	int i;
	int j;
	char nb[BUF_SIZE];
	char wrd[BUF_SIZE];
	t_filelist *stock;

	i = 0;
	while (buf[i])
	{
		j = 0;
		nb[0] = 0;
		wrd[0] = 0;
		if (buf[i] == '\n')
			break ;
		if (ft_strpos(&buf[i], '\n') < ft_strpos(&buf[i], ':'))
		{
			ft_putstr("Dict Error\n");
			return (FAILURE);
		}
		while (buf[i + j] != ' ')
		{
			nb[j] = buf[i + j];
			j++;
		}
		nb[j] = 0;
		i += j;
		while (buf[i] == ':' || buf[i] == ' ')
			i++;
		j = 0;
		while (buf[i + j] != '\n')
		{
			wrd[j] = buf[i + j];
			j++;
		}
		wrd[j] = 0;
		i += j + 1;
		sfile = ft_add_link(sfile, nb, wrd);
	}
	stock = sfile;
	/*while (sfile)
	{
		printf("NUMBER : %s\n WORD : %s\n\n", sfile->number, sfile->word);
		sfile = sfile->next;
	}*/
	/*if (ft_print_num("1000000000000000", stock) == FAILURE)
		return (FAILURE);*/
	return (SUCCESS);
}

int		ft_file_read(char *av)
{
	char		buffer[BUF_SIZE + 1];
	t_filelist	*structfile;
	int			file_size;

	structfile = NULL;
	file_size = ft_get_words(av, buffer);
	if (file_size == -1)
		return (FAILURE);
	if (ft_init_list(structfile, buffer) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int		 main(int argc, char **argv)
{
	if (argc == 3)
		ft_putstr("Error\n");
	if (argc == 2)
	{
		if (ft_file_read(argv[1]) == FAILURE)
			return (1);
	}
	else if (ft_file_read("dict") == FAILURE)
			return(1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 19:36:51 by lsuardi           #+#    #+#             */
/*   Updated: 2020/02/23 16:16:40 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H

# define	FILE_H
# define	SUCCESS		0
# define	FAILURE		-1
# define	BUF_SIZE	424242

# include				<sys/types.h>
# include				<sys/stat.h>
# include				<fcntl.h>
# include				<stdlib.h>
# include				<unistd.h>
# include				<stdio.h>
# include				"file.h"

typedef struct	s_filelist t_filelist;

struct			s_filelist
{
	char		*number;
	char		*word;
	int			units;
	t_filelist	*next;
};

#endif

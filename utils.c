/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 07:35:09 by psousa            #+#    #+#             */
/*   Updated: 2023/07/27 07:35:09 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *s, t_params *par, t_philo *p, int malloc)
{
	if (malloc)
	{
		if (par->death)
			free(par->death);
		if (par->fork)
			free(par->fork);
		if (p)
			free(p);
	}		
	return (printf("%s", s));
}

void	print_routine(t_philo *p, char *action)
{
	pthread_mutex_lock(p->par->death);
	if (p->par->over)
	{
		pthread_mutex_unlock(p->par->death);
		return ;
	}
	printf("%ld %d %s\n", time_now() - p->thread_start,
		p->id, action);
	pthread_mutex_unlock(p->par->death);
}

long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	ft_usleep(long int time)
{
	long int	start_time;

	start_time = time_now();
	while ((time_now() - start_time) < time)
		usleep(150);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 07:34:50 by psousa            #+#    #+#             */
/*   Updated: 2023/07/27 07:34:50 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_philo p, int last)
{
	if (p.par->check_meal
		&& last == p.par->num - 1
		&& p.iter_num == p.par->max_iter)
		return (ft_usleep(300));
	return (0);
}

static void	check_thread(t_params *p, t_philo *philo)
{
	int	i;

	while (!p->ready)
		continue ;
	while (!p->over)
	{
		i = -1;
		while (++i < p->num)
			if (check_death(&philo[i]) || check_meals(philo[i], i))
				p->over = 1;
	}
	if (p->check_meal && philo[p->num - 1].iter_num == p->max_iter)
	{
		ft_usleep(5 * p->num);
		printf("						\n");
		printf("All philosophers have eaten %d times and no one died\n", p->max_iter);
	}
	return ;
}

static int	init_thread(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < p->num)
	{
		philo[i].rf = philo[(i + 1) % p->num].lf;
		if (pthread_create(&philo[i].life_tid, NULL,
				&thread_routine, &philo[i]) == -1)
			return (error_msg("Error\nFailed to create thread\n", p, philo, 2));
	}
	i = -1;
	p->start = time_now();
	while (++i < p->num)
	{
		philo[i].thread_start = p->start;
		philo[i].meal = p->start;
	}
	p->ready = 1;
	return (0);
}

static void	end_thread(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < p->num)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	pthread_mutex_destroy(p->death);
	pthread_mutex_destroy(p->fork);
	free(p->death);
	free(p->fork);
	free(philo);
}

int	philosophers(t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * params->num);
	if (!philo || init_philo(params, philo))
		return (EXIT_FAILURE);
	if (init_thread(params, philo))
		return (EXIT_FAILURE);
	check_thread(params, philo);
	end_thread(params, philo);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:53:00 by rtorres           #+#    #+#             */
/*   Updated: 2024/08/29 11:43:36 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	check_philo_dead(t_simulation *sim)
{
	int	i;

	while (!sim->full)
	{
		i = -1;
		while (!sim->dead && ++i < sim->n_philo)
		{
			pthread_mutex_lock(&sim->check);
			if (get_time() - sim->ph[i].meal_time > (size_t)sim->time_to_die)
			{
				print_message(&sim->ph[i], MESSAGE_DEAD);
				sim->dead = 1;
			}
			pthread_mutex_unlock(&sim->check);
			usleep(100);
		}
		if (sim->dead)
			break ;
		i = 0;
		while (sim->n_meal != -1 && sim->n_philo
			&& sim->ph[i].m_eaten >= sim->n_meal)
			i++;
		if (i == sim->n_philo)
			sim->full = 1;
	}
}

void	clean_philo(t_simulation *sim, pthread_t *id)
{
	int	i;

	i = -1;
	while (++i < sim->n_philo)
		pthread_join(id[i], NULL);
	i = -1;
	while (++i < sim->n_philo)
		pthread_mutex_destroy(&sim->ph[i].fork);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->check);
	free(sim->ph);
	free(id);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	pass_time(t_simulation *sim, size_t time)
{
	size_t	i;

	i = get_time();
	while (!(sim->dead))
	{
		if (get_time() - i >= time)
			break ;
		usleep(100);
	}
}

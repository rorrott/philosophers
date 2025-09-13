/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:42:54 by rtorres           #+#    #+#             */
/*   Updated: 2024/08/29 10:23:49 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	eat(t_philosopher *philosopher)
{
	t_simulation	*sim;

	sim = philosopher->sim;
	pthread_mutex_lock(&philosopher->fork);
	print_message(philosopher, MESSAGE_FORKS);
	if (philosopher->sim->n_philo == 1)
	{
		pass_time(sim, sim->time_to_die);
		print_message(philosopher, MESSAGE_DEAD);
		pthread_mutex_unlock(&philosopher->fork);
		sim->dead = 1;
		return ;
	}
	pthread_mutex_lock(&philosopher->next->fork);
	print_message(philosopher, MESSAGE_FORKS);
	pthread_mutex_lock(&sim->check);
	philosopher->m_eaten++;
	print_message(philosopher, MESSAGE_EAT);
	philosopher->meal_time = get_time();
	pthread_mutex_unlock(&sim->check);
	pass_time(sim, sim->time_to_eat);
	pthread_mutex_unlock(&philosopher->fork);
	pthread_mutex_unlock(&philosopher->next->fork);
}

void	*is_alive(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sim;

	philo = (t_philosopher *)arg;
	sim = philo->sim;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!sim->dead && !sim->full)
	{
		eat(philo);
		print_message(philo, MESSAGE_SLEEP);
		pass_time(sim, sim->time_to_sleep);
		print_message(philo, MESSAGE_THINK);
	}
	return (NULL);
}

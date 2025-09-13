/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:35:52 by rtorres           #+#    #+#             */
/*   Updated: 2024/08/29 11:35:24 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static char	*get_message(int msg)
{
	if (msg == MESSAGE_FORKS)
		return (CYAN"has taken a fork"RST);
	if (msg == MESSAGE_EAT)
		return (YELLOW"is eating"RST);
	if (msg == MESSAGE_SLEEP)
		return (BLUE"is sleeping"RST);
	if (msg == MESSAGE_THINK)
		return (GREEN"is thinking"RST);
	if (msg == MESSAGE_DEAD)
		return (RED"died"RST);
	return ("Error: not valid message id");
}

void	print_message(t_philosopher *philo, int msg)
{
	size_t	i;

	i = get_time() - philo->sim->time;
	pthread_mutex_lock(&philo->sim->print_mutex);
	if (!philo->sim->dead && !philo->sim->full)
	{
		printf("[%ld] ", i);
		printf(MAG"Philosopher %d "RST, philo->id);
		printf("%s ", get_message(msg));
		printf("\n");
	}
	pthread_mutex_unlock(&philo->sim->print_mutex);
}

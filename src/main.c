/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:23:41 by rtorres           #+#    #+#             */
/*   Updated: 2024/08/29 11:42:59 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	is_error(void)
{
	write(2, "Error!, invalid arguments!\n", 27);
	return (1);
}

int	main(int ac, char **av)
{
	int				i;
	t_simulation	sim;
	pthread_t		*id;

	if ((ac < 5 || ac > 6) || parse_args(ac, av, &sim))
		return (is_error());
	id = (pthread_t *)malloc(sim.n_philo * sizeof(pthread_t));
	sim.time = get_time();
	i = -1;
	while (++i < sim.n_philo)
	{
		if (pthread_create(&id[i], NULL, &is_alive, &sim.ph[i]))
		{
			write(2, "Error! cannot create thread\n", 28);
			free(sim.ph);
			free(id);
			return (1);
		}
		pthread_mutex_lock(&sim.check);
		sim.ph[i].meal_time = sim.time;
		pthread_mutex_unlock(&sim.check);
	}
	check_philo_dead(&sim);
	clean_philo(&sim, id);
	return (0);
}

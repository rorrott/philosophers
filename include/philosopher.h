/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:30:22 by rtorres           #+#    #+#             */
/*   Updated: 2024/08/29 11:42:19 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

# define RST     "\033[0m"
# define CYAN    "\033[1;96m"
# define MAG     "\033[1;95m"
# define RED     "\033[31m" 
# define GREEN   "\033[32m"
# define BLUE    "\033[34m"
# define YELLOW  "\033[33m" 

enum e_message
{
	MESSAGE_FORKS = 0,
	MESSAGE_EAT,
	MESSAGE_SLEEP,
	MESSAGE_THINK,
	MESSAGE_DEAD
};

typedef struct s_philosopher
{
	int						id;
	int						m_eaten;
	size_t					meal_time;
	pthread_mutex_t			fork;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
	struct s_simulation		*sim;
}							t_philosopher;

typedef struct s_simulation
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meal;
	int				n_philo;
	int				full;
	int				dead;
	size_t			time;
	t_philosopher	*ph;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check;
}					t_simulation;

void	print_message(t_philosopher *philo, int msg);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	*is_alive(void *arg);
void	check_philo_dead(t_simulation *sim);
void	clean_philo(t_simulation *sim, pthread_t *id);
size_t	get_time(void);
void	pass_time(t_simulation *sim, size_t time);
int		parse_args(int ac, char **av, t_simulation *sim);

#endif
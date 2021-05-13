cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

#add_executable(philosophers philo_three/main.c philo_three/life.c philo_three/ft_atoi.c philo_three/utils.c philo_three/death.c)
add_executable(philosophers philo_two/life.c philo_two/ft_atoi.c philo_two/utils.c philo_two/death.c)
#add_executable(philosophers philo_one/life.c philo_one/ft_atoi.c philo_one/utils.c philo_one/death.c)
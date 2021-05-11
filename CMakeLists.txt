cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

add_executable(philosophers philo_one/life.c philo_one/ft_atoi.c philo_one/utils.c philo_one/death.c)
#add_executable(philosophers philo_one/life.c philo_one/ft_atoi.c philo_one/utils.c philo_one/death.c)
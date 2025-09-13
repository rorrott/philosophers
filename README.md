# philosophers

philosophers is a concurrency project developed as part of the 42 School curriculum.

The goal is to simulate the classical Dining Philosophers Problem, where philosophers alternate between eating, thinking, and sleeping, while competing for limited resources (forks).

This project introduces students to multithreading, synchronization, and concurrency issues such as deadlocks and race conditions.

## Features

- Simulation of philosophers sitting around a table

- Each philosopher:

- - Thinks 

- - Takes two forks 

- - Eats 

- - Sleeps 

- Correct handling of:

- - Thread creation and termination

- - Race conditions (mutex protection)

- - Deadlocks (avoided by design)
 
## Key Concepts

- Concurrency & parallelism

- Mutexes for resource protection

- Avoiding deadlocks and starvation

- Precise timing with usleep and gettimeofday

## Project Rules (42)

- Written in C

- Must use threads and mutexes (no semaphores in mandatory part)

- No data races or deadlocks allowed

- Each philosopher is a separate thread

- Must comply with 42 Norminette

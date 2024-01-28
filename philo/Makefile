# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsirenko <hsirenko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 16:17:53 by hsirenko          #+#    #+#              #
#    Updated: 2023/06/29 19:54:40 by hsirenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Source files
SRCS = data_init.c dinner_simulation.c error_handling.c input_check.c main.c setters_getters.c \
       synchronize_watch.c utils.c watch_dinner.c \

OBJS	:= $(SRCS:%.c=%.o)
NAME = philo   #name of my target executable

HEADER = philo.h

#Compiler
CC = gcc
RM = rm -f

#Compiler and linker flags
CFLAGS = -g -Wall -Wextra -Werror -pthread -fsanitize=address 
#-fsanitize=thread

#Targets
all:	$(NAME) #This is the default target that gets built when you run make with no arguments. It depends on the $(NAME) target, which is my final executable.

${NAME}:	${OBJS}  #This section defines how to build my target ($(NAME)). It depends on $(OBJS)
			$(CC) $(CFLAGS) $^ -o $@ #The final line compiles and links the object files ($^) into the target executable ($@).
                                                                      # It includes compiler flags ($(CFLAGS))

%.o: %.c                                          #This is a generic rule for compiling source files (%.c) into object files (%.o).
		$(CC) $(CFLAGS) -c $< -o $@   #It uses the compiler ($(CC)), compiler flags ($(CFLAGS)), and input and output filenames ($< and $@, respectively).

clean:                              #The clean target removes object files ($(OBJS)) using the $(RM) command
			${RM} ${OBJS}

fclean: clean                       #The fclean target depends on clean and additionally removes the final executable ($(NAME))
			${RM} $(NAME)

re: 		fclean all              #The re (rebuild) target first runs make fclean to clean everything, and then it runs make all to rebuild the project from scratch.

.PHONY:		all clean fclean re

# leaks: re
# 	@echo "\033[1;33m\nChecking for memory leaks...\033[0m"
# 	leaks --atExit -- ./$(NAME) 5 800 200 200 5

# valgrind_race: re
# 	@echo "\033[1;33m\nChecking for race conditions with valgrind...\033[0m"
# 	valgrind --tool=helgrind ./$(NAME) 5 800 200 200 5

# valgrind_leaks: re
# 	@echo "\033[1;33m\nChecking for memory leaks with valgrind...\033[0m"
# 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 5 800 200 200 5

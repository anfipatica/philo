NAME = philo
#NAME_BONUS = so_long_bonus

INC_DIR = ./inc
OBJS_DIR = ./obj
#BONUS_OBJS_DIR = ./obj/bonus
SRC_DIR = ./src
#BONUS_DIR = ./bonus
CC = gcc

CFLAGS = -Wall -Werror -Wextra -I$(INC_DIR)
#CFLAGS = -Wall -Werror -Wextra -I$(INC_DIR) -fsanitize=address -g3 
#CFLAGS = -Wall -Werror -Wextra -I$(INC_DIR) -fsanitize=thread -g -O1 -fPIE -pie -fno-omit-frame-pointer

RM = rm -rf

OBJS = $(OBJS_DIR)/philo.o \
		$(OBJS_DIR)/utils.o \
		$(OBJS_DIR)/free.o \
		$(OBJS_DIR)/init.o \
		$(OBJS_DIR)/getters_setters.o \
		$(OBJS_DIR)/actions.o \
		$(OBJS_DIR)/monitor.o \
		$(OBJS_DIR)/print_functions.o \
		$(OBJS_DIR)/validation.o


.PHONY = clean all fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $^ $(LIBFT) -o $@ $(CFLAGS)

$(OBJS_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS)

#bonus : $(NAME_BONUS)

#$(NAME_BONUS) : $(OBJS_BONUS)
#	make re -C src/utils/libft
#	$(CC) $^ $(LIBFT) -o $@ $(CFLAGS)

#$(BONUS_OBJS_DIR)/%.o : $(BONUS_DIR)/%.c
#	mkdir -p $(BONUS_OBJS_DIR)
#	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

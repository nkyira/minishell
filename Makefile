G = "\033[32m"
RORO =" \
	  __        __   ___________    __       _   ___________   __________    _        _   _________    _          _\n\
	 |   \    /   | |____   ____|  |   \    | | |____   ____| |  ________|  | |      | | |  _______|  | |        | |\n\
	 | |\ \  / /| |      | |       |  \ \   | |      | |      |  |_______   | |______| | | |_______   | |        | |\n\
	 | | \ \/ / | |      | |       | | \ \  | |      | |      |________  |  |  ______| | |  _______|  | |        | |\n\
	 | |  \__/  | |  ____| |____   | |   \ \| |  ____| |____   ________| |  | |      | | | |_______   | |______  | |______\n\
	 |_|        |_| |___________|  |_|    \___| |___________| |__________|  |_|      |_| |_________|  |________| |________|"

R1 =	 " __        __   ___________    __       _   ___________   __________    _        _   _________    _          _"
R2 =	 "|   \    /   | |____   ____|  |   \    | | |____   ____| |  ________|  | |      | | |  _______|  | |        | |"
R3 =	 "| |\ \  / /| |      | |       |  \ \   | |      | |      |  |_______   | |______| | | |_______   | |        | |"
R4 =	 "| | \ \/ / | |      | |       | | \ \  | |      | |      |________  |  |  ______| | |  _______|  | |        | |"
R5 =	 "| |  \__/  | |  ____| |____   | |   \ \| |  ____| |____   ________| |  | |      | | | |_______   | |______  | |______"
R6 =	 "|_|        |_| |___________|  |_|    \___| |___________| |__________|  |_|      |_| |_________|  |________| |________|"


CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

SRC = src/

OBJS_DIR = object/

LIBFT = libft/

LIBFT_LIB = ${LIBFT}libft.a 

PRINTF = printf/

PRINTF_LIB = $(PRINTF)libftprintf.a

PARSING_SRC = $(SRC)/parsing/

RELEASE_SRC = $(SRC)/release/

UTILS_SRC = $(SRC)/utils/

CHECK_SRC = $(SRC)/check_line/

COMMAND_SRC = $(SRC)/commande/

EXEC_SRC = $(SRC)/execution/

DEBUG = $(SRC)/debug/

SIGNAL = $(SRC)/signal/

BUILTIN_SRC = $(SRC)/builtin/

SOURCES = $(PARSING_SRC)separator.c $(PARSING_SRC)parsing_start.c\
			$(PARSING_SRC)init_token.c $(PARSING_SRC)dollar.c $(RELEASE_SRC)free_tokens.c\
			$(UTILS_SRC)utils.c $(UTILS_SRC)init_data.c $(UTILS_SRC)utils2.c\
			$(UTILS_SRC)env.c $(UTILS_SRC)env2.c\
			$(PARSING_SRC)dollar_quote_utils.c $(PARSING_SRC)quote.c\
			$(PARSING_SRC)replace_dollar_quote.c\
			$(CHECK_SRC)check_tokens.c $(CHECK_SRC)check_token_again.c\
			$(COMMAND_SRC)create_command.c $(COMMAND_SRC)free_command.c\
			$(COMMAND_SRC)init_command.c $(COMMAND_SRC)utils_command.c \
			$(COMMAND_SRC)command_path.c $(COMMAND_SRC)utils2_command.c \
			$(EXEC_SRC)exec_command.c $(EXEC_SRC)exec.c $(EXEC_SRC)redirection_trunc.c\
			$(EXEC_SRC)redirection_input.c $(EXEC_SRC)exec_parent_child.c\
			$(SIGNAL)signal.c\
			$(RELEASE_SRC)ft_exit.c\
			$(BUILTIN_SRC)exit.c $(BUILTIN_SRC)pwd.c $(BUILTIN_SRC)cd.c\
			$(BUILTIN_SRC)export.c $(BUILTIN_SRC)echo.c $(BUILTIN_SRC)unset.c\
			$(DEBUG)error.c $(DEBUG)error_fork.c\
			$(SRC)main.c 

OBJECTS = $(SOURCES:%.c=$(OBJS_DIR)%.o)

all: ${NAME}

$(OBJECTS):$(OBJS_DIR)%.o:%.c
		@mkdir -p $(@D)
		@$(CC) -g $(CFLAGS) -c $< -o $@

${NAME}: $(OBJECTS)
	make -C ${PRINTF}
	make -C $(LIBFT)
	${CC} $(CFLAGS) ${OBJECTS} ${PRINTF_LIB} ${LIBFT_LIB} -o ${NAME} -lreadline 
	@echo $(G) compile done

clean:
	rm -f $(OBJECTS)

fclean: clean
	make -C $(LIBFT) fclean 
	make -C $(PRINTF) fclean 
	rm -f $(NAME) 

re: fclean all

.SILENT:

.PHONY: all clean fclean re

#	sleep 0.8|echo $G ${R1}
#	sleep 0.6|echo $G ${R2} 
#	sleep 0.4|echo $G ${R3} 
#	sleep 0.3|echo $G ${R4} 
#	sleep 0.2|echo $G ${R5} 
#	sleep 0.1|echo $G ${R6}
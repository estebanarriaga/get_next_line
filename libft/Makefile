NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MY_SOURCES = ft_isalpha.c \
			ft_isdigit.c  \
			ft_isalnum.c \
			ft_bzero.c \
			ft_memset.c \
			ft_strlen.c \
			ft_isprint.c \
			ft_isascii.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strncmp.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strlcpy.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_memchr.c \
			ft_strrchr.c \
			ft_strlcat.c \
			ft_substr.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_memcmp.c \
			ft_split.c \
			ft_striteri.c

BONUS_SRCS = 	ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

$(NAME): $(MY_OBJECTS) libft.h
			@ar rcs $(NAME) $(MY_OBJECTS)

all:	$(NAME)

bonus: $(BONUS_OBJS) libft.h
		@ar rcs $(NAME) $(BONUS_OBJS)	

clean:
		@rm -f $(MY_OBJECTS) $(BONUS_OBJS)

fclean: clean
		@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus
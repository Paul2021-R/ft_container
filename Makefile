# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/05 16:30:32 by seojin            #+#    #+#              #
#    Updated: 2022/12/17 17:27:32 by seojin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef NAME
	NAME = ft_container
endif

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

ifndef SRCS
	SRCS = main.cpp
endif

LIB = lib.a
OBJS = $(SRCS:%.cpp=%.o)
OBJS_DIR = objs

all : $(NAME)

$(NAME) : $(OBJS_DIR)/ $(LIB)
	$(CXX) $(LIB) $(OBJS_DIR)/main.o -o $@

$(LIB) : $(addprefix $(OBJS_DIR)/, $(OBJS))
	ar rc $@ $^

$(OBJS_DIR) : 
	mkdir $@

$(OBJS_DIR)/%.o : %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean :
	$(RM) $(addprefix $(OBJS_DIR)/, $(OBJS))

fclean : 
	$(RM) $(LIB) $(NAME)
	$(RM) -r $(OBJS_DIR)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re

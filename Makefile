CXX		= c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98

NAME	= a.out

SRCS	= main.cpp
OBJS	= $(SRCS:.cpp=.o)
HEADERS	= main.hpp

ifdef DFLAG
	CXXFLAGS += -g2 -fsanitize=address
endif

ifdef 98
	CXX	= g++
	CXXFLAGS += -pedantic
endif

all : $(NAME)

debug:
	@make fclean
	@make DFLAG=1 all

98:
	@make fclean
	@make 98=1 all

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean :
	$(RM) $(OBJS)

fclean :
	make clean
	$(RM) $(NAME)

re :
	make fclean
	make all

$(OBJS)	: $(HEADERS)

.PHONY : all bonus clean fclean re

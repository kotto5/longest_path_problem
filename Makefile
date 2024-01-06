NAME	=	execute

SRCS	=	$(wildcard srcs/*.cpp)
INCLUDE	=	$(wildcard includes/*.hpp)
SRCDIR	=	srcs
OBJDIR	=	objs

OBJS	=	$(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPS	=	$(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.d)))

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address -MMD -MP

RM		=	rm -rf

all:		$(NAME)

objs/%.o:	srcs/%.cpp
			@mkdir -p objs
			$(CXX) $(CXXFLAGS) -c $< -o $@ -Iincludes

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

debug:		CXXFLAGS += -DDEBUG
debug:		re

clean:
			$(RM) $(OBJS) $(DEPS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re


-include	$(DEPS)
CC	=	g++

RM	=	rm -f

SRCS	=	Socket.cpp \
		PacketDecrypt.cpp \
		main.cpp

OBJS	=	$(SRCS:.cpp=.o)

OBJM	=	$(SRCM:.cpp=.o)

NAME	=	sniffer

LXXDFLAGS	=

#CXXFLAGS	=	-Wall -Wextra -I./include -I./src -std=c++11


all:		$(NAME)

$(NAME):	$(OBJS) $(OBJM)
	@$(CC) $(LDFLAGS) $(OBJS) $(OBJM) -o $(NAME) $(DXXFLAGS) -pthread -std=gnu++1z -std=c++1z
	@echo "------>" $(CGREEN) $(NAME) "created" $(CNOCOLOR)


clean:
	@echo "[" $(CRED) "Remove .o files" $(CNOCOLOR) "]"
	@$(RM) $(OBJS) $(OBJM) $(OBJT)

fclean: clean
	@$(RM) $(NAME) $(NAMET)

re:	fclean all



.PHONY: all clean fclean re test

##
## Makefile for  in /home/gamain_j/rendu/cpp_nibbler
##
## Made by gamain_j gamain_j
## Login   <gamain_j@epitech.net>
##
## Started on  Mon Mar 23 17:22:46 2015 gamain_j gamain_j
## Last update Sun Dec  6 23:42:35 2015 Grisha GHUKASYAN
##

CC	=	g++

RM	=	rm -rf

CXXFLAGS+=	-W -Wall -Wextra -Werror -std=c++11
CXXFLAGS+=	-fPIC -I./ -I./$(LIB1DIR) -I./$(MISCDIR) -I./$(MISCDIRLINUX) -I./$(MISSILEDIR)

LDFLAGS +=

MISSILEDIR	=	missiles/

MISCDIR	=	../misc/

MISCDIRLINUX	=	../misc/linux_specific/

MISCDIRWINDOWS	=	../misc/windows_specific/

LIB1DIR	=	monsters/

NAME	=	test

LIB1	=	$(LIB1DIR)MonsterTest.so

SRC	=	main_test.cpp \
		Game.cpp \
		Map.cpp \
		ScoreList.cpp \
		Score.cpp \
		MonsterFactory.cpp \
		MissileFactory.cpp \
		AUnit.cpp \
		Player.cpp \
		AMonster.cpp \
		AMissile.cpp \
		$(MISSILEDIR)BasicMissile.cpp \
		ABonus.cpp \
		AObstacle.cpp \
		$(MISCDIR)Timer.cpp \
		$(MISCDIRLINUX)CULibLoader.cpp

LIB1SRC	=	$(LIB1DIR)MonsterTest.cpp

OBJ	=	$(SRC:.cpp=.o)

LIB1OBJ	=	$(LIB1SRC:.cpp=.o)

all:		$(NAME) $(LIB1)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) -ldl

$(LIB1):	$(LIB1OBJ)
		$(CC) -shared -o $(LIB1) $(LIB1OBJ)

clean:
		$(RM) $(OBJ)
		$(RM) $(LIB1OBJ)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(LIB1)

re:		fclean all

.PHONY:		all clean fclean re

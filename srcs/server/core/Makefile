CC	=	g++

RM	=	rm -rf

CXXFLAGS+=	-W -Wall -Wextra -Werror -std=c++11
CXXFLAGS+=	-fPIC
CXXFLAGS+=	-I./ -I./$(LIB1DIR) -I./$(MISSILEDIR) -I./$(MISCDIR) -I./$(MISCDIRLINUX)

LDFLAGS +=

MISSILEDIR	=	missiles/

MISCDIR	=	../misc/

MISCDIRLINUX	=	../misc/linux_specific/

MISCDIRWINDOWS	=	../misc/windows_specific/

LIBSDIR	=	libs/

LIB1DIR	=	monsters/

NAME	=	test

LIB1	=	$(LIBSDIR)MonsterTest.so

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

LIB1SRC	=	AUnit.cpp \
		AMonster.cpp \
		$(LIB1DIR)MonsterTest.cpp

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

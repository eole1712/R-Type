CC	=	g++

RM	=	rm -rf

CXXFLAGS+=	-W -Wall -Wextra -Werror -std=c++11
CXXFLAGS+=	-fPIC -I./ -I./$(MISCDIR) -I./$(COMMONDIR)
CXXFLAGS+=	-I./$(MONSTERDIR) -I./$(MISSILEDIR)
CXXFLAGS+=	-I./$(COMMONMISCDIR) -I./$(MISCDIRLINUX)

LDFLAGS +=

MISCDIR		=	../misc/

COMMONDIR	=	../../common/core/

MONSTERDIR	=	$(COMMONDIR)monsters/

MISSILEDIR	=	$(COMMONDIR)missiles/

LIBSDIR		=	$(COMMONDIR)libs/

COMMONMISCDIR	=	../../common/misc/

MISCDIRLINUX	=	$(COMMONMISCDIR)linux_specific/

MISCDIRWINDOWS	=	$(COMMONMISCDIR)windows_specific/

NAME	=	test

LIB1	=	$(LIBSDIR)MonsterTest.so

SRC	=	main_test.cpp \
		Game.cpp \
		Map.cpp \
		ScoreList.cpp \
		Score.cpp \
		Player.cpp \
		$(COMMONDIR)MonsterFactory.cpp \
		$(COMMONDIR)MissileFactory.cpp \
		$(COMMONDIR)AUnit.cpp \
		$(COMMONDIR)AMonster.cpp \
		$(COMMONDIR)AMissile.cpp \
		$(MISSILEDIR)BasicMissile.cpp \
		$(COMMONDIR)ABonus.cpp \
		$(COMMONDIR)AObstacle.cpp \
		$(MISCDIRLINUX)CULibLoader.cpp \
		$(MISCDIR)Timer.cpp

LIB1SRC	=	$(COMMONDIR)AUnit.cpp \
		$(COMMONDIR)AMonster.cpp \
		$(MONSTERDIR)MonsterTest.cpp

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

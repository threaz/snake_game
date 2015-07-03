CPPFLAGS= -c -g -Iinc -Wall -pedantic -lncurses -std=c++11

snake_game: obj/main.o obj/Point.o obj/Object.o obj/Snake.o obj/Board.o obj/Player.o
	g++ -Wall -pedantic -std=c++11 -o snake_game obj/main.o obj/Point.o\
		obj/Object.o obj/Snake.o obj/Board.o obj/Player.o -lncurses

obj/main.o: src/main.cpp inc/Board.hh inc/Snake.hh
	g++ ${CPPFLAGS} -o obj/main.o src/main.cpp 

obj/Point.o: src/Point.cpp 
	g++ ${CPPFLAGS} -o obj/Point.o src/Point.cpp

obj/Object.o: src/Object.cpp inc/Point.hh
	g++ ${CPPFLAGS} -o obj/Object.o src/Object.cpp

obj/Snake.o: src/Snake.cpp inc/Object.hh inc/Snake.hh
	g++ ${CPPFLAGS} -o obj/Snake.o src/Snake.cpp

obj/Board.o: src/Board.cpp inc/Board.hh inc/Object.hh
	g++ ${CPPFLAGS} -o obj/Board.o src/Board.cpp

obj/Player.o: src/Player.cpp inc/Player.hh
	g++ ${CPPFLAGS} -o obj/Player.o src/Player.cpp

clean:
	rm -f obj/*.o snake_game

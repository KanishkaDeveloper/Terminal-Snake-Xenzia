BIN = snake
ARCHIVE = libsnake.a
SO = libsnake.SO
run: src/main.c src/food.c src/game.c src/render.c src/snake.c src/ui.c src/save.c src/obstacle.c
	gcc -c src/food.c src/game.c src/render.c src/snake.c src/ui.c src/save.c src/obstacle.c
	ar rcs ${ARCHIVE} food.o game.o render.o snake.o ui.o save.o obstacle.o
	gcc -g -o ${BIN} src/main.c ${ARCHIVE} -lncurses
clean: 
	rm ${BIN} *.o ${ARCHIVE}

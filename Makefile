all: dir chessviz

dir:
	mkdir -p bin
	mkdir -p build

chessviz: build/main.o build/searchsym.o build/board_print.o build/tokenlen.o
	gcc -Wall -Werror -o bin/chessviz.run build/main.o build/searchsym.o build/board_print.o build/tokenlen.o 

build/main.o: src/main.c
	gcc -Wall -Werror -o build/main.o -c src/main.c -MP -MMD -MT 'src/main.h'

build/searchsym.o: src/searchsym.c
	gcc -Wall -Werror -o build/searchsym.o -c src/searchsym.c -MP -MMD

build/board_print.o: src/board_print.c
	gcc -Wall -Werror -o build/board_print.o -c src/board_print.c -MP -MMD -MT 'src/board_print.h'

build/tokenlen.o: src/tokenlen.c
	gcc -Wall -Werror -o build/tokenlen.o -c src/tokenlen.c -MP -MMD

clean:
	rm -rf bin build

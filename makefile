bin/vbi: src/cli.c src/vbi.h src/vbi.c
	mkdir bin -p
	cc -std=c99 -o bin/vbi src/cli.c src/vbi.c

bin/vbi: src/cli.c src/vbi.h src/vbi.c
	mkdir bin -p
	cc -o bin/vbi src/cli.c src/vbi.c

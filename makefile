bin/vbi: src/cli.c src/vbi.h src/backend.c
	mkdir bin -p
	cc -o bin/vbi src/cli.c src/backend.c

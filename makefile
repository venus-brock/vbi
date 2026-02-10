bin/vbi: src/vbi.c src/backend.h src/backend.c
	mkdir bin -p
	cc -o bin/vbi src/vbi.c src/backend.c

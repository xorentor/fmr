all:
	gcc -I./std/ -I./src/ ./src/*.c ./std/*.c -o fmr -lpthread

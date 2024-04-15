all: clean chunk

chunk: main.c
	gcc -o chunk main.c

clean:
	rm -f chunk

CC=gcc
TARGET=main
 
all:
	$(CC) *.c -o $(TARGET)
 
clean:
	rm $(TARGET)
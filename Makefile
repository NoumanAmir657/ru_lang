CC=gcc
TARGET=main
 
all:
	$(CC) src/*.c -o $(TARGET)
 
clean:
	rm $(TARGET)
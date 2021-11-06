CC=gcc

install:
	$(CC) cwdc.c -o /usr/bin/cwdc
clean:
	rm -f /usr/bin/cwdc


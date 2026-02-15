CC=gcc
CFLAGS= -Wall -g
OUT = mylogin
MAIN=mylogin.c
LINK=pwdblib.c -lcrypt

main:
	$(CC) $(CFLAGS) $(LINK) $(MAIN) -o $(OUT)
	./mylogin

clean:
	rm mylogin


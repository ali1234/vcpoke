C = main.c mailbox.c
H = mailbox.h

F = -lrt -lm -ldl

all:	vcpoke

vcpoke:	$(C) $(H)
	gcc -o vcpoke $(F) $(C) $(H)

clean:
	rm -f vcpoke

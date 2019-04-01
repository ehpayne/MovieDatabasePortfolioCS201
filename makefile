OBJS = main.o menus.o readFiles.o createUpdateDelete.o hash.o

OOPTS = -Wall -std=c11 

all: database

database : $(OBJS)
	gcc $(OOPTS) -o database $(OBJS)


test:
	echo RUNNING THE DATABASE
	./database

clean:
	rm -f $(OBJS) database

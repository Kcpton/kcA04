#***********************************************************************
#
# MakeFile
#
#***********************************************************************

all: ft

clean:
	rm -f ft

clobber: clean
	rm -f dynarray.o ft_client.o ft.o node.o file.o

ft: ft.o dynarray.o node.o file.o ft_client.o
	gcc217 -g ft_client.o ft.o node.o file.o dynarray.o -o ft

dynarray.o: dynarray.c dynarray.h
	gcc217 -g -c dynarray.c

ft_client.o: ft_client.c ft.h node.h file.h dynarray.h a4def.h
	gcc217 -g -c ft_client.c

node.o: node.c node.h dynarray.h a4def.h
	gcc217 -g -c node.c

file.o: file.c node.c file.h node.h dynarray.h a4def.h
	gcc217 -g -c file.c

ft.o: ft.c dynarray.h ft.h a4def.h node.h file.h
	gcc217 -g -c ft.c

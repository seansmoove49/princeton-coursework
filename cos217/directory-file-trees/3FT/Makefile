all: sampleft

clean: 
	rm -f sampleft

clobber: clean
	rm -f ft_client.o dynarray.o *~

sampleft: dynarray.o node.o ft.o ft_client.o checkerFT.o
	gcc217 -g dynarray.o ft.o ft_client.o node.o checkerFT.o -o sampleft

checkerFT.o: checkerFT.c dynarray.h checkerFT.h node.h a4def.h
	gcc217 -c checkerFT.c

dynarray.o: dynarray.c dynarray.h
	gcc217 -c dynarray.c

ft_client.o: ft_client.c ft.h
	 gcc217 -c ft_client.c

ft.o: ft.c ft.h dynarray.h node.h a4def.h checkerFT.h
	gcc217 -c ft.c

node.o: node.c node.h a4def.h dynarray.h checkerFT.h
	gcc217 -c node.c
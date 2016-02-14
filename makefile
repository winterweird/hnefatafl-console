LIBFILES = wnd.o board.o logic.o gamemodes.o menu.o
MAIN = main.c
OUTPUT = hnefatafl
FLAGS = -std=c99

build: $(OUTPUT)

$(OUTPUT): $(MAIN) libhnefatafl.a
	gcc $< -o $@ libhnefatafl.a $(FLAGS)
	
libhnefatafl.a: $(LIBFILES)
	ar -cvq libhnefatafl.a $(LIBFILES)

%.o: %.c %.h
	gcc -c $< $(FLAGS)

clean:
	del *.o *.exe *.a

run:
	$(OUTPUT)
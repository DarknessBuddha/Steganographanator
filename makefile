# variables
MAIN := driver.c
SRC := ppm.c EncodeDecode.c
ARGS := input.ppm output.ppm
FLAGS := -Wall

# processes
HEADERS := $(patsubst %.c,%.h,$(SRC))
OBJECTS := $(patsubst %.c,%.o,$(MAIN) $(SRC))

ifeq ($(OS),Windows_NT)
EXECUTABLE := $(patsubst %.c,%.exe,$(MAIN))
else
EXECUTABLE := $(patsubst %.c,%.out,$(MAIN))
endif

# commands
all: $(OBJECTS)
	gcc $(FLAGS) -o $(EXECUTABLE) $^

run: all
	./$(EXECUTABLE) $(ARGS)

%.o: %.c %.h
	gcc $(FLAGS) -c $<

%.o: %.c
	gcc $(FLAGS) -c $<

ifeq ($(OS),Windows_NT)
clean:
	del *.o *.out *.exe
else
clean:
	rm -f *.o *.out *.exe
endif

tar: $(MAIN) $(SRC) $(HEADERS) README.txt makefile
	tar -czvf PA2EC.tar.gz $^
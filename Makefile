OBJECTS := main.o emitter.o entity.o player.o
CFLAGS = -c
LFLAGS = -framework GLUT -framework OpenGL -framework Cocoa
OUTPUT = arrow

all: $(OBJECTS)
	g++ $(LFLAGS) $(OBJECTS) -o $(OUTPUT)

clean:
	rm -f *.o arrow

%.o: src/%.cc
	g++ $(CFLAGS) $<


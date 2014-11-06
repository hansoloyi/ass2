# The compiler to use while compiling
CC = g++

# Flags to use while compiling.
CFLAGS = -g -O2 -Wall

SRCS = main.cpp utility/VecPoint.cpp utility/Color.cpp utility/Triangle.cpp \
	utility/Sphere.cpp Scene.cpp lodepng.cpp utility/Light.cpp Film.cpp \
	utility/Ray.cpp Raytracer.cpp

OBJS = $(SRCS:.cpp=.o)

# define the executable file 
MAIN = v


.PHONY: clean

all: $(MAIN)
	@echo

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN) utility/*~ utility/*.o

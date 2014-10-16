CC = g++

CFLAGS = -c -Wall

LDFLAGS = -lSDLmain -lSDL -lSDL_image -lGL -lSDL_mixer

RM = rm -f

SRCS = source/ai.cc source/ammo.cc source/asteroid.cc source/explosion.cc source/game.cc source/input.cc source/missile.cc source/planet.cc source/screen.cc source/sound.cc source/spacecraft.cc source/spaceobject.cc source/spacevector.cc

OBJS = $(SRCS:.cc=.o)

EXEC = SuperMelee

all: $(SRCS) $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXEC) $(OBJS)

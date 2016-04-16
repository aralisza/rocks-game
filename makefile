CXXFLAGS =
all: main
main: Level.o Game.o
		g++ $(CXXFLAGS) Level.o Game.o
Level.o: Level.cc
		g++ $(CXXFLAGS) -c Level.cc
Game.o: TestLevel.cc Game.cc
		g++ $(CXXFLAGS) -c TestLevel.cc Game.cc
clean:
		rm *.o

CXXFLAGS = 
all: main
main: Level.o Game.o Zedboard.o
	g++ $(CXXFLAGS) Level.o Game.o Zedboard.o
Level.o: Level.cc
	g++ $(CXXFLAGS) -c Level.cc
Game.o: TestLevel.cc Game.cc
	g++ $(CXXFLAGS) -c TestLevel.cc Game.cc
Zedboard.o: Zedboard.cc
	g++ $(CXXFLAGS) -c Zedboard.cc        
clean:
	rm *.o
        

CXXFLAGS =
all: main
main: Level.o Concrete.o
		g++ $(CXXFLAGS) Level.o main.o
Level.o: Level.cc
		g++ $(CXXFLAGS) -c Level.cc
Concrete.o: TestLevel.cc main.cc
		g++ $(CXXFLAGS) -c TestLevel.cc main.cc
clean:
		rm *.o

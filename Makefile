jslib: JSGenerator.cpp
	g++ -c JSGenerator.cpp

all: main.cpp
	g++ -c JSGenerator.cpp
	g++ -o main JSGenerator.o main.cpp

clean:
	rm *.o
	rm main
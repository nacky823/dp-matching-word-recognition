do: main.o file_data_reader.o
	g++ -Wall -o do main.o file_data_reader.o

main.o: main.cpp
	g++ -Wall -c main.cpp
lib.o: file_data_reader.cpp
	g++ -Wall -c file_data_reader.cpp

clean:
	rm -f *.o do
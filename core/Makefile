do: main.o file_data_reader.o calculator.o
	g++ -Wall -o do main.o file_data_reader.o calculator.o

main.o: main.cpp
	g++ -Wall -c main.cpp
file_data_reader.o: file_data_reader.cpp
	g++ -Wall -c file_data_reader.cpp
calculator.o: calculator.cpp
	g++ -Wall -c calculator.cpp -lm

clean:
	rm -f *.o do
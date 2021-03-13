ordering.out: main.o Customer.o SalesOrder.o EODRecord.o
	g++ -std=c++11 -o ordering main.o Customer.o SalesOrder.o EODRecord.o

main.o: main.cpp Customer.cpp SalesOrder.cpp EODRecord.cpp
	g++ -std=c++11 -c main.cpp Customer.cpp SalesOrder.cpp EODRecord.cpp

Customer.o: Customer.cpp
	g++ -std=c++11 -c Customer.cpp

SalesOrder.o: SalesOrder.cpp
	g++ -std=c++11 -c SalesOrder.cpp
	
EODRecord.o: EODRecord.cpp
	g++ -std=c++11 -c EODRecord.cpp

clean:
	rm *.o ordering.out
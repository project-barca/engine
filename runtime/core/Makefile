# all targets
all: serverTCP

# tool invocations
# executable "TCPServer" depends on the files TCPServer.o and SocketWrapper.o
serverTCP: bin/TCPServer.o bin/socketWrapper.o
	@echo 'Finish compiling classes'	
	@echo 'Building target...'
	g++ -o bin/TCPServer bin/TCPServer.o bin/socketWrapper.o -lpthread
	@echo 'Finished building target: TCPServer'
	@echo ' '

# depends on the source and header files
bin/TCPServer.o: ./tcp_server.cpp ./../../include/servertcp.h
	@echo 'Compiling ServerTCP Class...'
	g++ -c -o bin/TCPServer.o ./tcp_server.cpp -std=c++11

bin/socketWrapper.o: ./socket.cpp ./../../include/socketwrapper.h
	@echo 'Compiling SocketWrapper Class...'
	g++ -c -o bin/socketWrapper.o ./socket.cpp -std=c++11

# clean the build
clean:
	rm -f bin/
#include <iostream>
// needed for std::thread
#include <thread>
// needed for memset and string functions
#include <cstring>
// needed for std::queue	
#include <queue>
// needed for sleep
#include <unistd.h>
// class Headers
#include "./../../servertcp.h"
#include "./../../socketwrapper.h"

// initialize _running flag as true and allocates data queue on heap
ServerTCP::ServerTCP(int port, callback_t callback) : _port(port),_callback(callback),
										_running(true), _data(new queue<string>), _thread() {
}
// copies only port and callback function. Data queue is not copied!
ServerTCP::ServerTCP(const ServerTCP &other):_port(other.get_port()),_callback(other.get_callback()),
										_running(true), _data(new queue<string>), _thread() {
}
// assigns only port and callback function. Data queue is not copied, running flag is set to true.
ServerTCP& ServerTCP::operator=(const ServerTCP &other){
	if (&other == this)
		return *this;
	else {
		this->_port = other.get_port();
		this->_callback = other.get_callback();
		this->_running = true;
		return *this;
	}
} 
// sets flag to false and if thread is joinable (meaning that no one called stop() before), waits for the thread to finish.
// Deallocates data queue.
ServerTCP::~ServerTCP() {
	_running = false;
	if (_thread.joinable())
		_thread.join();
	delete _data;
}
// setting flag to true and starting the servers thread with the main run() routine.
void ServerTCP::start(){
	_running = true;
	_thread = thread(&ServerTCP::run, this);
}
// stops the server by setting _running flag to false.
// Waiting for the servers thread to finish its execution.
void ServerTCP::stop(){
	_running = false;
	if (_thread.joinable())
		_thread.join();
}
// this method is the servers main routine.
// 		1. Creates a listener socket and bind it to the given port
// 		2. Start listening on the given port.
// 		3. Sets all sockets to be non-blocking.
// 		4. Creates a set to hold all active sockets (connection)
// 		5. While running flag is true:
// 			5.1 Check for changes in active sockets.
// 			5.2 If listener socket has new connection - Accept it and add to set.
// 			5.3 If some client socket received data (bytes > 0) - Handle it.
// 		6. Close all sockets - terminate server.
void ServerTCP::run(){
  // listener socket
	int listener_fd;
  // hold the maximum file descriptor number from the active sockets
	int max_fd;
	// wraps the sockets detailed implementation. See SocketWrapper for details.
	SocketWrapper socket_wrapper;

	// 1.
	listener_fd = socket_wrapper.socket_bind(_port);
	// 2.
	socket_wrapper.start_listen(listener_fd, BACKLOG);
	cout << "Escutando na porta: " << _port << "..." << endl;
  // 3.
  socket_wrapper.set_nonblock(listener_fd);
  // 4.
  socket_wrapper.create_sets(listener_fd);
  max_fd = listener_fd;

  // 5.
  while(_running) {
    //5.1
    socket_wrapper.start_select(max_fd, TIMEOUT_SEC, TIMEOUT_USEC);
    for (int i=0; i < max_fd+1; i++) {
      // 5.2
      if (i == listener_fd) {
        max_fd = socket_wrapper.check_new_connection(listener_fd, max_fd);
      }
      //5.3
      else {
        string data;
        int bytes = socket_wrapper.receive_data(i, BUFFER_SIZE, data);
        if (bytes > 0) {
          socket_wrapper.respond_ok(i);
          handler(data);
        }
      }
    }
  }
  // 6.
  socket_wrapper.close_all(max_fd);
}

// handles incoming data - adding data to queue and calling callback function
void ServerTCP::handler(string incoming_data){
	// call the callback function with the incoming data
	_callback(incoming_data);

	// add data to the internal data queue
	_data->push(incoming_data);
}

// pop data from queue if available.
string ServerTCP::pop_data(){
	if (!_data->empty()){
		string data = _data->front();
		cout << "Pop! " << _data->front() << endl;
		_data->pop();
		return data;
	}
	else{
		cout << "Não existe nenhum dado na fila" << endl;
		return "";
	}
}
// get port 
int ServerTCP::get_port() const{
	return _port;
}
// get callback function
callback_t ServerTCP::get_callback() const{
	return _callback;
}

// !!!! Code below is for testing purpose only !!!!
void print(string print){
	cout << "Callback Function: " << print << endl;
}
void print2(string print){
	cout << "Callback Function2: " << print << endl;
}

int main (int argc, char *argv[]) {
	ServerTCP tcp_server(5555, &print);
	ServerTCP tcp_server2(3333, &print2);

	tcp_server.start();
	tcp_server2.start();
	sleep(60);
	tcp_server.pop_data();
	tcp_server.pop_data();
	tcp_server2.stop();
	cout << "server on 3333 stopped" << endl;
	tcp_server2.pop_data();
	tcp_server2.pop_data();
	sleep(30);
}

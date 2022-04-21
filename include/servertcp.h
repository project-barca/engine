#ifndef SERVERTCP_H_
#define SERVERTCP_H_
// maximum number of connection waiting to be accepted
#define BACKLOG 5
// timeout parameter for select() - in seconds
#define TIMEOUT_SEC 3
// timeout parameter for select() - in micro seconds
#define TIMEOUT_USEC 0
// incoming data buffer size (maximum bytes per incoming data)
#define BUFFER_SIZE 512

using namespace std;

// callback type - receives string as argument and returns void
typedef void (*callback_t) (string);

 // ServerTCP Class Declaration
 // this class accepts incoming TCP connection on a given port and handles incoming data.
 // The main routine (run()) runs in a separate thread to allow the main program to continue its execution.
 // On each incoming data it:
 // 		1. Respond with "OK"
 // 		2. Call the callback function with the incoming data (as string)
 // 		3. Add the incoming data to an internal queue
class ServerTCP {
  public:
    // receives port as integer and a callback function as callback_t type.
    ServerTCP(int, callback_t);
    // copy constructor.
    ServerTCP(const ServerTCP &other);
    // assignment Operator.
    ServerTCP& operator=(const ServerTCP &other);
    // destructor.
    virtual ~ServerTCP();
    // getters for port and callback function
    int get_port() const;
    callback_t get_callback() const;	
    // public function to pop data from the internal queue.
    string pop_data();
    // starts the internal thread that executes the main routine (run()).
    void start();
    // stops the main routine and the internal thread.
    void stop();

  private:
    // local Variables
    // listener port
    int _port;
    // pointer to the callback function
    callback_t _callback;
    // flag for starting and terminating the main loop
    bool _running;
    // queue for saving incoming data
    queue<string>* _data;
    // internal thread, this is in order to start and stop the thread from different class methods
    thread _thread;
    // this method handles incoming data. Calling callback function and adding data to queue.
    void handler(string);	
    // this is the main routine of this class.
    // It accepts incoming connection and receives incoming data from these connections.
    // It is private because it is only executed in a different thread by start() method.
    void run();
};

#endif
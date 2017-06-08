#include <thread>
#include <atomic>
#include <iostream>
#include <cstring>
#include <event2/event.h>
#include <event2/thread.h>
#include <event2/listener.h>
#include <unistd.h>


#define WAIT_TIME 2

struct event_base *base;
std::atomic <bool> m_active_thread;


void accept_error_cb(struct evconnlistener *listener, void *ctx) {}

void server_thread(){
  std::cout << "Running the dispatcher ..." << std::endl;
  event_base_dispatch(base);
  event_base_free(base);
  
  m_active_thread.store(false);
  std::cout << "Dead" << std::endl;
}

static void print_logs(int severity, const char *msg) {
  std::cout << severity << ". " << msg << std::endl;
}

void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen,
                            void *ctx)
{
  std::cout << "Who's connected to us ??" << std::endl;
}

int main() {
  struct sockaddr_in sin;
  struct evconnlistener *listener;
  event_set_log_callback(print_logs);
  std::cout << "PID is " << getpid() << std::endl;
  
  /* Configure and enable libevent.
     Create an second thread dispatching the events. We'll call it the dispatcher thread.
     Wait WAIT_TIME seconds to mockup the application execution
     Decide it's time to leave and tell the other thread/libevent to quit the event dispatching loop.
     Wait for the other thread to report its end of activity, join it and quit. */

  base = event_base_new();
  if (!base) {
    perror("Couldn't open event base");
    return -1;
  }
  
  std::memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = htonl(0);
  sin.sin_port = htons(1234);
  
  listener = evconnlistener_new_bind(base, accept_conn_cb, NULL, 0, -1, (struct sockaddr*) &sin, sizeof(sin));
  if (!listener) {
    perror("Couldn't create listener");
    return -1;
  }
      
  evthread_use_pthreads();

  /* Libevent is set up, now start the dispatcher thread,
     wait a bit and kill it.  */

  m_active_thread.store(true);
  std::thread m_thread(server_thread);
  
  std::cout << "Sleeping for " << WAIT_TIME << " seconds ..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME*1000));
  
  std::cout << "And killing the application." << std::endl;
  event_base_loopbreak(base);

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (not m_active_thread.load()) {
      break;
    }
    std::cout << "Waiting for the thread to die ... (try ^z/fg, SIGSTOP/SIGINT)" << std::endl;
  }

  m_thread.join();
  std::cout << "Bye everybody." << std::endl;
}

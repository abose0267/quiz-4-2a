#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// include additional necessary headers

void query(std::mutex *m, int no) {
  // Should print: the print number (starting from 0), "SYN", and the three dots
  std::unique_lock<std::mutex> l(*m);

  std::cout << "[" << no << "]"
            << " SYN ...";

  l.unlock();
  // "..."
}

void response(std::mutex *m) {
  // Should print "ACK"
  std::unique_lock<std::mutex> l(*m);

  std::cout << " ACL\n";
  l.unlock();
}

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("Usage: ./handshake <count>\n");
    exit(1);
  }

  int count = atoi(argv[1]);

  std::mutex m;
  std::vector<std::thread> tVec1;
  std::vector<std::thread> tVec2;
  for (int i = 0; i < count; i++) {

    std::thread t1 = std::thread(query, &m, i);
    std::thread t2 = std::thread(response, &m);

    t1.join();
    t2.join();
  }

  /**
   * Steps to follow:
   * 1. Get the "count" from cmd args

   * 2. Create necessary synchronization primitive(s)
   * 3. Create two threads, one for "SYN" and the other for "ACK"
   * 4. Provide the threads with necessary args
   * 5. Update the "query" and "response" functions to synchronize the output
  */

  return 0;
}
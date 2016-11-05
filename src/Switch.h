/**
 * Switch.h
 * Part of CSE353, Project 2 by Ian Neal and Sean Turner
 */

#pragma once

// trim this down later;
#include <atomic>
#include <cerrno>
#include <condition_variable>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include <arpa/inet.h>
#include <lib/PracticalSocket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <queue>
#include <sys/types.h>
#include <sys/socket.h>
#include "Frame.h"

namespace FreeLunch { // ok I'm just being silly, we can get rid of this in prod :)

namespace Always {

template <typename S, typename T>
struct Tuple {
  S s;
  T t;
};

class Switch {
public:

protected:
  sync_queue<Frame> frame_buffer; // this needs to be a tuple
  // <port, _num>? This may need to change.
  std::unordered_map<uint8_t, uint8_t> switch_table;
};

// TODO: rewrite this queue to be lockfree if we have time
/**
 * from Stroustrup section 42.3.4
 */
template <typename S, typename T>
class sync_queue {
public:
  void put(const T& val);
  void put(const T&& val);
  void get(T& val);
  void peek(T& val);
  bool empty() { return q.empty(); }
private:
  std::mutex mtx;
  std::condition_variable cond;
  std::priority_queue<Tuple<S, T>, vector<Tuple<S, T>>, CompareTuple<S, T> q;
};

template <typename S, typename T>
class CompareTuple {
public:
  bool operator()(Tuple<S, T>& t1, Tuple<S, T>& t2) {
    if (t1.s < t2.s) return true;
    return false;
  }
};


/**
 * code from:
 * https://stackoverflow.com/questions/15033827/multiple-threads-writing-to-stdcout-or-stdcerr
 * to solve problems with threads writing to streams
 *
 * I used this to get around some weird problems in p1. Streams *should* be threadsafe,
 * but I'm throwing this in just in case.
 */
class AtomicWriter {
  std::ostringstream st;
  std::ostream &stream;
public:
  AtomicWriter(std::ostream &s=std::cout):stream(s) { }
  template <typename T>
  AtomicWriter& operator<<(T const& t) {
    st << t;
    return *this;
  }
  AtomicWriter& operator<<( std::ostream&(*f)(std::ostream&) ) {
    st << f;
    return *this;
  }
  ~AtomicWriter() { stream << st.str(); }
};

} // namespace Always

} // namespace FreeLunch
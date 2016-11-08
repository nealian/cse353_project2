#pragma once

#include <string>
#include <cstdint>

#define MAX_FRAME_SZ 260 // 1 byte for each SRC, DST, and SIZE/ACK, potentially 2 more bytes for
// DST and PRIORITY on frames with priority, and 255 bytes for DATA.

class Frame {
public:
  // Getters
  uint8_t src();
  uint8_t dst();
  uint8_t size();
  std::string data();
  std::string raw();

  // Setters
  void clear();

  // Constructors
  Frame(std::string contents);
  Frame(uint8_t src, uint8_t dst, std::string data, uint8_t priority) :
      _SRC{src}, _DST{dst}, _DATA{data}, _priority{priority} {};
  Frame(uint8_t src, uint8_t dst, std::string data) : Frame(src, dst, data, 0) {};
  Frame(const Frame &) = default; // For function parameters
  Frame(Frame &&) = default; // For function return values

  // Operators
  bool operator<(const Frame f2) const {return _priority < f2._priority;};
  Frame& operator=(const Frame&) = default;

protected:
  uint8_t _SRC;
  uint8_t _DST;
  std::string _DATA;
  uint8_t _priority;
};

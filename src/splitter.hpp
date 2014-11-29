#ifndef __SPLITTER_HPP__
#define __SPLITTER_HPP__

#include <string>
#include <utility>
#include <vector>

class Splitter {
public:
  typedef std::pair<size_t, size_t> Bound;
  typedef std::vector<Bound> Bounds;
  virtual void Split(const std::string&, Bounds&) const = 0;
};

struct SplitterOption {
public:
  enum SplitterType {
    SPLITTER_TYPE_LENGTH = 0,
    SPLITTER_TYPE_WORD,
  };
  SplitterType type;
  size_t length;
  std::string delims;
};

Splitter* CreateSplitter(const SplitterOption& option);

#endif//__SPLITTER_HPP__

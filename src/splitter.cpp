#include "splitter.hpp"

#include <algorithm>

class LengthSplitter : public Splitter {
public:
  LengthSplitter(size_t len)
    : length_(len)
  {
    if (length_ <= 0) {
      length_ = 1;
    }
  }

  void Split(const std::string& str, Bounds& bounds) const
  {
    Bounds result;
    size_t beg = 0;
    while (beg < str.length()) {
      size_t end = std::min(beg + length_, str.length());
      result.push_back(std::make_pair(beg, end));
      beg = end;
    }
    bounds.swap(result);
  }

private:
  size_t length_;
};

class WordSplitter : public Splitter {
public:
  WordSplitter(const std::string& delims)
    : delims_(delims)
  {
  }

  void Split(const std::string& str, Bounds& bounds) const
  {
    Bounds result;
    size_t beg = 0;
    bool is_first = true;
    while (beg < str.length()) {
      beg = is_first ? beg : beg + 1;
      is_first = false;
      size_t end = str.find_first_of(delims_, beg);
      if (end == std::string::npos) {
        end = str.length();
      }
      result.push_back(std::make_pair(beg, end));
      beg = end;
    }
    bounds.swap(result);
  }

private:
  std::string delims_;
};


Splitter* CreateSplitter(const SplitterOption& option)
{
  switch (option.type) {

  case SplitterOption::SPLITTER_TYPE_LENGTH:
    return new LengthSplitter(option.length);

  case SplitterOption::SPLITTER_TYPE_WORD:
    return new WordSplitter(option.delims);

  default:
    return NULL;
  }
}

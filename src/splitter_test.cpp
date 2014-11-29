#include <gtest/gtest.h>

#include "splitter.hpp"

class LengthSplitterTest : public ::testing::Test
{
protected:

  void SetUp() {
    option.type = SplitterOption::SPLITTER_TYPE_LENGTH;
    splitter = NULL;
  }

  void TearDown() {
    if (splitter) {
      delete splitter;
    }
  }

  SplitterOption option;
  Splitter* splitter;
  Splitter::Bounds result;
};

TEST_F(LengthSplitterTest, SplitEach) {
  option.length = 1;
  splitter = CreateSplitter(option);
  splitter->Split("foobar", result);

  Splitter::Bounds expected;
  expected.push_back(std::make_pair(0, 1));
  expected.push_back(std::make_pair(1, 2));
  expected.push_back(std::make_pair(2, 3));
  expected.push_back(std::make_pair(3, 4));
  expected.push_back(std::make_pair(4, 5));
  expected.push_back(std::make_pair(5, 6));

  EXPECT_EQ(expected, result);
}

TEST_F(LengthSplitterTest, SplitByEachThree) {
  option.length = 3;
  splitter = CreateSplitter(option);
  splitter->Split("foobarbaz", result);

  Splitter::Bounds expected;
  expected.push_back(std::make_pair(0, 3));
  expected.push_back(std::make_pair(3, 6));
  expected.push_back(std::make_pair(6, 9));

  EXPECT_EQ(expected, result);
}

TEST_F(LengthSplitterTest, SplitByBigNumber) {
  option.length = 1000;
  splitter = CreateSplitter(option);
  splitter->Split("foobarbaz", result);

  Splitter::Bounds expected;
  expected.push_back(std::make_pair(0, 9));

  EXPECT_EQ(expected, result);
}

class WordSplitterTest : public ::testing::Test
{
protected:

  void SetUp() {
    option.type = SplitterOption::SPLITTER_TYPE_WORD;
    splitter = NULL;
  }

  void TearDown() {
    if (splitter) {
      delete splitter;
    }
  }

  SplitterOption option;
  Splitter* splitter;
  Splitter::Bounds result;
};

TEST_F(WordSplitterTest, SplitBySpace) {
  option.delims = " ";
  splitter = CreateSplitter(option);
  splitter->Split("foo bar baz", result);

  Splitter::Bounds expected;
  expected.push_back(std::make_pair(0, 3));
  expected.push_back(std::make_pair(4, 7));
  expected.push_back(std::make_pair(8, 11));

  EXPECT_EQ(expected, result);
}

TEST_F(WordSplitterTest, SplitByMultiChars) {
  option.delims = " ,\t";
  splitter = CreateSplitter(option);
  splitter->Split("foo bar,baz\tfoobar", result);

  Splitter::Bounds expected;
  expected.push_back(std::make_pair(0, 3));
  expected.push_back(std::make_pair(4, 7));
  expected.push_back(std::make_pair(8, 11));
  expected.push_back(std::make_pair(12, 18));

  EXPECT_EQ(expected, result);
}

TEST_F(WordSplitterTest, SplitEmpty) {
  option.delims = " ";
  splitter = CreateSplitter(option);
  splitter->Split("", result);

  Splitter::Bounds expected;

  EXPECT_EQ(expected, result);
}

TEST_F(WordSplitterTest, SplitByEmpty) {
  option.delims = "";
  splitter = CreateSplitter(option);
  splitter->Split("foo bar baz", result);

  Splitter::Bounds expected;
  expected.push_back(std::make_pair(0, 11));

  EXPECT_EQ(expected, result);
}

TEST_F(WordSplitterTest, SplitContinuedDelims) {
  option.delims = " ";
  splitter = CreateSplitter(option);
  splitter->Split("foo  bar   baz", result);

  Splitter::Bounds expected;
  expected.push_back(std::make_pair(0, 3));
  expected.push_back(std::make_pair(4, 4));
  expected.push_back(std::make_pair(5, 8));
  expected.push_back(std::make_pair(9, 9));
  expected.push_back(std::make_pair(10, 10));
  expected.push_back(std::make_pair(11, 14));

  EXPECT_EQ(expected, result);
}

TEST_F(WordSplitterTest, SplitTrailedDelim) {
  option.delims = " ";
  splitter = CreateSplitter(option);
  splitter->Split("foo ", result);

  Splitter::Bounds expected;
  expected.push_back(std::make_pair(0, 3));
  expected.push_back(std::make_pair(4, 4));

  EXPECT_EQ(expected, result);
}

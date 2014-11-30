bin_PROGRAMS =
check_PROGRAMS =
TESTS=

bin_PROGRAMS+= rev2
rev2_SOURCES= rev2.cpp splitter.hpp splitter.cpp

check_PROGRAMS += splitter_test
splitter_test_SOURCES = splitter.hpp splitter.cpp splitter_test.cpp
splitter_test_CPPFLAGS = $(GTEST_CPPFLAGS)
splitter_test_CXXFLAGS = $(GTEST_CXXFLAGS)
splitter_test_LDFLAGS = $(GTEST_LDFLAGS)
splitter_test_LDADD = $(GTEST_LIBS) \
                      $(top_builddir)/lib/gmock/libgmock_main.la \
                      $(top_builddir)/lib/gmock/libgmock.la
TESTS += splitter_test

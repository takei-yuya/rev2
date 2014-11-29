check_LTLIBRARIES = \
  gmock/libgmock.la \
  gmock/libgmock_main.la

gmock_libgmock_la_SOURCES = \
  gmock/gmock/gmock.h \
  gmock/gtest/gtest.h \
  gmock/gmock-gtest-all.cc
gmock_libgmock_la_CPPFLAGS = $(GTEST_CPPFLAGS)
gmock_libgmock_la_CXXFLAGS = $(GTEST_CXXFLAGS)
gmock_libgmock_la_LDFLAGS = $(GTEST_LDFLAGS)
gmock_libgmock_la_LIBADD = $(GTEST_LIBS)

gmock_libgmock_main_la_SOURCES = \
  gmock/gmock/gmock.h \
  gmock/gtest/gtest.h \
  gmock/gmock_main.cc
gmock_libgmock_main_la_CPPFLAGS = $(GTEST_CPPFLAGS)
gmock_libgmock_main_la_CXXFLAGS = $(GTEST_CXXFLAGS)
gmock_libgmock_main_la_LDFLAGS = $(GTEST_LDFLAGS)
gmock_libgmock_main_la_LIBADD = \
  $(GTEST_LIBS) \
  gmock/libgmock.la


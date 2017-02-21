AM_CPPFLAGS = $(CXX14_FLAGS)
AM_CXXFLAGS = $(PICKY_CXXFLAGS)

noinst_LIBRARIES = libutil.a

libutil_a_SOURCES = exception.hh zero.hh \
	file_descriptor.hh file_descriptor.cc \
	socket.hh socket-impl.hh \
	unix_address.hh unix_address.cc \
	unix_stream_socket.hh unix_stream_socket.cc

AM_CPPFLAGS = $(CXX14_FLAGS) -I$(srcdir)/../util
AM_CXXFLAGS = $(PICKY_CXXFLAGS)

bin_PROGRAMS = agent-passthrough
agent_passthrough_SOURCES = agent-passthrough.cc
agent_passthrough_LDADD = ../util/libutil.a
agent_passthrough_LDFLAGS = -pthread

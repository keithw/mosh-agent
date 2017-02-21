/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include "unix_stream_socket.hh"
#include "socket-impl.hh"

template class Socket<UnixAddress, AF_UNIX, SOCK_STREAM>;

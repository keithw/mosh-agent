/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include "unix_address.hh"
#include "socket.hh"

using UnixStreamSocket = Socket<UnixAddress, AF_UNIX, SOCK_STREAM>;

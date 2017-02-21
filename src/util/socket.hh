/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#pragma once

#include <sys/socket.h>
#include <functional>
#include "file_descriptor.hh"

/* class for sockets */
template <class AddressType, int domain, int type>
class Socket : public FileDescriptor
{
private:
  /* get the local or peer address the socket is connected to */
  AddressType get_address( const std::string & name_of_function,
                           const std::function<int(int, sockaddr *, socklen_t *)> & function ) const;

public:
  /* default constructor */
  Socket();

  /* construct from file descriptor */
  Socket( FileDescriptor && s_fd );

  /* get and set socket option */
  template <typename option_type>
  socklen_t getsockopt( const int level, const int option, option_type & option_value ) const;

  template <typename option_type>
  void setsockopt( const int level, const int option, const option_type & option_value );

  /* bind socket to a specified local address (usually to listen/accept) */
  void bind( const AddressType & address );

  /* connect socket to a specified peer address */
  void connect( const AddressType & address );

  /* mark the socket as listening for incoming connections */
  void listen( const int backlog );

  /* accept an incoming connection */
  Socket accept();

  /* accessors */
  AddressType local_address() const;
  AddressType peer_address() const;
};

/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#pragma once

#include "socket.hh"
#include "exception.hh"

/* default constructor for socket of (subclassed) domain and type */
template <class AddressType, int domain, int type>
Socket<AddressType, domain, type>::Socket()
  : FileDescriptor( SystemCall( "socket", socket( domain, type, 0 ) ) )
{}

/* construct from file descriptor */
template <class AddressType, int domain, int type>
Socket<AddressType, domain, type>::Socket( FileDescriptor && fd )
  : FileDescriptor( std::move( fd ) )
{
  int actual_value;
  socklen_t len;

  /* verify domain */
  len = getsockopt( SOL_SOCKET, SO_DOMAIN, actual_value );
  if ( (len != sizeof( actual_value )) or (actual_value != domain) ) {
    throw std::runtime_error( "socket domain mismatch" );
  }

  /* verify type */
  len = getsockopt( SOL_SOCKET, SO_TYPE, actual_value );
  if ( (len != sizeof( actual_value )) or (actual_value != type) ) {
    throw std::runtime_error( "socket type mismatch" );
  }
}

/* get the local or peer address the socket is connected to */
template <class AddressType, int domain, int type>
AddressType Socket<AddressType, domain, type>::get_address( const std::string & name_of_function,
                                                            const std::function<int(int, sockaddr *, socklen_t *)> & function ) const
{
  typename AddressType::raw address;
  socklen_t size = sizeof( address );

  SystemCall( name_of_function, function( fd_num(),
                                          &address.as_sockaddr,
                                          &size ) );

  return AddressType( address, size );
}

template <class AddressType, int domain, int type>
AddressType Socket<AddressType, domain, type>::local_address() const
{
  return get_address( "getsockname", getsockname );
}

template <class AddressType, int domain, int type>
AddressType Socket<AddressType, domain, type>::peer_address() const
{
  return get_address( "getpeername", getpeername );
}

/* bind socket to a specified local address (usually to listen/accept) */
template <class AddressType, int domain, int type>
void Socket<AddressType, domain, type>::bind( const AddressType & address )
{
  SystemCall( "bind " + address.str(), ::bind( fd_num(),
                                               &address.to_sockaddr(),
                                               address.size() ) );
}

/* connect socket to a specified peer address */
template <class AddressType, int domain, int type>
void Socket<AddressType, domain, type>::connect( const AddressType & address )
{
  SystemCall( "connect " + address.str(), ::connect( fd_num(),
                                                     &address.to_sockaddr(),
                                                     address.size() ) );
}

/* mark the socket as listening for incoming connections */
template <class AddressType, int domain, int type>
void Socket<AddressType, domain, type>::listen( const int backlog )
{
  SystemCall( "listen", ::listen( fd_num(), backlog ) );
}

/* accept an incoming connection */
template <class AddressType, int domain, int type>
Socket<AddressType, domain, type> Socket<AddressType, domain, type>::accept()
{
  register_read();
  return FileDescriptor( SystemCall( "accept", ::accept( fd_num(), nullptr, nullptr ) ) );
}

/* get socket option */
template <class AddressType, int domain, int type>
template <typename option_type>
socklen_t Socket<AddressType, domain, type>::getsockopt( const int level, const int option, option_type & option_value ) const
{
  socklen_t optlen = sizeof( option_value );
  SystemCall( "getsockopt", ::getsockopt( fd_num(), level, option,
                                          &option_value, &optlen ) );
  return optlen;
}

/* set socket option */
template <class AddressType, int domain, int type>
template <typename option_type>
void Socket<AddressType, domain, type>::setsockopt( const int level, const int option, const option_type & option_value )
{
  SystemCall( "setsockopt", ::setsockopt( fd_num(), level, option,
                                          &option_value, sizeof( option_value ) ) );
}

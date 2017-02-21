/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include <cstring>

#include "unix_address.hh"
#include "exception.hh"
#include "zero.hh"

using namespace std;

UnixAddress::UnixAddress( const raw & addr, const size_t size )
  : size_( size ),
    addr_()
{
  /* make sure proposed sockaddr can fit */
  if ( size > sizeof( addr_ ) ) {
    throw runtime_error( "invalid sockaddr size" );
  }

  if ( addr.as_sockaddr_un.sun_family != AF_UNIX ) {
    throw runtime_error( "invalid sockaddr_un family" );
  }

  memcpy( &addr_, &addr, size_ );
}

UnixAddress::raw make_sockaddr_un( const string & pathname )
{
  UnixAddress::raw ret;
  zero( ret );
  ret.as_sockaddr_un.sun_family = AF_UNIX;

  if ( pathname.size() + 1 > sizeof( ret.as_sockaddr_un.sun_path ) ) {
    throw runtime_error( "pathname too long for Unix-domain address: " + pathname );
  }

  if ( strlen( pathname.c_str() ) != pathname.size() ) {
    throw runtime_error( "invalid pathname: " + pathname );
  }

  strncpy( ret.as_sockaddr_un.sun_path, pathname.c_str(), sizeof( ret.as_sockaddr_un.sun_path ) );

  return ret;
}

UnixAddress::UnixAddress( const string & pathname )
  : UnixAddress( make_sockaddr_un( pathname ), sizeof( UnixAddress::raw ) )
{}

string UnixAddress::pathname() const
{
  const size_t pathname_len = strnlen( addr_.as_sockaddr_un.sun_path,
                                       size_ - offsetof( sockaddr_un, sun_path ) );
  return { addr_.as_sockaddr_un.sun_path, pathname_len };
}

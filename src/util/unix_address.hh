/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include <sys/socket.h>
#include <sys/un.h>

#include <string>

class UnixAddress
{
public:
  typedef union {
    sockaddr as_sockaddr;
    sockaddr_un as_sockaddr_un;
  } raw;

private:
  socklen_t size_;
  raw addr_;

public:
  /* constructors */
  UnixAddress( const raw & addr, const size_t size );
  UnixAddress( const std::string & pathname );

  /* accessors */
  std::string pathname() const;
  std::string str() const { return pathname(); }
  socklen_t size( void ) const { return size_; }
  const sockaddr & to_sockaddr( void ) const { return addr_.as_sockaddr; }
};

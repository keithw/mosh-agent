/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include <cstdlib>

#include "unix_stream_socket.hh"
#include "exception.hh"

using namespace std;

int main()
{
  try{
    UnixStreamSocket s;

    s.bind( UnixAddress( "/tmp/hello.socket" ) );

    return EXIT_SUCCESS;
  } catch ( const exception & e ) {
    print_exception( e );
    return EXIT_FAILURE;
  }
}

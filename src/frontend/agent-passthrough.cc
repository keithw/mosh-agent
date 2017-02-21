/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include <cstdlib>
#include <vector>
#include <thread>

#include "unix_stream_socket.hh"
#include "exception.hh"

using namespace std;

int main()
{
  try{
    UnixStreamSocket s;

    s.bind( UnixAddress( "/tmp/hello.socket" ) );

    s.listen( 16 );

    std::vector<thread> threads;

    while ( true ) {
      UnixStreamSocket connection = s.accept();

      threads.emplace_back( [] ( UnixStreamSocket connection ) {
          cerr << "Accepted new connection.\n";

          while ( not connection.eof() ) {
            const string str = connection.read();
            if ( str.size() ) {
              cout << "Got " << str.size() << " bytes:";
              for ( const char x : str ) {
                cout << " " << int( x );
              }
              cout << "\n";
            }
          }

          cerr << "Closing connection.\n";
          connection.close();
        }, move( connection ) );
    }

    for ( auto & the_thread : threads ) {
      the_thread.join();
    }

    s.close();

    return EXIT_SUCCESS;
  } catch ( const exception & e ) {
    print_exception( e );
    return EXIT_FAILURE;
  }
}

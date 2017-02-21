/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#pragma once

#include <string>

/* Unix file descriptors (sockets, files, etc.) */
class FileDescriptor
{
private:
  int fd_;
  bool eof_;

  unsigned int read_count_, write_count_;

  /* maximum size of a read */
  const static size_t BUFFER_SIZE = 1024 * 1024;

protected:
  void register_read() { read_count_++; }
  void register_write() { write_count_++; }
  void set_eof() { eof_ = true; }

public:
  /* construct from fd number */
  FileDescriptor( const int fd );

  /* close method */
  void close();

  /* move constructor */
  FileDescriptor( FileDescriptor && other );

  /* destructor */
  ~FileDescriptor();

  /* accessors */
  const int & fd_num() const { return fd_; }
  const bool & eof() const { return eof_; }
  unsigned int read_count() const { return read_count_; }
  unsigned int write_count() const { return write_count_; }

  /* read and write methods */
  std::string read( const size_t limit = BUFFER_SIZE );
  std::string::const_iterator write( const std::string & buffer, const bool write_all = true );
  std::string::const_iterator write( const std::string::const_iterator & begin,
                                     const std::string::const_iterator & end );

  /* forbid copying FileDescriptor objects or assigning them */
  FileDescriptor( const FileDescriptor & other ) = delete;
  const FileDescriptor & operator=( const FileDescriptor & other ) = delete;
};

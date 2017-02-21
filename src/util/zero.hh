/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#pragma once

#include <cstring>

template <typename T>
void zero( T & x ) {
  memset( &x, 0, sizeof( x ) );
}

#ifndef SIMPLEX_SUPPORT_ASSERT_H
#define SIMPLEX_SUPPORT_ASSERT_H

#include <Simplex/Support/TypeDefs.h>
#include <execinfo.h>
#include <iostream>

#ifndef NDEBUG
  #include <cassert>
  #define ASSERT(condition) \
  { \
      if(!(condition)) \
      { \
          std::cerr << "\n\nAssertion failed at " << __FILE__ << ":" << __LINE__; \
          std::cerr << " inside " << __FUNCTION__ << std::endl; \
          std::cerr << "Condition: " << #condition << std::endl; \
          printStackTrace(); \
          abort(); \
      } \
  }
#else
  #define ASSERT(condition) (condition)
#endif


static inline void printStackTrace(U32 max_frames = 63 )
{
   fprintf(stderr, "stack trace:\n");

   // storage array for stack trace address data
   void* addrlist[max_frames+1];

   // retrieve current stack addresses
   U32 addrlen = backtrace( addrlist, sizeof( addrlist ) / sizeof( void* ));

   if ( addrlen == 0 )
   {
      fprintf( stderr, "  \n" );
      return;
   }

   // create readable strings to each frame.
   char** symbollist = backtrace_symbols( addrlist, addrlen );

   // print the stack trace.
   for ( U32 i = 4; i < addrlen; i++ )
      fprintf( stderr, "%s\n", symbollist[i]);

   free(symbollist);
}

#endif
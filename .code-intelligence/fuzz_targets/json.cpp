#include <stddef.h>
#include <stdint.h>

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/json.hpp>
#include <tao/pegtl/memory_input.hpp>
#include <tao/pegtl/nothing.hpp>
#include <tao/pegtl/parse.hpp>


extern "C" int FUZZ( const char* Data, size_t Size )
{
   if( Size < 1 ) {
      return 0;
   }

   std::string s( Data, Size );
   using grammar = tao::pegtl::must< tao::pegtl::json::text, tao::pegtl::eof >;

   tao::pegtl::memory_input<> in( Data, Size, "" );
   try {
      tao::pegtl::parse< grammar >( in );
   }
   catch( ... ) {
   }
   return 0;  // Non-zero return values are reserved for future use.
}

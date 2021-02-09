#include <stdint.h>
#include <stddef.h>

#include <iomanip>
#include <iostream>
#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/json.hpp>
#include <tao/pegtl/contrib/trace.hpp>
#include "json_errors.hpp"

#include <string_view>



namespace pegtl = TAO_PEGTL_NAMESPACE;

namespace example
{
   using grammar = pegtl::must< pegtl::json::text, pegtl::eof >;

}  // namespace example


//int main(int argc, char **argv);

// extern "C" int FUZZ_INIT_WITH_ARGS(int *argc, char ***argv) {
extern "C" int FUZZ_INIT() {

  // Add global setup code here - called once before fuzzing starts

  return 0;
}

extern "C" int FUZZ(const char *Data, size_t Size) {

  tao::pegtl::memory_input in(Data, Size, "" );
  try{
    tao::pegtl::parse< example::grammar, tao::pegtl::nothing, example::control >( in );
  }catch( const pegtl::parse_error& e ) {
    return 0;
  }
  

  // reset state and free all locally allocated resources

  return 0;
}

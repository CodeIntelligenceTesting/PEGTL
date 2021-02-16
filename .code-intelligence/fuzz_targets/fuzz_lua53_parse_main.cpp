#include <stdint.h>
#include <stddef.h>

#include <iostream>
#include "lua53.hpp"



int main(int argc, char **argv);

// extern "C" int FUZZ_INIT_WITH_ARGS(int *argc, char ***argv) {
extern "C" int FUZZ_INIT() {

  // Add global setup code here - called once before fuzzing starts

  return 0;
}

extern "C" int FUZZ(const char *Data, size_t Size) {

  
  TAO_PEGTL_NAMESPACE::memory_input<> in(Data, Size, "");
  try{
    const auto r = TAO_PEGTL_NAMESPACE::parse< lua53::grammar >( in );
  }catch( const tao::pegtl::parse_error& e ) {
    return 0;
  }
  return 0;
  
}

#include <stdint.h>
#include <stddef.h>

#include <iomanip>
#include <iostream>
#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/json.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>
#include <tao/pegtl/contrib/parse_tree_to_dot.hpp>
#include "json_errors.hpp"

namespace pegtl = TAO_PEGTL_NAMESPACE;

namespace example
{
   using grammar = pegtl::must< pegtl::json::text, pegtl::eof >;

   template< typename Rule >
   using selector = pegtl::parse_tree::selector<
      Rule,
      pegtl::parse_tree::remove_content::on<
         pegtl::json::null,
         pegtl::json::true_,
         pegtl::json::false_,
         pegtl::json::array,
         pegtl::json::object,
         pegtl::json::member >,
      pegtl::parse_tree::store_content::on<
         pegtl::json::number,
         pegtl::json::string,
         pegtl::json::key > >;

}  // namespace example

int main(int argc, char **argv);

// extern "C" int FUZZ_INIT_WITH_ARGS(int *argc, char ***argv) {
extern "C" int FUZZ_INIT() {

  // Add global setup code here - called once before fuzzing starts

  return 0;
}

extern "C" int FUZZ(const char *Data, size_t Size) {

  pegtl::memory_input in(Data, Size, "");
   try {
      const auto root = pegtl::parse_tree::parse< example::grammar, example::selector, pegtl::nothing, example::control >( in );
      pegtl::parse_tree::print_dot( std::cout, *root );
   }
   catch( const pegtl::parse_error& e ) {
    return 0;
  }

  return 0;
}

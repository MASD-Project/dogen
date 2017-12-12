#include <ostream>
#include "dogen/test_models/cpp_98/io/no_properties_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

std::ostream& operator<<(std::ostream& s, const no_properties&) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_98::no_properties\"" << " }";
    return(s);
}

} } }

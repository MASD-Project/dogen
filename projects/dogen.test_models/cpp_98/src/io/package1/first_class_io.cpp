#include <ostream>
#include "dogen/test_models/cpp_98/io/package1/first_class_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {
namespace package1 {

std::ostream& operator<<(std::ostream& s, const first_class& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_98::package1::first_class\"" << ", "
      << "\"public_attribute\": " << v.public_attribute() << ", "
      << "\"private_attribute\": " << v.private_attribute()
      << " }";
    return(s);
}

} } } }

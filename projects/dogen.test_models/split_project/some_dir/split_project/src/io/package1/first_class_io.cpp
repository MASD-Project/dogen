#include <ostream>
#include "dogen/test_models/split_project/io/package1/first_class_io.hpp"

namespace dogen {
namespace test_models {
namespace split_project {
namespace package1 {

std::ostream& operator<<(std::ostream& s, const first_class& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::split_project::package1::first_class\"" << ", "
      << "\"public_attribute\": " << v.public_attribute() << ", "
      << "\"private_attribute\": " << v.private_attribute()
      << " }";
    return(s);
}

} } } }

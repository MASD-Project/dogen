#include <ostream>
#include "dogen/test_models/lam_model/io/package1/class_in_package_io.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {
namespace package1 {

std::ostream& operator<<(std::ostream& s, const class_in_package& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::lam_model::package1::class_in_package\"" << ", "
      << "\"prop_0\": " << v.prop_0()
      << " }";
    return(s);
}

} } } }

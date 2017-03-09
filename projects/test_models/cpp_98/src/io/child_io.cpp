#include <ostream>
#include "dogen/test_models/cpp_98/io/child_io.hpp"
#include "dogen/test_models/cpp_98/io/parent_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

std::ostream& operator<<(std::ostream& s, const child& v) {
    v.to_stream(s);
    return(s);
}

} } }

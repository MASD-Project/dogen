#include <string>
#include <ostream>
#include <stdexcept>
#include "dogen/test_models/cpp_98/io/an_enumeration_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

std::ostream& operator<<(std::ostream& s, const an_enumeration& v) {
    s << "{ " << "\"__type__\": " << "\"an_enumeration\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case invalid:
        attr = "\"invalid\"";
        break;
    case first:
        attr = "\"first\"";
        break;
    case second:
        attr = "\"second\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for an_enumeration");
    }
    s << attr << " }";
    return s;
}

} } }

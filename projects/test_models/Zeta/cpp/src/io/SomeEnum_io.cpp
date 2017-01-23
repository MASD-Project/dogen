#include <string>
#include <ostream>
#include <stdexcept>
#include "Phi/io/SomeEnum_io.hpp"

namespace Phi {

std::ostream& operator<<(std::ostream& s, const SomeEnum& v) {
    s << "{ " << "\"__type__\": " << "\"SomeEnum\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case SomeEnum::Invalid:
        attr = "\"Invalid\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for SomeEnum");
    }
    s << attr << " }";
    return s;
}

}

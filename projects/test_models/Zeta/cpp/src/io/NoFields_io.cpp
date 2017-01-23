#include <ostream>
#include "Phi/io/NoFields_io.hpp"

namespace Phi {

std::ostream& operator<<(std::ostream& s, const NoFields&) {
    s << " { "
      << "\"__type__\": " << "\"Phi::NoFields\"" << " }";
    return(s);
}

}

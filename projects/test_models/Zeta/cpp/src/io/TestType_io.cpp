#include <ostream>
#include "Zeta/io/String_io.hpp"
#include "Phi/io/TestType_io.hpp"

namespace Phi {

std::ostream& operator<<(std::ostream& s, const TestType& v) {
    s << " { "
      << "\"__type__\": " << "\"Phi::TestType\"" << ", "
      << "\"Version\": " << v.Version() << ", "
      << "\"AField\": " << v.AField()
      << " }";
    return(s);
}

}

#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen/test_models/cpp_98/io/no_default_ctor_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen {
namespace test_models {
namespace cpp_98 {

std::ostream& operator<<(std::ostream& s, const no_default_ctor& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_98::no_default_ctor\"" << ", "
      << "\"prop_0\": " << "\"" << tidy_up_string(v.prop_0()) << "\""
      << " }";
    return(s);
}

} } }

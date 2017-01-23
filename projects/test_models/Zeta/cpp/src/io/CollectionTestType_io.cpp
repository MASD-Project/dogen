#include <ostream>
#include <boost/algorithm/string.hpp>
#include "Phi/io/CollectionTestType_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace Phi {

std::ostream& operator<<(std::ostream& s, const CollectionTestType& v) {
    s << " { "
      << "\"__type__\": " << "\"Phi::CollectionTestType\"" << ", "
      << "\"BinariesTest\": " << v.BinariesTest()
      << " }";
    return(s);
}

}

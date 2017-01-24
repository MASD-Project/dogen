#include <ostream>
#include <boost/algorithm/string.hpp>
#include "Phi/io/Date_io.hpp"
#include "Zeta/io/ExternalModelTest_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::vector<std::string> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::vector<std::vector<std::string> > >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace Zeta {

std::ostream& operator<<(std::ostream& s, const ExternalModelTest& v) {
    s << " { "
      << "\"__type__\": " << "\"Zeta::ExternalModelTest\"" << ", "
      << "\"DateTest\": " << v.DateTest() << ", "
      << "\"BinariesTest\": " << v.BinariesTest() << ", "
      << "\"CollectionOfCollectionTest\": " << v.CollectionOfCollectionTest() << ", "
      << "\"CollectionOfCollectionOfCollectionTest\": " << v.CollectionOfCollectionOfCollectionTest()
      << " }";
    return(s);
}

}

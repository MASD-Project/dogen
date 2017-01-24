#include <sstream>
#include "Phi/test_data/CollectionTestType_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::vector<std::string> create_std_vector_std_string(unsigned int position) {
    std::vector<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace Phi {

CollectionTestType_generator::CollectionTestType_generator() : position_(0) { }

void CollectionTestType_generator::
populate(const unsigned int position, result_type& v) {
    v.BinariesTest(create_std_vector_std_string(position + 0));
}

CollectionTestType_generator::result_type
CollectionTestType_generator::create(const unsigned int position) {
    CollectionTestType r;
    CollectionTestType_generator::populate(position, r);
    return r;
}

CollectionTestType_generator::result_type*
CollectionTestType_generator::create_ptr(const unsigned int position) {
    CollectionTestType* p = new CollectionTestType();
    CollectionTestType_generator::populate(position, *p);
    return p;
}

CollectionTestType_generator::result_type
CollectionTestType_generator::operator()() {
    return create(position_++);
}

}

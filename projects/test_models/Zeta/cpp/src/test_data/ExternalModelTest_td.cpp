#include <sstream>
#include "Phi/test_data/Date_td.hpp"
#include "Zeta/test_data/ExternalModelTest_td.hpp"

namespace {

Phi::Date
create_Phi_Date(const unsigned int position) {
    return Phi::Date_generator::create(position);
}

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

std::vector<std::vector<std::string> > create_std_vector_std_vector_std_string(unsigned int position) {
    std::vector<std::vector<std::string> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_vector_std_string(position + i));
    }
    return r;
}

std::vector<std::vector<std::vector<std::string> > > create_std_vector_std_vector_std_vector_std_string(unsigned int position) {
    std::vector<std::vector<std::vector<std::string> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_vector_std_vector_std_string(position + i));
    }
    return r;
}

}

namespace Zeta {

ExternalModelTest_generator::ExternalModelTest_generator() : position_(0) { }

void ExternalModelTest_generator::
populate(const unsigned int position, result_type& v) {
    v.DateTest(create_Phi_Date(position + 0));
    v.BinariesTest(create_std_vector_std_string(position + 1));
    v.CollectionOfCollectionTest(create_std_vector_std_vector_std_string(position + 2));
    v.CollectionOfCollectionOfCollectionTest(create_std_vector_std_vector_std_vector_std_string(position + 3));
}

ExternalModelTest_generator::result_type
ExternalModelTest_generator::create(const unsigned int position) {
    ExternalModelTest r;
    ExternalModelTest_generator::populate(position, r);
    return r;
}

ExternalModelTest_generator::result_type*
ExternalModelTest_generator::create_ptr(const unsigned int position) {
    ExternalModelTest* p = new ExternalModelTest();
    ExternalModelTest_generator::populate(position, *p);
    return p;
}

ExternalModelTest_generator::result_type
ExternalModelTest_generator::operator()() {
    return create(position_++);
}

}

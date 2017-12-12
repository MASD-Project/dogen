#include <sstream>
#include "dogen/test_models/cpp_98/test_data/no_default_ctor_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace test_models {
namespace cpp_98 {

no_default_ctor_generator::no_default_ctor_generator() : position_(0) { }

void no_default_ctor_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_std_string(position + 0));
}

no_default_ctor_generator::result_type
no_default_ctor_generator::create(const unsigned int position) {
    no_default_ctor r;
    no_default_ctor_generator::populate(position, r);
    return r;
}

no_default_ctor_generator::result_type*
no_default_ctor_generator::create_ptr(const unsigned int position) {
    no_default_ctor* p = new no_default_ctor();
    no_default_ctor_generator::populate(position, *p);
    return p;
}

no_default_ctor_generator::result_type
no_default_ctor_generator::operator()() {
    return create(position_++);
}

} } }

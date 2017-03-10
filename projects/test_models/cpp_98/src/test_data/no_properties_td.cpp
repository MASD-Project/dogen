#include "dogen/test_models/cpp_98/test_data/no_properties_td.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

no_properties_generator::no_properties_generator() : position_(0) { }

void no_properties_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

no_properties_generator::result_type
no_properties_generator::create(const unsigned int/*position*/) {
    no_properties r;
    return r;
}

no_properties_generator::result_type*
no_properties_generator::create_ptr(const unsigned int position) {
    no_properties* p = new no_properties();
    no_properties_generator::populate(position, *p);
    return p;
}

no_properties_generator::result_type
no_properties_generator::operator()() {
    return create(position_++);
}

} } }

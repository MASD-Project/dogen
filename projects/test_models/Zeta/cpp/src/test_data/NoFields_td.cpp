#include "Phi/test_data/NoFields_td.hpp"

namespace Phi {

NoFields_generator::NoFields_generator() : position_(0) { }

void NoFields_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

NoFields_generator::result_type
NoFields_generator::create(const unsigned int/*position*/) {
    NoFields r;
    return r;
}

NoFields_generator::result_type*
NoFields_generator::create_ptr(const unsigned int position) {
    NoFields* p = new NoFields();
    NoFields_generator::populate(position, *p);
    return p;
}

NoFields_generator::result_type
NoFields_generator::operator()() {
    return create(position_++);
}

}

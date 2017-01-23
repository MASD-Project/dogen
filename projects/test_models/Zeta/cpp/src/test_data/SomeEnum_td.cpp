#include "Phi/test_data/SomeEnum_td.hpp"

namespace Phi {

SomeEnum_generator::SomeEnum_generator() : position_(0) { }
void SomeEnum_generator::
populate(const unsigned int position, result_type& v) {
    v = static_cast<SomeEnum>(position % 1);
}

SomeEnum_generator::result_type
SomeEnum_generator::create(const unsigned int  position) {
    result_type r;
    SomeEnum_generator::populate(position, r);
    return r;
}

SomeEnum_generator::result_type
SomeEnum_generator::operator()() {
    return create(position_++);
}

}

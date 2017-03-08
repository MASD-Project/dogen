#include "dogen/test_models/split_project/test_data/package1/first_class_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace dogen {
namespace test_models {
namespace split_project {
namespace package1 {

first_class_generator::first_class_generator() : position_(0) { }

void first_class_generator::
populate(const unsigned int position, result_type& v) {
    v.public_attribute(create_int(position + 0));
    v.private_attribute(create_int(position + 1));
}

first_class_generator::result_type
first_class_generator::create(const unsigned int position) {
    first_class r;
    first_class_generator::populate(position, r);
    return r;
}

first_class_generator::result_type*
first_class_generator::create_ptr(const unsigned int position) {
    first_class* p = new first_class();
    first_class_generator::populate(position, *p);
    return p;
}

first_class_generator::result_type
first_class_generator::operator()() {
    return create(position_++);
}

} } } }

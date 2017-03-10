#include "dogen/test_models/lam_model/test_data/package1/class_in_package_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace dogen {
namespace test_models {
namespace lam_model {
namespace package1 {

class_in_package_generator::class_in_package_generator() : position_(0) { }

void class_in_package_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
}

class_in_package_generator::result_type
class_in_package_generator::create(const unsigned int position) {
    class_in_package r;
    class_in_package_generator::populate(position, r);
    return r;
}

class_in_package_generator::result_type*
class_in_package_generator::create_ptr(const unsigned int position) {
    class_in_package* p = new class_in_package();
    class_in_package_generator::populate(position, *p);
    return p;
}

class_in_package_generator::result_type
class_in_package_generator::operator()() {
    return create(position_++);
}

} } } }

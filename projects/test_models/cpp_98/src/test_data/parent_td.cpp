#include "dogen/test_models/cpp_98/test_data/child_td.hpp"
#include "dogen/test_models/cpp_98/test_data/parent_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_98 {

void parent_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
}

parent_generator::result_type*
parent_generator::create_ptr(const unsigned int position) {
    return dogen::test_models::cpp_98::child_generator::create_ptr(position);
}

} } }

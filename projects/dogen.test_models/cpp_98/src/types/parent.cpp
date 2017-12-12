#include <ostream>
#include "dogen/test_models/cpp_98/types/parent.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

parent::parent()
    : prop_0_(static_cast<int>(0)) { }

parent::parent(const int prop_0)
    : prop_0_(prop_0) { }

void parent::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_98::parent\"" << ", "
      << "\"prop_0\": " << prop_0_
      << " }";
}

void parent::swap(parent& other) {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool parent::compare(const parent& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

int parent::prop_0() const {
    return prop_0_;
}

void parent::prop_0(const int v) {
    prop_0_ = v;
}

} } }

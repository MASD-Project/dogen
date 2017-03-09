#include <ostream>
#include "dogen/test_models/cpp_98/types/child.hpp"
#include "dogen/test_models/cpp_98/io/parent_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

child::child()
    : prop_1_(static_cast<int>(0)) { }

child::child(
    const int prop_0,
    const int prop_1)
    : dogen::test_models::cpp_98::parent(prop_0),
      prop_1_(prop_1) { }

void child::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_98::child\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::cpp_98::parent::to_stream(s);
    s << ", "
      << "\"prop_1\": " << prop_1_
      << " }";
}

void child::swap(child& other) {
    dogen::test_models::cpp_98::parent::swap(other);

    using std::swap;
    swap(prop_1_, other.prop_1_);
}

bool child::equals(const dogen::test_models::cpp_98::parent& other) const {
    const child* const p(dynamic_cast<const child* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool child::operator==(const child& rhs) const {
    return dogen::test_models::cpp_98::parent::compare(rhs) &&
        prop_1_ == rhs.prop_1_;
}

child& child::operator=(child other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int child::prop_1() const {
    return prop_1_;
}

void child::prop_1(const int v) {
    prop_1_ = v;
}

} } }

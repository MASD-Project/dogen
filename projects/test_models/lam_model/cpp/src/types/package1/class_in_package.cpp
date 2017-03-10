#include "dogen/test_models/lam_model/types/package1/class_in_package.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {
namespace package1 {

class_in_package::class_in_package()
    : prop_0_(static_cast<int>(0)) { }

class_in_package::class_in_package(const int prop_0)
    : prop_0_(prop_0) { }

void class_in_package::swap(class_in_package& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool class_in_package::operator==(const class_in_package& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

class_in_package& class_in_package::operator=(class_in_package other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int class_in_package::prop_0() const {
    return prop_0_;
}

void class_in_package::prop_0(const int v) {
    prop_0_ = v;
}

} } } }

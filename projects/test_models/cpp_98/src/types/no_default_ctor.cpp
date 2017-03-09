#include "dogen/test_models/cpp_98/types/no_default_ctor.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

no_default_ctor::no_default_ctor()
     { }

no_default_ctor::no_default_ctor(const std::string& prop_0)
    : prop_0_(prop_0) { }

void no_default_ctor::swap(no_default_ctor& other) {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool no_default_ctor::operator==(const no_default_ctor& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

no_default_ctor& no_default_ctor::operator=(no_default_ctor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& no_default_ctor::prop_0() const {
    return prop_0_;
}

std::string& no_default_ctor::prop_0() {
    return prop_0_;
}

void no_default_ctor::prop_0(const std::string& v) {
    prop_0_ = v;
}

} } }

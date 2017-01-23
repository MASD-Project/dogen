#include "Phi/types/TestType.hpp"

namespace Phi {

TestType::TestType()
    : Version_(static_cast<Zeta::String>(0)),
      AField_(static_cast<Zeta::String>(0)) { }

TestType::TestType(
    const Zeta::String Version,
    const Zeta::String AField)
    : Version_(Version),
      AField_(AField) { }

void TestType::swap(TestType& other) noexcept {
    using std::swap;
    swap(Version_, other.Version_);
    swap(AField_, other.AField_);
}

bool TestType::operator==(const TestType& rhs) const {
    return Version_ == rhs.Version_ &&
        AField_ == rhs.AField_;
}

TestType& TestType::operator=(TestType other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

Zeta::String TestType::Version() const {
    return Version_;
}

void TestType::Version(const Zeta::String v) {
    Version_ = v;
}

Zeta::String TestType::AField() const {
    return AField_;
}

void TestType::AField(const Zeta::String v) {
    AField_ = v;
}

}

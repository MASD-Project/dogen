#include "dogen/test_models/split_project/types/package1/first_class.hpp"

namespace dogen {
namespace test_models {
namespace split_project {
namespace package1 {

first_class::first_class()
    : public_attribute_(static_cast<int>(0)),
      private_attribute_(static_cast<int>(0)) { }

first_class::first_class(
    const int public_attribute,
    const int private_attribute)
    : public_attribute_(public_attribute),
      private_attribute_(private_attribute) { }

void first_class::swap(first_class& other) noexcept {
    using std::swap;
    swap(public_attribute_, other.public_attribute_);
    swap(private_attribute_, other.private_attribute_);
}

bool first_class::operator==(const first_class& rhs) const {
    return public_attribute_ == rhs.public_attribute_ &&
        private_attribute_ == rhs.private_attribute_;
}

first_class& first_class::operator=(first_class other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int first_class::public_attribute() const {
    return public_attribute_;
}

void first_class::public_attribute(const int v) {
    public_attribute_ = v;
}

int first_class::private_attribute() const {
    return private_attribute_;
}

void first_class::private_attribute(const int v) {
    private_attribute_ = v;
}

} } } }

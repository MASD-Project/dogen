#include "Phi/types/CollectionTestType.hpp"

namespace Phi {

CollectionTestType::CollectionTestType(const std::vector<std::string>& BinariesTest)
    : BinariesTest_(BinariesTest) { }

void CollectionTestType::swap(CollectionTestType& other) noexcept {
    using std::swap;
    swap(BinariesTest_, other.BinariesTest_);
}

bool CollectionTestType::operator==(const CollectionTestType& rhs) const {
    return BinariesTest_ == rhs.BinariesTest_;
}

CollectionTestType& CollectionTestType::operator=(CollectionTestType other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<std::string>& CollectionTestType::BinariesTest() const {
    return BinariesTest_;
}

std::vector<std::string>& CollectionTestType::BinariesTest() {
    return BinariesTest_;
}

void CollectionTestType::BinariesTest(const std::vector<std::string>& v) {
    BinariesTest_ = v;
}

void CollectionTestType::BinariesTest(const std::vector<std::string>&& v) {
    BinariesTest_ = std::move(v);
}

}

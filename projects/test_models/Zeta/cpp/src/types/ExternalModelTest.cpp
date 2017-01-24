#include "Zeta/types/ExternalModelTest.hpp"

namespace Zeta {

ExternalModelTest::ExternalModelTest()
    : DateTest_(static_cast<Phi::Date>(0)) { }

ExternalModelTest::ExternalModelTest(
    const Phi::Date DateTest,
    const std::vector<std::string>& BinariesTest,
    const std::vector<std::vector<std::string> >& CollectionOfCollectionTest,
    const std::vector<std::vector<std::vector<std::string> > >& CollectionOfCollectionOfCollectionTest)
    : DateTest_(DateTest),
      BinariesTest_(BinariesTest),
      CollectionOfCollectionTest_(CollectionOfCollectionTest),
      CollectionOfCollectionOfCollectionTest_(CollectionOfCollectionOfCollectionTest) { }

void ExternalModelTest::swap(ExternalModelTest& other) noexcept {
    using std::swap;
    swap(DateTest_, other.DateTest_);
    swap(BinariesTest_, other.BinariesTest_);
    swap(CollectionOfCollectionTest_, other.CollectionOfCollectionTest_);
    swap(CollectionOfCollectionOfCollectionTest_, other.CollectionOfCollectionOfCollectionTest_);
}

bool ExternalModelTest::operator==(const ExternalModelTest& rhs) const {
    return DateTest_ == rhs.DateTest_ &&
        BinariesTest_ == rhs.BinariesTest_ &&
        CollectionOfCollectionTest_ == rhs.CollectionOfCollectionTest_ &&
        CollectionOfCollectionOfCollectionTest_ == rhs.CollectionOfCollectionOfCollectionTest_;
}

ExternalModelTest& ExternalModelTest::operator=(ExternalModelTest other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

Phi::Date ExternalModelTest::DateTest() const {
    return DateTest_;
}

void ExternalModelTest::DateTest(const Phi::Date v) {
    DateTest_ = v;
}

const std::vector<std::string>& ExternalModelTest::BinariesTest() const {
    return BinariesTest_;
}

std::vector<std::string>& ExternalModelTest::BinariesTest() {
    return BinariesTest_;
}

void ExternalModelTest::BinariesTest(const std::vector<std::string>& v) {
    BinariesTest_ = v;
}

void ExternalModelTest::BinariesTest(const std::vector<std::string>&& v) {
    BinariesTest_ = std::move(v);
}

const std::vector<std::vector<std::string> >& ExternalModelTest::CollectionOfCollectionTest() const {
    return CollectionOfCollectionTest_;
}

std::vector<std::vector<std::string> >& ExternalModelTest::CollectionOfCollectionTest() {
    return CollectionOfCollectionTest_;
}

void ExternalModelTest::CollectionOfCollectionTest(const std::vector<std::vector<std::string> >& v) {
    CollectionOfCollectionTest_ = v;
}

void ExternalModelTest::CollectionOfCollectionTest(const std::vector<std::vector<std::string> >&& v) {
    CollectionOfCollectionTest_ = std::move(v);
}

const std::vector<std::vector<std::vector<std::string> > >& ExternalModelTest::CollectionOfCollectionOfCollectionTest() const {
    return CollectionOfCollectionOfCollectionTest_;
}

std::vector<std::vector<std::vector<std::string> > >& ExternalModelTest::CollectionOfCollectionOfCollectionTest() {
    return CollectionOfCollectionOfCollectionTest_;
}

void ExternalModelTest::CollectionOfCollectionOfCollectionTest(const std::vector<std::vector<std::vector<std::string> > >& v) {
    CollectionOfCollectionOfCollectionTest_ = v;
}

void ExternalModelTest::CollectionOfCollectionOfCollectionTest(const std::vector<std::vector<std::vector<std::string> > >&& v) {
    CollectionOfCollectionOfCollectionTest_ = std::move(v);
}

}

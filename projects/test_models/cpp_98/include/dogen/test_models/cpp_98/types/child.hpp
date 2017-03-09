#ifndef DOGEN_TEST_MODELS_CPP_98_TYPES_CHILD_HPP
#define DOGEN_TEST_MODELS_CPP_98_TYPES_CHILD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_98/types/parent.hpp"
#include "dogen/test_models/cpp_98/serialization/child_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

class child : public dogen::test_models::cpp_98::parent {
public:
    child();

    virtual ~child() { }

public:
    child(
        const int prop_0,
        const int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_98::child& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_98::child& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const;

public:
    int prop_1() const;
    void prop_1(const int v);

public:
    bool operator==(const child& rhs) const;
    bool operator!=(const child& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::test_models::cpp_98::parent& other) const;

public:
    void swap(child& other);
    child& operator=(child other);

private:
    int prop_1_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_98::child& lhs,
    dogen::test_models::cpp_98::child& rhs) {
    lhs.swap(rhs);
}

}

#endif

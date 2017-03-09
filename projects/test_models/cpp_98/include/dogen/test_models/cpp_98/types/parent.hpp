#ifndef DOGEN_TEST_MODELS_CPP_98_TYPES_PARENT_HPP
#define DOGEN_TEST_MODELS_CPP_98_TYPES_PARENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_98/serialization/parent_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

class parent {
public:
    parent();

    virtual ~parent() = 0;

public:
    explicit parent(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_98::parent& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_98::parent& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    int prop_0() const;
    void prop_0(const int v);

protected:
    bool compare(const parent& rhs) const;
public:
    virtual bool equals(const parent& other) const = 0;

protected:
    void swap(parent& other);

private:
    int prop_0_;
};

inline parent::~parent() { }

inline bool operator==(const parent& lhs, const parent& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif

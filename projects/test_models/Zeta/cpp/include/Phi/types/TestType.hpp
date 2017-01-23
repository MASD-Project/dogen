#ifndef PHI_TYPES_TESTTYPE_HPP
#define PHI_TYPES_TESTTYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "Zeta/types/String.hpp"
#include "Phi/serialization/TestType_fwd_ser.hpp"

namespace Phi {

/**
 * @brief Test type
 */
class TestType final {
public:
    TestType(const TestType&) = default;
    TestType(TestType&&) = default;
    ~TestType() = default;

public:
    TestType();

public:
    TestType(
        const Zeta::String Version,
        const Zeta::String AField);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const Phi::TestType& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, Phi::TestType& v, unsigned int version);

public:
    /**
     * @brief Some comment
     */
    /**@{*/
    Zeta::String Version() const;
    void Version(const Zeta::String v);
    /**@}*/

    Zeta::String AField() const;
    void AField(const Zeta::String v);

public:
    bool operator==(const TestType& rhs) const;
    bool operator!=(const TestType& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(TestType& other) noexcept;
    TestType& operator=(TestType other);

private:
    Zeta::String Version_;
    Zeta::String AField_;
};

}

namespace std {

template<>
inline void swap(
    Phi::TestType& lhs,
    Phi::TestType& rhs) {
    lhs.swap(rhs);
}

}

#endif

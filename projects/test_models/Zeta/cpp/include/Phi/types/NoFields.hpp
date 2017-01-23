#ifndef PHI_TYPES_NOFIELDS_HPP
#define PHI_TYPES_NOFIELDS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "Phi/serialization/NoFields_fwd_ser.hpp"

namespace Phi {

/**
 * @brief Test type
 */
class NoFields final {
public:
    NoFields() = default;
    NoFields(const NoFields&) = default;
    NoFields(NoFields&&) = default;
    ~NoFields() = default;
    NoFields& operator=(const NoFields&) = default;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const Phi::NoFields& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, Phi::NoFields& v, unsigned int version);

public:
    bool operator==(const NoFields& rhs) const;
    bool operator!=(const NoFields& rhs) const {
        return !this->operator==(rhs);
    }

};

}

#endif

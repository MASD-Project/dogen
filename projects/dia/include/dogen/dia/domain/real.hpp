/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_REAL_HPP
#define DOGEN_DIA_DOMAIN_REAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class real_serializer; } }

/**
 * @brief Represents a real value.
 */
class real {
public:
    real() = default;
    real(const real&) = default;
    ~real() = default;
    real(real&&) = default;
    real& operator=(const real&) = default;

public:
    explicit real(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of a real value.
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

private:
    friend class dogen::dia::serialization::detail::real_serializer;

public:
    bool operator==(const dogen::dia::real& value) const {
        return(value_ == value.value());
    }

    bool operator!=(const dogen::dia::real& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif

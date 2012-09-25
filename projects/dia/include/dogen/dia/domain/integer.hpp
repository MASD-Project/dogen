/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_INTEGER_HPP
#define DOGEN_DIA_DOMAIN_INTEGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class integer_serializer; } }

/**
 * @brief Represents an integer value.
 */
class integer {
public:
    integer() = default;
    integer(const integer&) = default;
    ~integer() = default;
    integer(integer&&) = default;
    integer& operator=(const integer&) = default;

public:
    explicit integer(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of an integer value
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

private:
    friend class dogen::dia::serialization::detail::integer_serializer;

public:
    bool operator==(const dogen::dia::integer& value) const {
        return(value_ == value.value());
    }

    bool operator!=(const dogen::dia::integer& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif

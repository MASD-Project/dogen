/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_BOOLEAN_HPP
#define DOGEN_DIA_DOMAIN_BOOLEAN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class boolean_serializer; } }

/**
 * @brief Represents a boolean value
 */
class boolean {
public:
    boolean() = default;
    boolean(const boolean&) = default;
    ~boolean() = default;
    boolean(boolean&&) = default;
    boolean& operator=(const boolean&) = default;

private:
    friend class dogen::dia::serialization::detail::boolean_serializer;

public:
    boolean(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of a boolean value
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

    bool operator==(const dogen::dia::boolean& value) const {
        return(value_ == value.value());
    }

    bool operator!=(const dogen::dia::boolean& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif

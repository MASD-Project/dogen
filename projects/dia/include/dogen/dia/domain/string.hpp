/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_STRING_HPP
#define DOGEN_DIA_DOMAIN_STRING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class string_serializer; } }

/**
 * @brief Represents a string value.
 */
class string {
public:
    string() = default;
    string(const string&) = default;
    ~string() = default;
    string(string&&) = default;
    string& operator=(const string&) = default;

private:
    friend class dogen::dia::serialization::detail::string_serializer;

public:
    explicit string(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of a string value.
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

public:
    bool operator==(const dogen::dia::string& value) const {
        return(value_ == value.value());
    }

    bool operator!=(const dogen::dia::string& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif

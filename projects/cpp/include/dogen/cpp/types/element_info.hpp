/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_CPP_TYPES_ELEMENT_INFO_HPP
#define DOGEN_CPP_TYPES_ELEMENT_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include "dogen/cpp/serialization/element_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {

class element_info {
public:
    element_info() = default;
    element_info(const element_info&) = default;
    element_info(element_info&&) = default;

    virtual ~element_info() noexcept = 0;

public:
    explicit element_info(const std::string& documentation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const element_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, element_info& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

protected:
    bool compare(const element_info& rhs) const;
public:
    virtual bool equals(const element_info& other) const = 0;

protected:
    void swap(element_info& other) noexcept;

private:
    std::string documentation_;
};

inline element_info::~element_info() noexcept { }

inline bool operator==(const element_info& lhs, const element_info& rhs) {
    return lhs.equals(rhs);
}

} }



#endif

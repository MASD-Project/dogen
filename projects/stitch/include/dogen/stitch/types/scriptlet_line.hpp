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
#ifndef DOGEN_STITCH_TYPES_SCRIPTLET_LINE_HPP
#define DOGEN_STITCH_TYPES_SCRIPTLET_LINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/stitch/serialization/scriptlet_line_fwd_ser.hpp"

namespace dogen {
namespace stitch {

class scriptlet_line final {
public:
    scriptlet_line() = default;
    scriptlet_line(const scriptlet_line&) = default;
    scriptlet_line(scriptlet_line&&) = default;
    ~scriptlet_line() = default;

public:
    explicit scriptlet_line(const std::string& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const scriptlet_line& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, scriptlet_line& v, unsigned int version);

public:
    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);

public:
    bool operator==(const scriptlet_line& rhs) const;
    bool operator!=(const scriptlet_line& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(scriptlet_line& other) noexcept;
    scriptlet_line& operator=(scriptlet_line other);

private:
    std::string content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::scriptlet_line& lhs,
    dogen::stitch::scriptlet_line& rhs) {
    lhs.swap(rhs);
}

}

#endif

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
#ifndef DOGEN_OM_TYPES_CODE_GENERATION_MARKER_HPP
#define DOGEN_OM_TYPES_CODE_GENERATION_MARKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/om/serialization/code_generation_marker_fwd_ser.hpp"

namespace dogen {
namespace om {

/**
 * @brief Text identifying the file as code generated.
 */
class code_generation_marker final {
public:
    code_generation_marker() = default;
    code_generation_marker(const code_generation_marker&) = default;
    code_generation_marker(code_generation_marker&&) = default;
    ~code_generation_marker() = default;

public:
    explicit code_generation_marker(const std::string& text);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const code_generation_marker& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, code_generation_marker& v, unsigned int version);

public:
    const std::string& text() const;
    std::string& text();
    void text(const std::string& v);
    void text(const std::string&& v);

public:
    bool operator==(const code_generation_marker& rhs) const;
    bool operator!=(const code_generation_marker& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(code_generation_marker& other) noexcept;
    code_generation_marker& operator=(code_generation_marker other);

private:
    std::string text_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::code_generation_marker& lhs,
    dogen::om::code_generation_marker& rhs) {
    lhs.swap(rhs);
}

}

#endif

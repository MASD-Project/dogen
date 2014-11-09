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
#ifndef DOGEN_CPP_TYPES_PATH_SPEC_KEY_HPP
#define DOGEN_CPP_TYPES_PATH_SPEC_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/cpp/serialization/path_spec_key_fwd_ser.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace cpp {

class path_spec_key final {
public:
    path_spec_key() = default;
    path_spec_key(const path_spec_key&) = default;
    path_spec_key(path_spec_key&&) = default;
    ~path_spec_key() = default;

public:
    path_spec_key(
        const std::string& formatter_id,
        const dogen::sml::qname& qname);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const path_spec_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, path_spec_key& v, unsigned int version);

public:
    const std::string& formatter_id() const;
    std::string& formatter_id();
    void formatter_id(const std::string& v);
    void formatter_id(const std::string&& v);

    const dogen::sml::qname& qname() const;
    dogen::sml::qname& qname();
    void qname(const dogen::sml::qname& v);
    void qname(const dogen::sml::qname&& v);

public:
    bool operator==(const path_spec_key& rhs) const;
    bool operator!=(const path_spec_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_spec_key& other) noexcept;
    path_spec_key& operator=(path_spec_key other);

private:
    std::string formatter_id_;
    dogen::sml::qname qname_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::path_spec_key& lhs,
    dogen::cpp::path_spec_key& rhs) {
    lhs.swap(rhs);
}

}

#endif

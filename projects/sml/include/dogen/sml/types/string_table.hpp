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
#ifndef DOGEN_SML_TYPES_STRING_TABLE_HPP
#define DOGEN_SML_TYPES_STRING_TABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/sml/serialization/string_table_fwd_ser.hpp"
#include "dogen/sml/types/entry.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Stores a static table of strings.
 */
class string_table final {
public:
    string_table() = default;
    string_table(const string_table&) = default;
    string_table(string_table&&) = default;
    ~string_table() = default;

public:
    string_table(
        const dogen::sml::qname& name,
        const std::string& documentation,
        const std::list<dogen::sml::entry>& entries);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const string_table& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, string_table& v, unsigned int version);

public:
    const dogen::sml::qname& name() const;
    dogen::sml::qname& name();
    void name(const dogen::sml::qname& v);
    void name(const dogen::sml::qname&& v);

    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);

    const std::list<dogen::sml::entry>& entries() const;
    std::list<dogen::sml::entry>& entries();
    void entries(const std::list<dogen::sml::entry>& v);
    void entries(const std::list<dogen::sml::entry>&& v);

public:
    bool operator==(const string_table& rhs) const;
    bool operator!=(const string_table& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(string_table& other) noexcept;
    string_table& operator=(string_table other);

private:
    dogen::sml::qname name_;
    std::string documentation_;
    std::list<dogen::sml::entry> entries_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::string_table& lhs,
    dogen::sml::string_table& rhs) {
    lhs.swap(rhs);
}

}

#endif

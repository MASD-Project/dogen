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
#ifndef DOGEN_CPP_TYPES_RELATIONSHIPS_HPP
#define DOGEN_CPP_TYPES_RELATIONSHIPS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <unordered_set>
#include "dogen/cpp/serialization/relationships_fwd_ser.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace cpp {

class relationships final {
public:
    relationships(const relationships&) = default;
    ~relationships() = default;

public:
    relationships();

public:
    relationships(relationships&& rhs);

public:
    relationships(
        const std::unordered_set<dogen::sml::qname>& names,
        const std::unordered_set<dogen::sml::qname>& forward_decls,
        const std::unordered_set<dogen::sml::qname>& keys,
        const std::unordered_set<dogen::sml::qname>& leaves,
        const bool has_std_string,
        const bool has_variant,
        const bool is_parent,
        const bool is_child,
        const bool requires_stream_manipulators,
        const bool has_std_pair,
        const boost::optional<dogen::sml::qname>& visitor);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const relationships& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, relationships& v, unsigned int version);

public:
    const std::unordered_set<dogen::sml::qname>& names() const;
    std::unordered_set<dogen::sml::qname>& names();
    void names(const std::unordered_set<dogen::sml::qname>& v);
    void names(const std::unordered_set<dogen::sml::qname>&& v);

    const std::unordered_set<dogen::sml::qname>& forward_decls() const;
    std::unordered_set<dogen::sml::qname>& forward_decls();
    void forward_decls(const std::unordered_set<dogen::sml::qname>& v);
    void forward_decls(const std::unordered_set<dogen::sml::qname>&& v);

    const std::unordered_set<dogen::sml::qname>& keys() const;
    std::unordered_set<dogen::sml::qname>& keys();
    void keys(const std::unordered_set<dogen::sml::qname>& v);
    void keys(const std::unordered_set<dogen::sml::qname>&& v);

    const std::unordered_set<dogen::sml::qname>& leaves() const;
    std::unordered_set<dogen::sml::qname>& leaves();
    void leaves(const std::unordered_set<dogen::sml::qname>& v);
    void leaves(const std::unordered_set<dogen::sml::qname>&& v);

    bool has_std_string() const;
    void has_std_string(const bool v);

    bool has_variant() const;
    void has_variant(const bool v);

    bool is_parent() const;
    void is_parent(const bool v);

    bool is_child() const;
    void is_child(const bool v);

    bool requires_stream_manipulators() const;
    void requires_stream_manipulators(const bool v);

    bool has_std_pair() const;
    void has_std_pair(const bool v);

    const boost::optional<dogen::sml::qname>& visitor() const;
    boost::optional<dogen::sml::qname>& visitor();
    void visitor(const boost::optional<dogen::sml::qname>& v);
    void visitor(const boost::optional<dogen::sml::qname>&& v);

public:
    bool operator==(const relationships& rhs) const;
    bool operator!=(const relationships& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(relationships& other) noexcept;
    relationships& operator=(relationships other);

private:
    std::unordered_set<dogen::sml::qname> names_;
    std::unordered_set<dogen::sml::qname> forward_decls_;
    std::unordered_set<dogen::sml::qname> keys_;
    std::unordered_set<dogen::sml::qname> leaves_;
    bool has_std_string_;
    bool has_variant_;
    bool is_parent_;
    bool is_child_;
    bool requires_stream_manipulators_;
    bool has_std_pair_;
    boost::optional<dogen::sml::qname> visitor_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::relationships& lhs,
    dogen::cpp::relationships& rhs) {
    lhs.swap(rhs);
}

}

#endif

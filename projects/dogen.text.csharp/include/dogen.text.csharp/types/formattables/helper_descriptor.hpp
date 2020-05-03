/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_TEXT_CSHARP_TYPES_FORMATTABLES_HELPER_DESCRIPTOR_HPP
#define DOGEN_TEXT_CSHARP_TYPES_FORMATTABLES_HELPER_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>

namespace dogen::text::csharp::formattables {

class helper_descriptor final {
public:
    helper_descriptor(const helper_descriptor&) = default;
    helper_descriptor(helper_descriptor&&) = default;
    ~helper_descriptor() = default;

public:
    helper_descriptor();

public:
    helper_descriptor(
        const std::string& family,
        const std::list<std::string>& namespaces,
        const std::string& name_identifiable,
        const std::string& name_qualified,
        const std::string& name_tree_qualified,
        const std::string& name_tree_identifiable,
        const bool is_simple_type,
        const bool is_circular_dependency);

public:
    const std::string& family() const;
    std::string& family();
    void family(const std::string& v);
    void family(const std::string&& v);

    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);

    const std::string& name_identifiable() const;
    std::string& name_identifiable();
    void name_identifiable(const std::string& v);
    void name_identifiable(const std::string&& v);

    const std::string& name_qualified() const;
    std::string& name_qualified();
    void name_qualified(const std::string& v);
    void name_qualified(const std::string&& v);

    const std::string& name_tree_qualified() const;
    std::string& name_tree_qualified();
    void name_tree_qualified(const std::string& v);
    void name_tree_qualified(const std::string&& v);

    const std::string& name_tree_identifiable() const;
    std::string& name_tree_identifiable();
    void name_tree_identifiable(const std::string& v);
    void name_tree_identifiable(const std::string&& v);

    bool is_simple_type() const;
    void is_simple_type(const bool v);

    bool is_circular_dependency() const;
    void is_circular_dependency(const bool v);

public:
    bool operator==(const helper_descriptor& rhs) const;
    bool operator!=(const helper_descriptor& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_descriptor& other) noexcept;
    helper_descriptor& operator=(helper_descriptor other);

private:
    std::string family_;
    std::list<std::string> namespaces_;
    std::string name_identifiable_;
    std::string name_qualified_;
    std::string name_tree_qualified_;
    std::string name_tree_identifiable_;
    bool is_simple_type_;
    bool is_circular_dependency_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::csharp::formattables::helper_descriptor& lhs,
    dogen::text::csharp::formattables::helper_descriptor& rhs) {
    lhs.swap(rhs);
}

}

#endif

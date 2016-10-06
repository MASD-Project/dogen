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
#ifndef DOGEN_DYNAMIC_TYPES_PROFILE_HPP
#define DOGEN_DYNAMIC_TYPES_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/serialization/profile_fwd_ser.hpp"
#include "dogen/dynamic/types/field_instance_definition.hpp"

namespace dogen {
namespace dynamic {

class profile final {
public:
    profile() = default;
    profile(const profile&) = default;
    profile(profile&&) = default;
    ~profile() = default;

public:
    profile(
        const std::string& name,
        const std::list<std::string>& parents,
        const std::unordered_map<std::string, dogen::dynamic::field_instance_definition>& instance_definitions,
        const dogen::dynamic::object& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::dynamic::profile& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::dynamic::profile& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::list<std::string>& parents() const;
    std::list<std::string>& parents();
    void parents(const std::list<std::string>& v);
    void parents(const std::list<std::string>&& v);

    const std::unordered_map<std::string, dogen::dynamic::field_instance_definition>& instance_definitions() const;
    std::unordered_map<std::string, dogen::dynamic::field_instance_definition>& instance_definitions();
    void instance_definitions(const std::unordered_map<std::string, dogen::dynamic::field_instance_definition>& v);
    void instance_definitions(const std::unordered_map<std::string, dogen::dynamic::field_instance_definition>&& v);

    const dogen::dynamic::object& content() const;
    dogen::dynamic::object& content();
    void content(const dogen::dynamic::object& v);
    void content(const dogen::dynamic::object&& v);

public:
    bool operator==(const profile& rhs) const;
    bool operator!=(const profile& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(profile& other) noexcept;
    profile& operator=(profile other);

private:
    std::string name_;
    std::list<std::string> parents_;
    std::unordered_map<std::string, dogen::dynamic::field_instance_definition> instance_definitions_;
    dogen::dynamic::object content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dynamic::profile& lhs,
    dogen::dynamic::profile& rhs) {
    lhs.swap(rhs);
}

}

#endif

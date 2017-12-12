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
#ifndef DOGEN_ANNOTATIONS_TYPES_PROFILE_HPP
#define DOGEN_ANNOTATIONS_TYPES_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "dogen.annotations/types/entry_template.hpp"
#include "dogen.annotations/serialization/profile_fwd_ser.hpp"

namespace dogen {
namespace annotations {

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
        const std::unordered_set<std::string>& labels,
        const std::list<dogen::annotations::entry_template>& templates);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::profile& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::profile& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::list<std::string>& parents() const;
    std::list<std::string>& parents();
    void parents(const std::list<std::string>& v);
    void parents(const std::list<std::string>&& v);

    const std::unordered_set<std::string>& labels() const;
    std::unordered_set<std::string>& labels();
    void labels(const std::unordered_set<std::string>& v);
    void labels(const std::unordered_set<std::string>&& v);

    const std::list<dogen::annotations::entry_template>& templates() const;
    std::list<dogen::annotations::entry_template>& templates();
    void templates(const std::list<dogen::annotations::entry_template>& v);
    void templates(const std::list<dogen::annotations::entry_template>&& v);

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
    std::unordered_set<std::string> labels_;
    std::list<dogen::annotations::entry_template> templates_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::profile& lhs,
    dogen::annotations::profile& rhs) {
    lhs.swap(rhs);
}

}

#endif

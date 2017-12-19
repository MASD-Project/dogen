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
#ifndef DOGEN_FORMATTERS_TYPES_REPOSITORY_HPP
#define DOGEN_FORMATTERS_TYPES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.formatting/types/modeline_group.hpp"
#include "dogen.formatting/serialization/repository_fwd_ser.hpp"

namespace dogen {
namespace formatting {

class repository final {
public:
    repository() = default;
    repository(const repository&) = default;
    repository(repository&&) = default;
    ~repository() = default;

public:
    repository(
        const std::unordered_map<std::string, dogen::formatting::modeline_group>& modeline_groups,
        const std::unordered_map<std::string, std::string>& licence_texts);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatting::repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatting::repository& v, unsigned int version);

public:
    const std::unordered_map<std::string, dogen::formatting::modeline_group>& modeline_groups() const;
    std::unordered_map<std::string, dogen::formatting::modeline_group>& modeline_groups();
    void modeline_groups(const std::unordered_map<std::string, dogen::formatting::modeline_group>& v);
    void modeline_groups(const std::unordered_map<std::string, dogen::formatting::modeline_group>&& v);

    const std::unordered_map<std::string, std::string>& licence_texts() const;
    std::unordered_map<std::string, std::string>& licence_texts();
    void licence_texts(const std::unordered_map<std::string, std::string>& v);
    void licence_texts(const std::unordered_map<std::string, std::string>&& v);

public:
    bool operator==(const repository& rhs) const;
    bool operator!=(const repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(repository& other) noexcept;
    repository& operator=(repository other);

private:
    std::unordered_map<std::string, dogen::formatting::modeline_group> modeline_groups_;
    std::unordered_map<std::string, std::string> licence_texts_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatting::repository& lhs,
    dogen::formatting::repository& rhs) {
    lhs.swap(rhs);
}

}

#endif

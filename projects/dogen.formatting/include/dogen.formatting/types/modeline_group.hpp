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
#ifndef DOGEN_FORMATTING_TYPES_MODELINE_GROUP_HPP
#define DOGEN_FORMATTING_TYPES_MODELINE_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.formatting/types/modeline.hpp"
#include "dogen.formatting/serialization/modeline_group_fwd_ser.hpp"

namespace dogen {
namespace formatting {

/**
 * @brief Group of modelines, logically associated.
 *
 * For example, one may choose to have a set of modelines for @e emacs , or for
 * @e vi, etc.
 */
class modeline_group final {
public:
    modeline_group() = default;
    modeline_group(const modeline_group&) = default;
    modeline_group(modeline_group&&) = default;
    ~modeline_group() = default;

public:
    modeline_group(
        const std::string& name,
        const std::unordered_map<std::string, dogen::formatting::modeline>& modelines);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatting::modeline_group& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatting::modeline_group& v, unsigned int version);

public:
    /**
     * @brief Name of the modeline group. Must be unique
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief All the modelines for this group.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::formatting::modeline>& modelines() const;
    std::unordered_map<std::string, dogen::formatting::modeline>& modelines();
    void modelines(const std::unordered_map<std::string, dogen::formatting::modeline>& v);
    void modelines(const std::unordered_map<std::string, dogen::formatting::modeline>&& v);
    /**@}*/

public:
    bool operator==(const modeline_group& rhs) const;
    bool operator!=(const modeline_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(modeline_group& other) noexcept;
    modeline_group& operator=(modeline_group other);

private:
    std::string name_;
    std::unordered_map<std::string, dogen::formatting::modeline> modelines_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatting::modeline_group& lhs,
    dogen::formatting::modeline_group& rhs) {
    lhs.swap(rhs);
}

}

#endif

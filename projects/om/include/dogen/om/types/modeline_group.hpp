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
#ifndef DOGEN_OM_TYPES_MODELINE_GROUP_HPP
#define DOGEN_OM_TYPES_MODELINE_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include <unordered_map>
#include "dogen/om/serialization/modeline_group_fwd_ser.hpp"
#include "dogen/om/types/modeline.hpp"

namespace dogen {
namespace om {

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
    explicit modeline_group(const std::unordered_map<std::string, dogen::om::modeline>& modelines);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const modeline_group& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, modeline_group& v, unsigned int version);

public:
    /**
     * @brief All the modelines for this group.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::om::modeline>& modelines() const;
    std::unordered_map<std::string, dogen::om::modeline>& modelines();
    void modelines(const std::unordered_map<std::string, dogen::om::modeline>& v);
    void modelines(const std::unordered_map<std::string, dogen::om::modeline>&& v);
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
    std::unordered_map<std::string, dogen::om::modeline> modelines_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::modeline_group& lhs,
    dogen::om::modeline_group& rhs) {
    lhs.swap(rhs);
}

}

#endif

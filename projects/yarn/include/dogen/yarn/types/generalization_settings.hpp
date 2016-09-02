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
#ifndef DOGEN_YARN_TYPES_GENERALIZATION_SETTINGS_HPP
#define DOGEN_YARN_TYPES_GENERALIZATION_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/yarn/serialization/generalization_settings_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class generalization_settings final {
public:
    generalization_settings(const generalization_settings&) = default;
    generalization_settings(generalization_settings&&) = default;
    ~generalization_settings() = default;

public:
    generalization_settings();

public:
    generalization_settings(
        const bool is_final,
        const std::list<std::string>& parents);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::generalization_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::generalization_settings& v, unsigned int version);

public:
    bool is_final() const;
    void is_final(const bool v);

    const std::list<std::string>& parents() const;
    std::list<std::string>& parents();
    void parents(const std::list<std::string>& v);
    void parents(const std::list<std::string>&& v);

public:
    bool operator==(const generalization_settings& rhs) const;
    bool operator!=(const generalization_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(generalization_settings& other) noexcept;
    generalization_settings& operator=(generalization_settings other);

private:
    bool is_final_;
    std::list<std::string> parents_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::generalization_settings& lhs,
    dogen::yarn::generalization_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif

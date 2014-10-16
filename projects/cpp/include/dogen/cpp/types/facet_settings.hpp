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
#ifndef DOGEN_CPP_TYPES_FACET_SETTINGS_HPP
#define DOGEN_CPP_TYPES_FACET_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/cpp/serialization/facet_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Settings for the individual facets.
 */
class facet_settings final {
public:
    facet_settings(const facet_settings&) = default;
    facet_settings(facet_settings&&) = default;
    ~facet_settings() = default;

public:
    facet_settings();

public:
    facet_settings(
        const bool enabled,
        const std::string& directory_name,
        const std::string& postfix);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const facet_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, facet_settings& v, unsigned int version);

public:
    /**
     * @brief For each facet, whether they are enabled or not.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    const std::string& directory_name() const;
    std::string& directory_name();
    void directory_name(const std::string& v);
    void directory_name(const std::string&& v);

    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);

public:
    bool operator==(const facet_settings& rhs) const;
    bool operator!=(const facet_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(facet_settings& other) noexcept;
    facet_settings& operator=(facet_settings other);

private:
    bool enabled_;
    std::string directory_name_;
    std::string postfix_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::facet_settings& lhs,
    dogen::cpp::facet_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif

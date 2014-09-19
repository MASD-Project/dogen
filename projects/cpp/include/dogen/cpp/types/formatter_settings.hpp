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
#ifndef DOGEN_CPP_TYPES_FORMATTER_SETTINGS_HPP
#define DOGEN_CPP_TYPES_FORMATTER_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include <unordered_map>
#include "dogen/cpp/serialization/formatter_settings_fwd_ser.hpp"
#include "dogen/cpp/types/includes.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Settings for the individual formatters.
 */
class formatter_settings final {
public:
    formatter_settings() = default;
    formatter_settings(const formatter_settings&) = default;
    formatter_settings(formatter_settings&&) = default;
    ~formatter_settings() = default;

public:
    formatter_settings(
        const std::unordered_map<std::string, bool>& enabled_facets,
        const dogen::cpp::includes& includes,
        const std::string& relative_path);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const formatter_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, formatter_settings& v, unsigned int version);

public:
    /**
     * @brief For each facet, whether they are enabled or not.
     */
    /**@{*/
    const std::unordered_map<std::string, bool>& enabled_facets() const;
    std::unordered_map<std::string, bool>& enabled_facets();
    void enabled_facets(const std::unordered_map<std::string, bool>& v);
    void enabled_facets(const std::unordered_map<std::string, bool>&& v);
    /**@}*/

    /**
     * @brief Include files for the facet.
     */
    /**@{*/
    const dogen::cpp::includes& includes() const;
    dogen::cpp::includes& includes();
    void includes(const dogen::cpp::includes& v);
    void includes(const dogen::cpp::includes&& v);
    /**@}*/

    const std::string& relative_path() const;
    std::string& relative_path();
    void relative_path(const std::string& v);
    void relative_path(const std::string&& v);

public:
    bool operator==(const formatter_settings& rhs) const;
    bool operator!=(const formatter_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formatter_settings& other) noexcept;
    formatter_settings& operator=(formatter_settings other);

private:
    std::unordered_map<std::string, bool> enabled_facets_;
    dogen::cpp::includes includes_;
    std::string relative_path_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::formatter_settings& lhs,
    dogen::cpp::formatter_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif

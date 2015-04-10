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
#ifndef DOGEN_CPP_TYPES_SETTINGS_FORMATTER_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_FORMATTER_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <list>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/serialization/settings/formatter_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class formatter_settings final {
public:
    formatter_settings(const formatter_settings&) = default;
    ~formatter_settings() = default;

public:
    formatter_settings();

public:
    formatter_settings(formatter_settings&& rhs);

public:
    formatter_settings(
        const bool enabled,
        const boost::filesystem::path& file_path,
        const boost::optional<std::string>& header_guard,
        const std::list<std::string>& inclusion_dependencies,
        const std::set<std::string>& integrated_facets);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const formatter_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, formatter_settings& v, unsigned int version);

public:
    bool enabled() const;
    void enabled(const bool v);

    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);

    /**
     * @brief Header guard to use for this file, if applicable.
     */
    /**@{*/
    const boost::optional<std::string>& header_guard() const;
    boost::optional<std::string>& header_guard();
    void header_guard(const boost::optional<std::string>& v);
    void header_guard(const boost::optional<std::string>&& v);
    /**@}*/

    const std::list<std::string>& inclusion_dependencies() const;
    std::list<std::string>& inclusion_dependencies();
    void inclusion_dependencies(const std::list<std::string>& v);
    void inclusion_dependencies(const std::list<std::string>&& v);

    const std::set<std::string>& integrated_facets() const;
    std::set<std::string>& integrated_facets();
    void integrated_facets(const std::set<std::string>& v);
    void integrated_facets(const std::set<std::string>&& v);

public:
    bool operator==(const formatter_settings& rhs) const;
    bool operator!=(const formatter_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formatter_settings& other) noexcept;
    formatter_settings& operator=(formatter_settings other);

private:
    bool enabled_;
    boost::filesystem::path file_path_;
    boost::optional<std::string> header_guard_;
    std::list<std::string> inclusion_dependencies_;
    std::set<std::string> integrated_facets_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::formatter_settings& lhs,
    dogen::cpp::settings::formatter_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif

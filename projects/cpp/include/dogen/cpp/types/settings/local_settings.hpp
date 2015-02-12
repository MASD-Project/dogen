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
#ifndef DOGEN_CPP_TYPES_SETTINGS_LOCAL_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_LOCAL_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <string>
#include <unordered_map>
#include "dogen/cpp/serialization/settings/local_settings_fwd_ser.hpp"
#include "dogen/cpp/types/settings/local_facet_settings.hpp"
#include "dogen/cpp/types/settings/local_formatter_settings.hpp"
#include "dogen/cpp/types/settings/type_settings.hpp"
#include "dogen/formatters/types/general_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class local_settings final {
public:
    local_settings() = default;
    local_settings(const local_settings&) = default;
    ~local_settings() = default;

public:
    local_settings(local_settings&& rhs);

public:
    local_settings(
        const boost::optional<dogen::formatters::general_settings>& general_settings,
        const std::unordered_map<std::string, dogen::cpp::settings::local_facet_settings>& facet_settings,
        const std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>& formatter_settings,
        const boost::optional<dogen::cpp::settings::type_settings>& type_settings);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const local_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, local_settings& v, unsigned int version);

public:
    const boost::optional<dogen::formatters::general_settings>& general_settings() const;
    boost::optional<dogen::formatters::general_settings>& general_settings();
    void general_settings(const boost::optional<dogen::formatters::general_settings>& v);
    void general_settings(const boost::optional<dogen::formatters::general_settings>&& v);

    const std::unordered_map<std::string, dogen::cpp::settings::local_facet_settings>& facet_settings() const;
    std::unordered_map<std::string, dogen::cpp::settings::local_facet_settings>& facet_settings();
    void facet_settings(const std::unordered_map<std::string, dogen::cpp::settings::local_facet_settings>& v);
    void facet_settings(const std::unordered_map<std::string, dogen::cpp::settings::local_facet_settings>&& v);

    const std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>& formatter_settings() const;
    std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>& formatter_settings();
    void formatter_settings(const std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>& v);
    void formatter_settings(const std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>&& v);

    const boost::optional<dogen::cpp::settings::type_settings>& type_settings() const;
    boost::optional<dogen::cpp::settings::type_settings>& type_settings();
    void type_settings(const boost::optional<dogen::cpp::settings::type_settings>& v);
    void type_settings(const boost::optional<dogen::cpp::settings::type_settings>&& v);

public:
    bool operator==(const local_settings& rhs) const;
    bool operator!=(const local_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(local_settings& other) noexcept;
    local_settings& operator=(local_settings other);

private:
    boost::optional<dogen::formatters::general_settings> general_settings_;
    std::unordered_map<std::string, dogen::cpp::settings::local_facet_settings> facet_settings_;
    std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings> formatter_settings_;
    boost::optional<dogen::cpp::settings::type_settings> type_settings_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::local_settings& lhs,
    dogen::cpp::settings::local_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif

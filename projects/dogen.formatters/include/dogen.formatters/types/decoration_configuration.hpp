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
#ifndef DOGEN_FORMATTERS_TYPES_DECORATION_CONFIGURATION_HPP
#define DOGEN_FORMATTERS_TYPES_DECORATION_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.formatters/serialization/decoration_configuration_fwd_ser.hpp"

namespace dogen {
namespace formatters {

class decoration_configuration final {
public:
    decoration_configuration() = default;
    decoration_configuration(const decoration_configuration&) = default;
    ~decoration_configuration() = default;

public:
    decoration_configuration(decoration_configuration&& rhs);

public:
    decoration_configuration(
        const boost::optional<bool>& generate_decoration,
        const std::list<std::string>& copyright_notices,
        const std::string& licence_name,
        const std::string& modeline_group_name,
        const boost::optional<bool>& marker_add_date_time,
        const boost::optional<bool>& marker_add_warning,
        const std::string& marker_message);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatters::decoration_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatters::decoration_configuration& v, unsigned int version);

public:
    const boost::optional<bool>& generate_decoration() const;
    boost::optional<bool>& generate_decoration();
    void generate_decoration(const boost::optional<bool>& v);
    void generate_decoration(const boost::optional<bool>&& v);

    const std::list<std::string>& copyright_notices() const;
    std::list<std::string>& copyright_notices();
    void copyright_notices(const std::list<std::string>& v);
    void copyright_notices(const std::list<std::string>&& v);

    const std::string& licence_name() const;
    std::string& licence_name();
    void licence_name(const std::string& v);
    void licence_name(const std::string&& v);

    const std::string& modeline_group_name() const;
    std::string& modeline_group_name();
    void modeline_group_name(const std::string& v);
    void modeline_group_name(const std::string&& v);

    const boost::optional<bool>& marker_add_date_time() const;
    boost::optional<bool>& marker_add_date_time();
    void marker_add_date_time(const boost::optional<bool>& v);
    void marker_add_date_time(const boost::optional<bool>&& v);

    const boost::optional<bool>& marker_add_warning() const;
    boost::optional<bool>& marker_add_warning();
    void marker_add_warning(const boost::optional<bool>& v);
    void marker_add_warning(const boost::optional<bool>&& v);

    const std::string& marker_message() const;
    std::string& marker_message();
    void marker_message(const std::string& v);
    void marker_message(const std::string&& v);

public:
    bool operator==(const decoration_configuration& rhs) const;
    bool operator!=(const decoration_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decoration_configuration& other) noexcept;
    decoration_configuration& operator=(decoration_configuration other);

private:
    boost::optional<bool> generate_decoration_;
    std::list<std::string> copyright_notices_;
    std::string licence_name_;
    std::string modeline_group_name_;
    boost::optional<bool> marker_add_date_time_;
    boost::optional<bool> marker_add_warning_;
    std::string marker_message_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::decoration_configuration& lhs,
    dogen::formatters::decoration_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

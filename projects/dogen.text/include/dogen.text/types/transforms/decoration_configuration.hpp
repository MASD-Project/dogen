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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_DECORATION_CONFIGURATION_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_DECORATION_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>

namespace dogen::text::transforms {

class decoration_configuration final {
public:
    decoration_configuration() = default;
    decoration_configuration(const decoration_configuration&) = default;
    ~decoration_configuration() = default;

public:
    decoration_configuration(decoration_configuration&& rhs);

public:
    decoration_configuration(
        const boost::optional<bool>& enabled,
        const std::list<std::string>& copyright_notices,
        const std::string& licence_name,
        const std::string& modeline_group_name,
        const std::string& marker_name);

public:
    const boost::optional<bool>& enabled() const;
    boost::optional<bool>& enabled();
    void enabled(const boost::optional<bool>& v);
    void enabled(const boost::optional<bool>&& v);

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

    const std::string& marker_name() const;
    std::string& marker_name();
    void marker_name(const std::string& v);
    void marker_name(const std::string&& v);

public:
    bool operator==(const decoration_configuration& rhs) const;
    bool operator!=(const decoration_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decoration_configuration& other) noexcept;
    decoration_configuration& operator=(decoration_configuration other);

private:
    boost::optional<bool> enabled_;
    std::list<std::string> copyright_notices_;
    std::string licence_name_;
    std::string modeline_group_name_;
    std::string marker_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::transforms::decoration_configuration& lhs,
    dogen::text::transforms::decoration_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

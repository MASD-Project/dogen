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
#ifndef MASD_DOGEN_CLI_TYPES_CONVERSION_CONFIGURATION_HPP
#define MASD_DOGEN_CLI_TYPES_CONVERSION_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace masd::dogen::cli {

/**
 * @brief Configuration for the model conversion.
 */
class conversion_configuration final {
public:
    conversion_configuration() = default;
    conversion_configuration(const conversion_configuration&) = default;
    ~conversion_configuration() = default;

public:
    conversion_configuration(conversion_configuration&& rhs);

public:
    conversion_configuration(
        const boost::filesystem::path& source,
        const std::string& destination);

public:
    const boost::filesystem::path& source() const;
    boost::filesystem::path& source();
    conversion_configuration& source(const boost::filesystem::path& v);
    conversion_configuration& source(const boost::filesystem::path&& v);

    /**
     * @brief Name of the file to output the conversion to.
     */
    /**@{*/
    const std::string& destination() const;
    std::string& destination();
    conversion_configuration& destination(const std::string& v);
    conversion_configuration& destination(const std::string&& v);
    /**@}*/

public:
    bool operator==(const conversion_configuration& rhs) const;
    bool operator!=(const conversion_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(conversion_configuration& other) noexcept;
    conversion_configuration& operator=(conversion_configuration other);

private:
    boost::filesystem::path source_;
    std::string destination_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::cli::conversion_configuration& lhs,
    masd::dogen::cli::conversion_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

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
#ifndef MASD_DOGEN_OPTIONS_TYPES_DARTING_OPTIONS_HPP
#define MASD_DOGEN_OPTIONS_TYPES_DARTING_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace masd::dogen::options {

class darting_options final {
public:
    darting_options(const darting_options&) = default;
    ~darting_options() = default;

public:
    darting_options();

public:
    darting_options(darting_options&& rhs);

public:
    darting_options(
        const std::string& log_level,
        const bool force_write,
        const std::string& product_name,
        const boost::filesystem::path& log_directory);

public:
    /**
     * @brief What level of logging to log at.
     */
    /**@{*/
    const std::string& log_level() const;
    std::string& log_level();
    void log_level(const std::string& v);
    void log_level(const std::string&& v);
    /**@}*/

    bool force_write() const;
    void force_write(const bool v);

    const std::string& product_name() const;
    std::string& product_name();
    void product_name(const std::string& v);
    void product_name(const std::string&& v);

    const boost::filesystem::path& log_directory() const;
    boost::filesystem::path& log_directory();
    void log_directory(const boost::filesystem::path& v);
    void log_directory(const boost::filesystem::path&& v);

public:
    bool operator==(const darting_options& rhs) const;
    bool operator!=(const darting_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(darting_options& other) noexcept;
    darting_options& operator=(darting_options other);

private:
    std::string log_level_;
    bool force_write_;
    std::string product_name_;
    boost::filesystem::path log_directory_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::options::darting_options& lhs,
    masd::dogen::options::darting_options& rhs) {
    lhs.swap(rhs);
}

}

#endif

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
#ifndef DOGEN_CONFIG_TYPES_OUTPUT_OPTIONS_HPP
#define DOGEN_CONFIG_TYPES_OUTPUT_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include "dogen/config/serialization/output_options_fwd_ser.hpp"

namespace dogen {
namespace config {

class output_options final {
public:
    output_options(const output_options&) = default;
    output_options(output_options&&) = default;
    ~output_options() = default;

public:
    output_options();

public:
    output_options(
        const bool delete_extra_files,
        const bool force_write,
        const std::vector<std::string>& ignore_patterns);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const output_options& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, output_options& v, unsigned int version);

public:
    /**
     * @brief Delete any extra files found in managed directories.
     */
    /**@{*/
    bool delete_extra_files() const;
    void delete_extra_files(const bool v);
    /**@}*/

    /**
     * @brief Always generate files even if there are no differences
     * with existing file.
     */
    /**@{*/
    bool force_write() const;
    void force_write(const bool v);
    /**@}*/

    /**
     * @brief List of regular expressions to filter out files to ignore.
     */
    /**@{*/
    const std::vector<std::string>& ignore_patterns() const;
    std::vector<std::string>& ignore_patterns();
    void ignore_patterns(const std::vector<std::string>& v);
    void ignore_patterns(const std::vector<std::string>&& v);
    /**@}*/

public:
    bool operator==(const output_options& rhs) const;
    bool operator!=(const output_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(output_options& other) noexcept;
    output_options& operator=(output_options other);

private:
    bool delete_extra_files_;
    bool force_write_;
    std::vector<std::string> ignore_patterns_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::output_options& lhs,
    dogen::config::output_options& rhs) {
    lhs.swap(rhs);
}

}

#endif

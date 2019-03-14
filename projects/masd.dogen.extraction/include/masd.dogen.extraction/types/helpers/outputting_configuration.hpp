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
#ifndef MASD_DOGEN_EXTRACTION_TYPES_HELPERS_OUTPUTTING_CONFIGURATION_HPP
#define MASD_DOGEN_EXTRACTION_TYPES_HELPERS_OUTPUTTING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>

namespace masd::dogen::extraction::helpers {

class outputting_configuration final {
public:
    outputting_configuration(const outputting_configuration&) = default;
    outputting_configuration(outputting_configuration&&) = default;
    ~outputting_configuration() = default;

public:
    outputting_configuration();

public:
    outputting_configuration(
        const bool force_write,
        const bool delete_extra_files,
        const std::vector<std::string>& ignore_files_matching_regex,
        const bool delete_empty_directories);

public:
    bool force_write() const;
    void force_write(const bool v);

    bool delete_extra_files() const;
    void delete_extra_files(const bool v);

    const std::vector<std::string>& ignore_files_matching_regex() const;
    std::vector<std::string>& ignore_files_matching_regex();
    void ignore_files_matching_regex(const std::vector<std::string>& v);
    void ignore_files_matching_regex(const std::vector<std::string>&& v);

    bool delete_empty_directories() const;
    void delete_empty_directories(const bool v);

public:
    bool operator==(const outputting_configuration& rhs) const;
    bool operator!=(const outputting_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(outputting_configuration& other) noexcept;
    outputting_configuration& operator=(outputting_configuration other);

private:
    bool force_write_;
    bool delete_extra_files_;
    std::vector<std::string> ignore_files_matching_regex_;
    bool delete_empty_directories_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::extraction::helpers::outputting_configuration& lhs,
    masd::dogen::extraction::helpers::outputting_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

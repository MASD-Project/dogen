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
#ifndef DOGEN_TYPES_REPORTING_CONFIGURATION_HPP
#define DOGEN_TYPES_REPORTING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/types/reporting_style.hpp"

namespace dogen {

/**
 * @brief Configuration related to operational reports.
 */
class reporting_configuration final {
public:
    reporting_configuration(const reporting_configuration&) = default;
    ~reporting_configuration() = default;

public:
    reporting_configuration();

public:
    reporting_configuration(reporting_configuration&& rhs);

public:
    reporting_configuration(
        const dogen::reporting_style style,
        const boost::filesystem::path& output_directory);

public:
    dogen::reporting_style style() const;
    void style(const dogen::reporting_style v);

    const boost::filesystem::path& output_directory() const;
    boost::filesystem::path& output_directory();
    void output_directory(const boost::filesystem::path& v);
    void output_directory(const boost::filesystem::path&& v);

public:
    bool operator==(const reporting_configuration& rhs) const;
    bool operator!=(const reporting_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(reporting_configuration& other) noexcept;
    reporting_configuration& operator=(reporting_configuration other);

private:
    dogen::reporting_style style_;
    boost::filesystem::path output_directory_;
};

}

namespace std {

template<>
inline void swap(
    dogen::reporting_configuration& lhs,
    dogen::reporting_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

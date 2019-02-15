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
#ifndef MASD_DOGEN_TYPES_DIFFING_CONFIGURATION_HPP
#define MASD_DOGEN_TYPES_DIFFING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "masd.dogen/types/diffing_style.hpp"

namespace masd::dogen {

/**
 * @brief Configuration for diff generation.
 */
class diffing_configuration final {
public:
    diffing_configuration(const diffing_configuration&) = default;
    diffing_configuration(diffing_configuration&&) = default;
    ~diffing_configuration() = default;

public:
    diffing_configuration();

public:
    diffing_configuration(
        const masd::dogen::diffing_style style,
        const bool report_identical_files);

public:
    /**
     * @brief What style to use when producing diffs.
     */
    /**@{*/
    masd::dogen::diffing_style style() const;
    diffing_configuration& style(const masd::dogen::diffing_style v);
    /**@}*/

    /**
     * @brief If true, reports files that have not changed as well.
     */
    /**@{*/
    bool report_identical_files() const;
    diffing_configuration& report_identical_files(const bool v);
    /**@}*/

public:
    bool operator==(const diffing_configuration& rhs) const;
    bool operator!=(const diffing_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(diffing_configuration& other) noexcept;
    diffing_configuration& operator=(diffing_configuration other);

private:
    masd::dogen::diffing_style style_;
    bool report_identical_files_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::diffing_configuration& lhs,
    masd::dogen::diffing_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

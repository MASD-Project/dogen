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
#ifndef MASD_DOGEN_TYPES_OPERATIONAL_REPORTING_CONFIGURATION_HPP
#define MASD_DOGEN_TYPES_OPERATIONAL_REPORTING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "masd.dogen/types/operational_reporting_style.hpp"

namespace masd::dogen {

/**
 * @brief Configuration related to operational reports.
 */
class operational_reporting_configuration final {
public:
    operational_reporting_configuration(const operational_reporting_configuration&) = default;
    operational_reporting_configuration(operational_reporting_configuration&&) = default;
    ~operational_reporting_configuration() = default;

public:
    operational_reporting_configuration();

public:
    explicit operational_reporting_configuration(const masd::dogen::operational_reporting_style style);

public:
    masd::dogen::operational_reporting_style style() const;
    void style(const masd::dogen::operational_reporting_style v);

public:
    bool operator==(const operational_reporting_configuration& rhs) const;
    bool operator!=(const operational_reporting_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(operational_reporting_configuration& other) noexcept;
    operational_reporting_configuration& operator=(operational_reporting_configuration other);

private:
    masd::dogen::operational_reporting_style style_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::operational_reporting_configuration& lhs,
    masd::dogen::operational_reporting_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

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
#ifndef MASD_DOGEN_TYPES_ERROR_HANDLING_CONFIGURATION_HPP
#define MASD_DOGEN_TYPES_ERROR_HANDLING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace masd::dogen {

/**
 * @brief Configuration related to the behaviour of Dogen in the presence of errors and
 * warnings.
 */
class error_handling_configuration final {
public:
    error_handling_configuration(const error_handling_configuration&) = default;
    error_handling_configuration(error_handling_configuration&&) = default;
    ~error_handling_configuration() = default;

public:
    error_handling_configuration();

public:
    explicit error_handling_configuration(const bool compatibility_mode_enabled);

public:
    /**
     * @brief Try to process models even if there are errors.
     *
     * Only a certain class of errors are allowed, believed to be caused by backwards or
     * forwards compatibility problems: missing types or types that do not exist.
     */
    /**@{*/
    bool compatibility_mode_enabled() const;
    void compatibility_mode_enabled(const bool v);
    /**@}*/

public:
    bool operator==(const error_handling_configuration& rhs) const;
    bool operator!=(const error_handling_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(error_handling_configuration& other) noexcept;
    error_handling_configuration& operator=(error_handling_configuration other);

private:
    bool compatibility_mode_enabled_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::error_handling_configuration& lhs,
    masd::dogen::error_handling_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

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
#ifndef MASD_DOGEN_TYPES_WEAVING_CONFIGURATION_HPP
#define MASD_DOGEN_TYPES_WEAVING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "masd.dogen/types/weaving_style.hpp"

namespace masd::dogen {

/**
 * @brief Configuration for weaving.
 */
class weaving_configuration final {
public:
    weaving_configuration(const weaving_configuration&) = default;
    ~weaving_configuration() = default;

public:
    weaving_configuration();

public:
    weaving_configuration(weaving_configuration&& rhs);

public:
    weaving_configuration(
        const boost::filesystem::path& output_directory,
        const masd::dogen::weaving_style style);

public:
    /**
     * @brief Directory in which to place the output.
     */
    /**@{*/
    const boost::filesystem::path& output_directory() const;
    boost::filesystem::path& output_directory();
    weaving_configuration& output_directory(const boost::filesystem::path& v);
    weaving_configuration& output_directory(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief What style of weaving to perform.
     */
    /**@{*/
    masd::dogen::weaving_style style() const;
    weaving_configuration& style(const masd::dogen::weaving_style v);
    /**@}*/

public:
    bool operator==(const weaving_configuration& rhs) const;
    bool operator!=(const weaving_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(weaving_configuration& other) noexcept;
    weaving_configuration& operator=(weaving_configuration other);

private:
    boost::filesystem::path output_directory_;
    masd::dogen::weaving_style style_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::weaving_configuration& lhs,
    masd::dogen::weaving_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

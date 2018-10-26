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
#ifndef MASD_DOGEN_TYPES_TRACING_CONFIGURATION_HPP
#define MASD_DOGEN_TYPES_TRACING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "masd.dogen/types/tracing_level.hpp"
#include "masd.dogen/types/tracing_format.hpp"

namespace masd::dogen {

/**
 * @brief Configuration related to tracing.
 */
class tracing_configuration final {
public:
    tracing_configuration(const tracing_configuration&) = default;
    ~tracing_configuration() = default;

public:
    tracing_configuration();

public:
    tracing_configuration(tracing_configuration&& rhs);

public:
    tracing_configuration(
        const bool enabled,
        const boost::filesystem::path& output_directory,
        const masd::dogen::tracing_level level,
        const masd::dogen::tracing_format format,
        const bool enable_guids);

public:
    /**
     * @brief If true, the configurable aspect will be expressed.
     */
    /**@{*/
    bool enabled() const;
    tracing_configuration& enabled(const bool v);
    /**@}*/

    /**
     * @brief Directory in which to place the output.
     */
    /**@{*/
    const boost::filesystem::path& output_directory() const;
    boost::filesystem::path& output_directory();
    tracing_configuration& output_directory(const boost::filesystem::path& v);
    tracing_configuration& output_directory(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Dump all available probing information about transforms.
     */
    /**@{*/
    masd::dogen::tracing_level level() const;
    tracing_configuration& level(const masd::dogen::tracing_level v);
    /**@}*/

    /**
     * @brief Format to use when writting trace files.
     */
    /**@{*/
    masd::dogen::tracing_format format() const;
    tracing_configuration& format(const masd::dogen::tracing_format v);
    /**@}*/

    /**
     * @brief Enable GUIDs in probe stats.
     *
     * Disabling GUIDs makes comparisons easier.
     */
    /**@{*/
    bool enable_guids() const;
    tracing_configuration& enable_guids(const bool v);
    /**@}*/

public:
    bool operator==(const tracing_configuration& rhs) const;
    bool operator!=(const tracing_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(tracing_configuration& other) noexcept;
    tracing_configuration& operator=(tracing_configuration other);

private:
    bool enabled_;
    boost::filesystem::path output_directory_;
    masd::dogen::tracing_level level_;
    masd::dogen::tracing_format format_;
    bool enable_guids_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::tracing_configuration& lhs,
    masd::dogen::tracing_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

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
#ifndef DOGEN_TYPES_TRACING_CONFIGURATION_HPP
#define DOGEN_TYPES_TRACING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/types/tracing_level.hpp"
#include "dogen/types/tracing_format.hpp"
#include "dogen/types/tracing_backend.hpp"

namespace dogen {

/**
 * @brief Configuration related to transform tracing.
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
        const dogen::tracing_level level,
        const dogen::tracing_format format,
        const bool guids_enabled,
        const std::string& logging_impact,
        const bool use_short_names,
        const boost::filesystem::path& output_directory,
        const dogen::tracing_backend backend,
        const std::string& run_id);

public:
    /**
     * @brief Dump all available tracing information about transforms.
     */
    /**@{*/
    dogen::tracing_level level() const;
    tracing_configuration& level(const dogen::tracing_level v);
    /**@}*/

    /**
     * @brief Format to use when writting trace files.
     *
     * Only valid for the file backend.
     */
    /**@{*/
    dogen::tracing_format format() const;
    tracing_configuration& format(const dogen::tracing_format v);
    /**@}*/

    /**
     * @brief Enable GUIDs in probe stats.
     *
     * Disabling GUIDs makes comparisons easier.
     */
    /**@{*/
    bool guids_enabled() const;
    tracing_configuration& guids_enabled(const bool v);
    /**@}*/

    /**
     * @brief Additional information to tell tracing about the possible impact of logging.
     *
     * Informative string detailing whether logging was off, or set to debug etc. This is
     * required in order to be able to compare like-for-like numbers.
     */
    /**@{*/
    const std::string& logging_impact() const;
    std::string& logging_impact();
    tracing_configuration& logging_impact(const std::string& v);
    tracing_configuration& logging_impact(const std::string&& v);
    /**@}*/

    /**
     * @brief Use short directory and file names. Useful mainly on windows due to path
     * size limitations.
     */
    /**@{*/
    bool use_short_names() const;
    tracing_configuration& use_short_names(const bool v);
    /**@}*/

    const boost::filesystem::path& output_directory() const;
    boost::filesystem::path& output_directory();
    tracing_configuration& output_directory(const boost::filesystem::path& v);
    tracing_configuration& output_directory(const boost::filesystem::path&& v);

    /**
     * @brief Which backend to use for tracing.
     */
    /**@{*/
    dogen::tracing_backend backend() const;
    tracing_configuration& backend(const dogen::tracing_backend v);
    /**@}*/

    /**
     * @brief Identifier to use for the present run.
     */
    /**@{*/
    const std::string& run_id() const;
    std::string& run_id();
    tracing_configuration& run_id(const std::string& v);
    tracing_configuration& run_id(const std::string&& v);
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
    dogen::tracing_level level_;
    dogen::tracing_format format_;
    bool guids_enabled_;
    std::string logging_impact_;
    bool use_short_names_;
    boost::filesystem::path output_directory_;
    dogen::tracing_backend backend_;
    std::string run_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::tracing_configuration& lhs,
    dogen::tracing_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

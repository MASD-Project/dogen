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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_OPTIONS_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen/types/tracing_configuration.hpp"

namespace masd::dogen::coding::transforms {

class options final {
public:
    options(const options&) = default;
    ~options() = default;

public:
    options();

public:
    options(options&& rhs);

public:
    options(
        const boost::filesystem::path& log_file,
        const std::string& log_level,
        const boost::filesystem::path& target,
        const boost::filesystem::path& output_directory_path,
        const bool compatibility_mode,
        const boost::filesystem::path& probe_directory,
        const boost::optional<masd::dogen::tracing_configuration>& tracing);

public:
    /**
     * @brief Full path to the log file.
     */
    /**@{*/
    const boost::filesystem::path& log_file() const;
    boost::filesystem::path& log_file();
    void log_file(const boost::filesystem::path& v);
    void log_file(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief What level of logging to log at.
     */
    /**@{*/
    const std::string& log_level() const;
    std::string& log_level();
    void log_level(const std::string& v);
    void log_level(const std::string&& v);
    /**@}*/

    /**
     * @brief Full path to the model to generate.
     */
    /**@{*/
    const boost::filesystem::path& target() const;
    boost::filesystem::path& target();
    void target(const boost::filesystem::path& v);
    void target(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Full path to the directory in which to place the generated code.
     */
    /**@{*/
    const boost::filesystem::path& output_directory_path() const;
    boost::filesystem::path& output_directory_path();
    void output_directory_path(const boost::filesystem::path& v);
    void output_directory_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Try to process diagram even if there are errors.
     *
     * Only a certain class of errors are allowed, believed to be caused by backwards or
     * forwards compatibility problems: missing types or types that do not exist.
     */
    /**@{*/
    bool compatibility_mode() const;
    void compatibility_mode(const bool v);
    /**@}*/

    /**
     * @brief Full path to the directory in which to place probe information.
     */
    /**@{*/
    const boost::filesystem::path& probe_directory() const;
    boost::filesystem::path& probe_directory();
    void probe_directory(const boost::filesystem::path& v);
    void probe_directory(const boost::filesystem::path&& v);
    /**@}*/

    const boost::optional<masd::dogen::tracing_configuration>& tracing() const;
    boost::optional<masd::dogen::tracing_configuration>& tracing();
    void tracing(const boost::optional<masd::dogen::tracing_configuration>& v);
    void tracing(const boost::optional<masd::dogen::tracing_configuration>&& v);

public:
    bool operator==(const options& rhs) const;
    bool operator!=(const options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(options& other) noexcept;
    options& operator=(options other);

private:
    boost::filesystem::path log_file_;
    std::string log_level_;
    boost::filesystem::path target_;
    boost::filesystem::path output_directory_path_;
    bool compatibility_mode_;
    boost::filesystem::path probe_directory_;
    boost::optional<masd::dogen::tracing_configuration> tracing_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::transforms::options& lhs,
    masd::dogen::coding::transforms::options& rhs) {
    lhs.swap(rhs);
}

}

#endif

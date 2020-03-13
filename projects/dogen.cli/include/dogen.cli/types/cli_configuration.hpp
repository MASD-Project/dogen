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
#ifndef DOGEN_CLI_TYPES_CLI_CONFIGURATION_HPP
#define DOGEN_CLI_TYPES_CLI_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/variant.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.cli/types/dumpspecs_configuration.hpp"
#include "dogen.cli/types/conversion_configuration.hpp"
#include "dogen.cli/types/generation_configuration.hpp"

namespace dogen::cli {

/**
 * @brief Configuration specific to the CLI application.
 */
class cli_configuration final {
public:
    cli_configuration() = default;
    cli_configuration(const cli_configuration&) = default;
    ~cli_configuration() = default;

public:
    cli_configuration(cli_configuration&& rhs);

public:
    cli_configuration(
        const boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration, dogen::cli::dumpspecs_configuration>& activity,
        const boost::filesystem::path& byproduct_directory);

public:
    const boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration, dogen::cli::dumpspecs_configuration>& activity() const;
    boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration, dogen::cli::dumpspecs_configuration>& activity();
    cli_configuration& activity(const boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration, dogen::cli::dumpspecs_configuration>& v);
    cli_configuration& activity(const boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration, dogen::cli::dumpspecs_configuration>&& v);

    /**
     * @brief Directory in which to place all files not directly related to generated code.
     */
    /**@{*/
    const boost::filesystem::path& byproduct_directory() const;
    boost::filesystem::path& byproduct_directory();
    cli_configuration& byproduct_directory(const boost::filesystem::path& v);
    cli_configuration& byproduct_directory(const boost::filesystem::path&& v);
    /**@}*/

public:
    bool operator==(const cli_configuration& rhs) const;
    bool operator!=(const cli_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cli_configuration& other) noexcept;
    cli_configuration& operator=(cli_configuration other);

private:
    boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration, dogen::cli::dumpspecs_configuration> activity_;
    boost::filesystem::path byproduct_directory_;
};

}

namespace std {

template<>
inline void swap(
    dogen::cli::cli_configuration& lhs,
    dogen::cli::cli_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

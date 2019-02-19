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
#ifndef MASD_DOGEN_CLI_TYPES_CONFIGURATION_HPP
#define MASD_DOGEN_CLI_TYPES_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include "masd.dogen/types/configuration.hpp"
#include "masd.dogen.cli/types/cli_configuration.hpp"
#include "masd.dogen.utility/types/log/logging_configuration.hpp"

namespace masd::dogen::cli {

/**
 * @brief All of the configuration required by the command line application.
 */
class configuration final {
public:
    configuration() = default;
    configuration(const configuration&) = default;
    ~configuration() = default;

public:
    configuration(configuration&& rhs);

public:
    configuration(
        const boost::optional<masd::dogen::utility::log::logging_configuration>& logging,
        const masd::dogen::configuration& api,
        const masd::dogen::cli::cli_configuration& cli);

public:
    /**
     * @brief Configuration related to logging, if any.
     */
    /**@{*/
    const boost::optional<masd::dogen::utility::log::logging_configuration>& logging() const;
    boost::optional<masd::dogen::utility::log::logging_configuration>& logging();
    void logging(const boost::optional<masd::dogen::utility::log::logging_configuration>& v);
    void logging(const boost::optional<masd::dogen::utility::log::logging_configuration>&& v);
    /**@}*/

    const masd::dogen::configuration& api() const;
    masd::dogen::configuration& api();
    void api(const masd::dogen::configuration& v);
    void api(const masd::dogen::configuration&& v);

    const masd::dogen::cli::cli_configuration& cli() const;
    masd::dogen::cli::cli_configuration& cli();
    void cli(const masd::dogen::cli::cli_configuration& v);
    void cli(const masd::dogen::cli::cli_configuration&& v);

public:
    bool operator==(const configuration& rhs) const;
    bool operator!=(const configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(configuration& other) noexcept;
    configuration& operator=(configuration other);

private:
    boost::optional<masd::dogen::utility::log::logging_configuration> logging_;
    masd::dogen::configuration api_;
    masd::dogen::cli::cli_configuration cli_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::cli::configuration& lhs,
    masd::dogen::cli::configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

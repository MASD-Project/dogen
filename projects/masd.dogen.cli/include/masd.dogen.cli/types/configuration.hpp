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
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen/types/diffing_configuration.hpp"
#include "masd.dogen/types/tracing_configuration.hpp"
#include "masd.dogen.cli/types/weaving_configuration.hpp"
#include "masd.dogen.cli/types/conversion_configuration.hpp"
#include "masd.dogen.cli/types/generation_configuration.hpp"
#include "masd.dogen/types/error_handling_configuration.hpp"
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
        const boost::optional<masd::dogen::tracing_configuration>& tracing,
        const boost::optional<masd::dogen::diffing_configuration>& diffing,
        const boost::optional<masd::dogen::error_handling_configuration>& error_handling,
        const boost::filesystem::path& byproduct_output_directory,
        const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& activity);

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

    const boost::optional<masd::dogen::tracing_configuration>& tracing() const;
    boost::optional<masd::dogen::tracing_configuration>& tracing();
    void tracing(const boost::optional<masd::dogen::tracing_configuration>& v);
    void tracing(const boost::optional<masd::dogen::tracing_configuration>&& v);

    const boost::optional<masd::dogen::diffing_configuration>& diffing() const;
    boost::optional<masd::dogen::diffing_configuration>& diffing();
    void diffing(const boost::optional<masd::dogen::diffing_configuration>& v);
    void diffing(const boost::optional<masd::dogen::diffing_configuration>&& v);

    const boost::optional<masd::dogen::error_handling_configuration>& error_handling() const;
    boost::optional<masd::dogen::error_handling_configuration>& error_handling();
    void error_handling(const boost::optional<masd::dogen::error_handling_configuration>& v);
    void error_handling(const boost::optional<masd::dogen::error_handling_configuration>&& v);

    /**
     * @brief Directory in which to place all artefacts which are not directly related to code generation.
     *
     * These include traces, logs etc.
     */
    /**@{*/
    const boost::filesystem::path& byproduct_output_directory() const;
    boost::filesystem::path& byproduct_output_directory();
    void byproduct_output_directory(const boost::filesystem::path& v);
    void byproduct_output_directory(const boost::filesystem::path&& v);
    /**@}*/

    const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& activity() const;
    boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& activity();
    void activity(const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& v);
    void activity(const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>&& v);

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
    boost::optional<masd::dogen::tracing_configuration> tracing_;
    boost::optional<masd::dogen::diffing_configuration> diffing_;
    boost::optional<masd::dogen::error_handling_configuration> error_handling_;
    boost::filesystem::path byproduct_output_directory_;
    boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration> activity_;
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

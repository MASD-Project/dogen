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
#include <sstream>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/convenience.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/type_repository_io.hpp"
#include "dogen/annotations/io/archetype_location_repository_io.hpp"
#include "dogen/yarn/io/helpers/mapping_set_repository_io.hpp"
#include "dogen/yarn/types/helpers/probing_error.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/yarn/types/helpers/transform_prober.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.transform_prober"));

const std::string directory_missing("Probe data directory must be supplied.");
const std::string failed_delete("Failed to delete prober data directory.");
const std::string failed_create("Failed to create prober data directory.");

template<typename Ioable>
inline void write(const boost::filesystem::path& dir, const std::string& fn,
    const Ioable& target) {

    const auto path(dir / fn);
    BOOST_LOG_SEV(lg, debug) << "Writing: " << path.generic_string();

    boost::filesystem::ofstream stream(path);
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    stream << target;
}

}

namespace dogen {
namespace yarn {
namespace helpers {

transform_prober::transform_prober(
    const bool probe_data, const bool probe_stats,
    const bool probe_stats_graph,
    const boost::filesystem::path& probe_directory,
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp,
    const helpers::mapping_set_repository& msrp)
    : probe_data_(probe_data), probe_stats_(probe_stats),
      probe_stats_graph_(probe_stats_graph),
      probe_directory_(probe_directory) {

    /*
     * If any kind of probing was requested, we must have a directory
     * in which to place the probing data.
     */
    if (probe_data_ || probe_stats_ || probe_stats_graph_) {
        if (probe_directory_.empty()) {
            BOOST_LOG_SEV(lg, error) << directory_missing;
            BOOST_THROW_EXCEPTION(probing_error(directory_missing));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Prober initialised. Settings: "
                             << " probe data: " << probe_data
                             << " probe stats: " << probe_stats
                             << " probe stats graph: " << probe_stats_graph
                             << " probe data directory: "
                             << probe_directory.generic_string();

    if (!probe_data)
        return;

    handle_probe_directory();
    write_initial_inputs(alrp, atrp, msrp);
}

void transform_prober::handle_probe_directory() const {
    if (boost::filesystem::exists(probe_directory_)) {
        BOOST_LOG_SEV(lg, debug) << "Prober data already exists: "
                                 << probe_directory_.generic_string();

        boost::system::error_code ec;
        boost::filesystem::remove_all(probe_directory_, ec);
        if (ec) {
            BOOST_LOG_SEV(lg, error) << failed_delete;
            BOOST_THROW_EXCEPTION(probing_error(failed_delete));
        }
        BOOST_LOG_SEV(lg, debug) << "Deleted prober data directory.";
    }

    boost::system::error_code ec;
    boost::filesystem::create_directories(probe_directory_, ec);
    if (ec) {
        BOOST_LOG_SEV(lg, error) << failed_create;
        BOOST_THROW_EXCEPTION(probing_error(failed_create));
    }
    BOOST_LOG_SEV(lg, debug) << "Created prober data directory.";
}

void transform_prober::write_initial_inputs(
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp,
    const helpers::mapping_set_repository& msrp) const {

    BOOST_LOG_SEV(lg, debug) << "Writing initial inputs.";

    write(probe_directory_, "archetype_location_repository.json", alrp);
    write(probe_directory_, "type_repository.json", atrp);
    write(probe_directory_, "mapping_set_repository.json", msrp);

    BOOST_LOG_SEV(lg, debug) << "Finish writing initial inputs.";
}

} } }

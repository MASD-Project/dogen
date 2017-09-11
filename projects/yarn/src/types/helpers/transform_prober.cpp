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
#include <iomanip>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/convenience.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/type_repository_io.hpp"
#include "dogen/annotations/io/archetype_location_repository_io.hpp"
#include "dogen/yarn/io/helpers/mapping_set_repository_io.hpp"
#include "dogen/yarn/types/helpers/probing_error.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/yarn/types/helpers/transform_metrics.hpp"
#include "dogen/yarn/types/helpers/transform_prober.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.transform_prober"));

const char zero('0');
const unsigned int leading_zeros(3);
const std::string delimiter("-");
const std::string extension(".json");

const std::string chain_directory_exists("Directory for chain already exists: ");
const std::string directory_missing("Probe data directory must be supplied.");
const std::string failed_delete("Failed to delete prober data directory.");
const std::string failed_create("Failed to create prober data directory.");
const std::string unexpected_empty("The stack must not be empty.");

}

namespace dogen {
namespace yarn {
namespace helpers {

transform_prober::transform_prober(
    const bool probe_data, const bool probe_stats,
    const boost::filesystem::path& probe_directory,
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp,
    const helpers::mapping_set_repository& msrp)
    : current_directory_(probe_directory),
      probe_data_(probe_data), probe_stats_(probe_stats),
      probe_directory_(probe_directory) {

    validate();
    if (!probe_data_)
        return;

    handle_probe_directory();
    write_initial_inputs(alrp, atrp, msrp);
    transform_position_.push(1);
}

void transform_prober::validate() const {
    /*
     * If data probing was requested, we must have a directory in
     * which to place the data.
     */
    if (probe_data_ && probe_directory_.empty()) {
        BOOST_LOG_SEV(lg, error) << directory_missing;
        BOOST_THROW_EXCEPTION(probing_error(directory_missing));
    }

    BOOST_LOG_SEV(lg, debug) << "Prober initialised. Settings: "
                             << " probe data: " << probe_data_
                             << " probe stats: " << probe_stats_
                             << " probe data directory: "
                             << probe_directory_.generic_string();
}

bool transform_prober::probing_enabled() const {
    return probe_data_ || probe_stats_;
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

void transform_prober::handle_current_directory() const {
    ensure_transform_position_not_empty();

    const auto id(builder_.current().id());
    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top() << delimiter << id;
    current_directory_ /= s.str();

    if (boost::filesystem::exists(current_directory_)) {
        const auto gs(current_directory_.generic_string());
        BOOST_LOG_SEV(lg, error) << chain_directory_exists << gs;
        BOOST_THROW_EXCEPTION(probing_error(chain_directory_exists + gs));
    }

    boost::system::error_code ec;
    boost::filesystem::create_directories(current_directory_, ec);
    if (ec) {
        BOOST_LOG_SEV(lg, error) << failed_create;
        BOOST_THROW_EXCEPTION(probing_error(failed_create));
    }
    BOOST_LOG_SEV(lg, debug) << "Created current directory: "
                             << current_directory_.generic_string();
}

void transform_prober::ensure_transform_position_not_empty() const {
    if (transform_position_.empty()) {
        BOOST_LOG_SEV(lg, error) << unexpected_empty;
        BOOST_THROW_EXCEPTION(probing_error(unexpected_empty));
    }
}

boost::filesystem::path transform_prober::
full_path_for_writing(const std::string& id, const std::string& type) const {
    ensure_transform_position_not_empty();

    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top() << delimiter << id << delimiter
      << builder_.current().guid() << delimiter << type << extension;

    return current_directory_ / s.str();
}

void transform_prober::write_initial_inputs(
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp,
    const helpers::mapping_set_repository& msrp) const {

    BOOST_LOG_SEV(lg, debug) << "Writing initial inputs.";

    auto path(current_directory_ / "001-archetype_location_repository.json");
    BOOST_LOG_SEV(lg, debug) << "Writing: " << path.generic_string();
    write(path, alrp);

    path = current_directory_ / "001-type_repository.json";
    BOOST_LOG_SEV(lg, debug) << "Writing: " << path.generic_string();
    write(path, atrp);

    path = current_directory_ / "001-mapping_set_repository.json";
    BOOST_LOG_SEV(lg, debug) << "Writing: " << path.generic_string();
    write(path, msrp);

    BOOST_LOG_SEV(lg, debug) << "Finish writing initial inputs.";
}

void transform_prober::start_chain(const std::string& id) const {
    if (!probing_enabled())
        return;

    builder_.start(id);
    BOOST_LOG_SEV(lg, debug) << "Starting: " << id
                             << "(" << builder_.current().guid() << ")";

    if (!probe_data_)
        return;

    ++transform_position_.top();
    handle_current_directory();
    transform_position_.push(0);
}

void transform_prober::start_transform(const std::string& id) const {
    if (!probing_enabled())
        return;

    builder_.start(id);
    BOOST_LOG_SEV(lg, debug) << "Starting: " << id
                             << "(" << builder_.current().guid() << ")";
}

void transform_prober::end_chain() const {
    if (!probing_enabled())
        return;

    BOOST_LOG_SEV(lg, debug) << "Ending: " << builder_.current().id()
                             << " (" << builder_.current().guid() << ")";
    builder_.end();

    if (!probe_data_)
        return;

    ensure_transform_position_not_empty();
    transform_position_.pop();
    current_directory_ = current_directory_.parent_path();
}

void transform_prober::end_transform() const {
    if (!probing_enabled())
        return;

    BOOST_LOG_SEV(lg, debug) << "Ending: " << builder_.current().id()
                             << " (" << builder_.current().guid() << ")";
    builder_.end();
}

} } }

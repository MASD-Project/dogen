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
#include "dogen/yarn/types/helpers/transform_metrics_printer.hpp"
#include "dogen/yarn/types/helpers/transform_prober.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.transform_prober"));

const char zero('0');
const std::string empty;
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

transform_prober::transform_prober(const transforms::options& o,
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp,
    const helpers::mapping_set_repository& msrp)
    : builder_(o.log_level(), o.probe_all()),
      current_directory_(o.probe_directory()),
      probe_data_(o.probe_all()),
      probe_stats_(o.probe_all() || o.probe_stats()),
      disable_guids_in_stats_(o.probe_stats_disable_guids()),
      use_org_mode_(o.probe_stats_org_mode()),
      use_short_names_(o.probe_use_short_names()),
      probe_directory_(o.probe_directory()) {

    validate();

    if (!probing_enabled())
        return;

    handle_probe_directory();

    if (!probe_data_)
        return;

    transform_position_.push(0);
    write_initial_inputs(alrp, atrp, msrp);
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
    BOOST_LOG_SEV(lg, debug) << "Handling probe directory.";

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
    BOOST_LOG_SEV(lg, debug) << "Created prober data directory: "
                             << probe_directory_.generic_string();
}

void transform_prober::handle_current_directory() const {
    BOOST_LOG_SEV(lg, debug) << "Handling current directory change.";

    ensure_transform_position_not_empty();

    const auto id(builder_.current()->transform_id());
    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top();

    if (!use_short_names_)
        s << delimiter << id;

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

boost::filesystem::path
transform_prober::full_path_for_writing(const std::string& filename) const {
    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top();

    if (!use_short_names_)
        s << delimiter << filename;

    s << extension;

    return current_directory_ / s.str();
}

boost::filesystem::path transform_prober::full_path_for_writing(
    const std::string& transform_id, const std::string& type) const {
    ensure_transform_position_not_empty();

    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top();

    if (!use_short_names_) {
        s << delimiter << transform_id << delimiter
          << builder_.current()->guid();
    }

    s << delimiter << type << extension;

    return current_directory_ / s.str();
}

void transform_prober::write_initial_inputs(
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp,
    const helpers::mapping_set_repository& msrp) const {

    BOOST_LOG_SEV(lg, debug) << "Writing initial inputs.";

    ensure_transform_position_not_empty();
    auto path(full_path_for_writing("archetype_location_repository"));
    BOOST_LOG_SEV(lg, debug) << "Writing: " << path.generic_string();
    utility::filesystem::write(path, alrp);

    ++transform_position_.top();
    path = full_path_for_writing("type_repository");
    BOOST_LOG_SEV(lg, debug) << "Writing: " << path.generic_string();
    utility::filesystem::write(path, atrp);

    ++transform_position_.top();
    path = full_path_for_writing("mapping_set_repository");
    BOOST_LOG_SEV(lg, debug) << "Writing: " << path.generic_string();
    utility::filesystem::write(path, msrp);

    BOOST_LOG_SEV(lg, debug) << "Finish writing initial inputs.";
}

void transform_prober::start_transform(const std::string& transform_id) const {
    if (!probing_enabled())
        return;

    start_transform(transform_id, empty);
}

void transform_prober::start_chain(const std::string& transform_id) const {
    if (!probing_enabled())
        return;

    start_chain(transform_id, empty);
}

void transform_prober::start_chain(const std::string& transform_id,
    const std::string& model_id) const {
    if (!probing_enabled())
        return;

    BOOST_LOG_SEV(lg, debug) << "Starting: " << transform_id
                             << " (" << builder_.current()->guid() << ")";
    builder_.start(transform_id, model_id);

    if (!probe_data_)
        return;

    ++transform_position_.top();
    handle_current_directory();
    transform_position_.push(0);
}

void transform_prober::start_transform(const std::string& transform_id,
    const std::string& model_id) const {
    if (!probing_enabled())
        return;

    builder_.start(transform_id, model_id);
    BOOST_LOG_SEV(lg, debug) << "Starting: " << transform_id
                             << " (" << builder_.current()->guid() << ")";
}

void transform_prober::end_chain() const {
    if (!probing_enabled())
        return;

    BOOST_LOG_SEV(lg, debug) << "Ending: " << builder_.current()->transform_id()
                             << " (" << builder_.current()->guid() << ")";
    builder_.end();

    if (!probe_data_)
        return;

    ensure_transform_position_not_empty();
    transform_position_.pop();
    current_directory_ = current_directory_.parent_path();
    BOOST_LOG_SEV(lg, debug) << "Current directory is now: "
                             << current_directory_.generic_string();
}

void transform_prober::end_transform() const {
    if (!probing_enabled())
        return;

    BOOST_LOG_SEV(lg, debug) << "Ending: " << builder_.current()->transform_id()
                             << " (" << builder_.current()->guid() << ")";
    builder_.end();
}

void transform_prober::end_probing() const {
    BOOST_LOG_SEV(lg, debug) << "Finished probing.";

    if (!probe_stats_)
        return;

    const auto tm(builder_.build());
    const bool uom(use_org_mode_);
    const bool dgis(disable_guids_in_stats_);
    const auto s(transform_metrics_printer::print(dgis, uom, tm));
    const auto fn(uom ? "transform_stats.org" : "transform_stats.txt");
    utility::filesystem::write(probe_directory_ / fn, s);
}

} } }

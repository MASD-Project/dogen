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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/convenience.hpp>
#include "dogen/io/tracing_format_io.hpp"
#include "dogen/io/tracing_configuration_io.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/metrics.hpp"
#include "dogen.tracing/types/references_printer.hpp"
#include "dogen.tracing/types/metrics_printer.hpp"
#include "dogen.tracing/types/file_backend.hpp"

namespace {

const std::string id("tracing.file_backend");

using namespace dogen::utility::log;
auto lg(logger_factory(id));

const char zero('0');
const std::string empty;
const unsigned int leading_zeros(5);
const std::string delimiter("-");
const std::string extension(".json");

const std::string chain_directory_exists(
    "Directory for chain already exists: ");
const std::string directory_missing("Tracing data directory must be supplied.");
const std::string failed_delete("Failed to delete tracer data directory.");
const std::string failed_create("Failed to create tracer data directory.");
const std::string unexpected_empty("The stack must not be empty.");
const std::string invalid_tracing_format(
    "Invalid or unsupported tracing format: ");

boost::filesystem::path get_current_directory(
    const boost::optional<dogen::tracing_configuration>& cfg) {
    if (!cfg)
        return boost::filesystem::path();

    return cfg->output_directory();
}

}

namespace dogen::tracing {

file_backend::file_backend(const tracing_configuration& cfg,
    const std::string& version, const std::string& run_id,
    const std::string& activity, const std::string& logging_impact,
    const std::string& tracing_impact)
    : detailed_tracing_enabled_(cfg.level() == tracing_level::detail),
      configuration_(cfg),
      builder_(version, run_id, activity, logging_impact, tracing_impact),
      current_directory_(get_current_directory(cfg)) {

    /*
     * If data tracing was requested, we must have a directory in
     * which to place the data.
     */
    if (cfg.output_directory().empty()) {
        BOOST_LOG_SEV(lg, error) << directory_missing;
        BOOST_THROW_EXCEPTION(tracing_error(directory_missing));
    }

    BOOST_LOG_SEV(lg, debug) << "Tracer initialised. Configuration: "
                             << configuration_;


    handle_output_directory();

    if (!detailed_tracing_enabled_)
        return;

    transform_position_.push(0);
}

std::string file_backend::id() const {
    return ::id;
}

dogen::tracing_backend file_backend::tracing_backend() const {
    return dogen::tracing_backend::file;
}

void file_backend::handle_output_directory() const {
    BOOST_LOG_SEV(lg, debug) << "Handling output directory.";

    const auto& od(configuration_.output_directory());
    if (boost::filesystem::exists(od)) {
        BOOST_LOG_SEV(lg, debug) << "Output directory already exists: "
                                 << od.generic_string();

        boost::system::error_code ec;
        boost::filesystem::remove_all(od, ec);
        if (ec) {
            BOOST_LOG_SEV(lg, error) << failed_delete;
            BOOST_THROW_EXCEPTION(tracing_error(failed_delete));
        }
        BOOST_LOG_SEV(lg, debug) << "Deleted output data directory.";
    }

    boost::system::error_code ec;
    boost::filesystem::create_directories(od, ec);
    if (ec) {
        BOOST_LOG_SEV(lg, error) << failed_create;
        BOOST_THROW_EXCEPTION(tracing_error(failed_create));
    }
    BOOST_LOG_SEV(lg, debug) << "Created output data directory: "
                             << od.generic_string();
}

void file_backend::handle_current_directory() const {
    BOOST_LOG_SEV(lg, debug) << "Handling current directory change.";

    ensure_transform_position_not_empty();

    const auto id(builder_.current()->transform_id());
    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top();

    if (!configuration_.use_short_names())
        s << delimiter << id;

    current_directory_ /= s.str();

    if (boost::filesystem::exists(current_directory_)) {
        const auto gs(current_directory_.generic_string());
        BOOST_LOG_SEV(lg, error) << chain_directory_exists << gs;
        BOOST_THROW_EXCEPTION(tracing_error(chain_directory_exists + gs));
    }

    boost::system::error_code ec;
    boost::filesystem::create_directories(current_directory_, ec);
    if (ec) {
        BOOST_LOG_SEV(lg, error) << failed_create;
        BOOST_THROW_EXCEPTION(tracing_error(failed_create));
    }
    BOOST_LOG_SEV(lg, debug) << "Created current directory: "
                             << current_directory_.generic_string();
}

void file_backend::ensure_transform_position_not_empty() const {
    if (transform_position_.empty()) {
        BOOST_LOG_SEV(lg, error) << unexpected_empty;
        BOOST_THROW_EXCEPTION(tracing_error(unexpected_empty));
    }
}

boost::filesystem::path
file_backend::full_path_for_writing(const std::string& transform_id,
    const std::string& type, const std::string& model_id) const {
    ensure_transform_position_not_empty();

    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top();

    if (!configuration_.use_short_names()) {
        s << delimiter << transform_id << delimiter;

        if (!model_id.empty())
            s << model_id << delimiter;

        s << builder_.current()->guid();

    }

    s << delimiter << type << extension;

    const auto r(current_directory_ / s.str());
    BOOST_LOG_SEV(lg, debug) << "Computed full path for writing: "
                             << r.generic_string()
                             << " ID: " << model_id;
    return r;
}

boost::filesystem::path
file_backend::make_path(const boost::filesystem::path& dir,
    const std::string& fn, const tracing_format tf) const {

    boost::filesystem::path r(dir);
    switch(tf) {
    case tracing_format::plain:
        r /= fn + ".txt";
        break;
    case tracing_format::org_mode:
        r /= fn + ".org";
        break;
    case tracing_format::graphviz:
        r /= fn + ".dot";
        break;
    default: {
        BOOST_LOG_SEV(lg, error) << invalid_tracing_format << tf;
        BOOST_THROW_EXCEPTION(tracing_error(invalid_tracing_format +
                boost::lexical_cast<std::string>(tf)));
    } }
    return r;
}

void file_backend::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::tracing::file_backend\"" << " }";
}

void file_backend::add_references_graph(const std::string& root_vertex,
    const std::unordered_map<std::string, std::list<std::string>>&
    edges_per_model) const {
    root_vertex_ = root_vertex;
    edges_per_model_ = edges_per_model;
}


void file_backend::
start_run(const std::string& input_id, const std::string& input) const {
    if (!detailed_tracing_enabled_)
        return;

    ensure_transform_position_not_empty();
    const auto p(full_path_for_writing(input_id, "initial_input"));
    utility::filesystem::write(p, input);
    ++transform_position_.top();
}

void file_backend::end_run() const {
    BOOST_LOG_SEV(lg, debug) << "Finished tracing.";
    /*
     * Write the metrics.
     */
    const auto tm(builder_.build());
    const auto tf(configuration_.format());
    const bool dg(!configuration_.guids_enabled());
    const auto s(metrics_printer::print(dg, tf, tm));
    const auto& od(configuration_.output_directory());
    BOOST_LOG_SEV(lg, debug) << "Writing to output directory: '"
                             << od.generic_string() << "'";
    const std::string fn("transform_stats");
    const auto p(make_path(od, fn, tf));
    utility::filesystem::write(p, s);

    /*
     * Write the references.
     */
    const std::string fn2("references_graph");
    const auto p2(make_path(od, fn2, tf));
    const auto s2(references_printer::print(tf, root_vertex_, edges_per_model_));
    utility::filesystem::write(p2, s2);
}

void file_backend::start_chain(const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id) const {
    start_chain(parent_transform_instance_id,
        transform_id, transform_instance_id, empty);
}

void file_backend::start_chain(
    const std::string& /*parent_transform_instance_id*/,
    const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id) const {
    builder_.start(transform_id, transform_instance_id, model_id);
    BOOST_LOG_SEV(lg, debug) << "Starting: " << transform_id
                             << " (" << builder_.current()->guid() << ")";

    if (!detailed_tracing_enabled_)
        return;

    handle_current_directory();
    ++transform_position_.top();
    transform_position_.push(0);
}

void file_backend::start_chain(const std::string& parent_transform_instance_id,
    const std::string& transform_id, const std::string& transform_instance_id,
    const std::string& model_id, const std::string& input) const {
    start_chain(parent_transform_instance_id,
        transform_id, transform_instance_id, model_id);

    if (!detailed_tracing_enabled_)
        return;

    ensure_transform_position_not_empty();
    const auto p(full_path_for_writing(transform_id, "input", model_id));
    utility::filesystem::write(p, input);
    ++transform_position_.top();
}

void file_backend::end_chain(const std::string& /*parent_transform_instance_id*/,
    const std::string& /*transform_id*/,
    const std::string& /*transform_instance_id*/) const {
    BOOST_LOG_SEV(lg, debug) << "Ending: " << builder_.current()->transform_id()
                             << " (" << builder_.current()->guid() << ")";
    builder_.end();

    if (!detailed_tracing_enabled_)
        return;

    ensure_transform_position_not_empty();
    transform_position_.pop();
    current_directory_ = current_directory_.parent_path();
    BOOST_LOG_SEV(lg, debug) << "Current directory is now: "
                             << current_directory_.generic_string();
}

void file_backend::end_chain(const std::string& parent_transform_instance_id,
    const std::string& transform_id, const std::string& transform_instance_id,
    const std::string& model_id, const std::string& output) const {
    if (detailed_tracing_enabled_) {
        ensure_transform_position_not_empty();
        const auto id(builder_.current()->transform_id());
        const auto p(full_path_for_writing(id, "output", model_id));
        utility::filesystem::write(p, output);
    }
    end_chain(parent_transform_instance_id,
        transform_id, transform_instance_id);
}

void file_backend::
start_transform(const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id) const {
    start_transform(parent_transform_instance_id,
        transform_id, transform_instance_id,empty);
}

void file_backend::
start_transform(const std::string& /*parent_transform_instance_id*/,
    const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id) const {
    builder_.start(transform_id, transform_instance_id, model_id);
    BOOST_LOG_SEV(lg, debug) << "Starting: " << transform_id
                             << " (" << builder_.current()->guid() << ")";
}

void file_backend::start_transform(
    const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id,
    const std::string& input) const {
    start_transform(parent_transform_instance_id,
        transform_id, transform_instance_id, model_id);

    if (detailed_tracing_enabled_) {
        ensure_transform_position_not_empty();
        const auto p(full_path_for_writing(transform_id, "input", model_id));
        utility::filesystem::write(p, input);
        ++transform_position_.top();
    }
}

void file_backend::end_transform(
    const std::string& /*parent_transform_instance_id*/,
    const std::string& /*transform_id*/,
    const std::string& /*transform_instance_id*/) const {
    BOOST_LOG_SEV(lg, debug) << "Ending: " << builder_.current()->transform_id()
                             << " (" << builder_.current()->guid() << ")";
    builder_.end();
}

void file_backend::
end_transform(const std::string& parent_transform_instance_id,
    const std::string& transform_id, const std::string& transform_instance_id,
    const std::string& model_id, const std::string& output) const {
    if (detailed_tracing_enabled_) {
        ensure_transform_position_not_empty();
        const auto id(builder_.current()->transform_id());
        const auto p(full_path_for_writing(id, "output", model_id));
        utility::filesystem::write(p, output);
        ++transform_position_.top();
    }
    end_transform(parent_transform_instance_id,
        transform_id, transform_instance_id);
}

bool file_backend::operator==(const file_backend& /*rhs*/) const {
    return false;
}

}

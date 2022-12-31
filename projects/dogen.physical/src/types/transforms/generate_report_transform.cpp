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
#include <set>
#include <unordered_map>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/io/reporting_style_io.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/io/entities/physical_id_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/hash/entities/operation_type_hash.hpp"
#include "dogen.physical/hash/entities/operation_reason_hash.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/generate_report_transform.hpp"

namespace {

const std::string transform_id("physical.transforms.generate_report_transform");

const std::string reason_invalid("invalid");
const std::string reason_newly_generated("newly generated");
const std::string reason_changed_generated("changed generated");
const std::string reason_unchanged_generated("unchanged generated");
const std::string reason_already_exists("already exists");
const std::string reason_ignore_generated("ignore generated");
const std::string reason_force_write("force write");
const std::string reason_unexpected("unexpected");
const std::string reason_ignore_unexpected("ignore unexpected");
const std::string reason_ignore_regex("ignore regex");

const std::string type_invalid("invalid");
const std::string type_create_only("create_only");
const std::string type_write("write");
const std::string type_ignore("ignore");
const std::string type_remove("remove");

const std::string unexpected_operation_type(
    "Operation type is invalid or unsupported.");
const std::string unexpected_operation_reason(
    "Operation reason is invalid or unsupported.");
const std::string unexpected_destination(
    "Destination is invalid or unsupported: ");
const std::string unexpected_reporting_style(
    "Reporting style is invalid or unsupported: ");
const std::string empty_file_name("Empty file name supplied.");

const std::string org_extension(".org");
const std::string text_extension(".txt");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

using dogen::physical::transforms::transform_exception;
using dogen::physical::entities::operation_type;
void print_operation_type(const bool add_brackets,
    const operation_type ot, std::ostream& s) {
    if (add_brackets)
        s << "[";

    switch(ot) {
    case operation_type::invalid:
        s << type_invalid;
        break;
    case operation_type::create_only:
        s << type_create_only;
        break;
    case operation_type::write:
        s << type_write;
        break;
    case operation_type::ignore:
        s << type_ignore;
        break;
    case operation_type::remove:
        s << type_remove;
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unexpected_operation_type;
        BOOST_THROW_EXCEPTION(transform_exception(unexpected_operation_type));
    }

    if (add_brackets)
        s << "] ";
}

using dogen::physical::entities::operation_reason;
void print_operation_reason(const bool add_brackets,
    const operation_reason reason, std::ostream& s) {
    if (add_brackets)
        s << "[";

    switch(reason) {
    case operation_reason::invalid:
        s << reason_invalid;
        break;
    case operation_reason::newly_generated:
        s << reason_newly_generated;
        break;
    case operation_reason::changed_generated:
        s << reason_changed_generated;
        break;
    case operation_reason::unchanged_generated:
        s << reason_unchanged_generated;
        break;
    case operation_reason::already_exists:
        s << reason_already_exists;
        break;
    case operation_reason::ignore_generated:
        s << reason_ignore_generated;
        break;
    case operation_reason::force_write:
        s << reason_force_write;
        break;
    case operation_reason::unexpected:
        s << reason_unexpected;
        break;
    case operation_reason::ignore_unexpected:
        s << reason_ignore_unexpected;
        break;
    case operation_reason::ignore_regex:
        s << reason_ignore_regex;
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unexpected_operation_reason;
        BOOST_THROW_EXCEPTION(transform_exception(unexpected_operation_reason));
    }

    if (add_brackets)
        s << "] ";
}

std::list<boost::shared_ptr<dogen::physical::entities::artefact>>
gather_artefacts(const dogen::physical::entities::model& m) {
    std::list<boost::shared_ptr<dogen::physical::entities::artefact>> r;
    for (const auto& pr_pair : m.regions_by_logical_id()) {
        const auto& pr(pr_pair.second);
        for (const auto& a_pair : pr.artefacts_by_archetype())
            r.push_back(a_pair.second);
    }

    for (const auto& a : m.orphan_artefacts())
        r.push_back(a);

    return r;
}

void print_plain_report(std::ostream& s,
    const boost::filesystem::path& managed_dir,
    const std::list<boost::shared_ptr<dogen::physical::entities::artefact>>&
    artefacts) {
    for (auto& ptr : artefacts) {
        auto& a(*ptr);
        const auto p(a.file_path());
        if (p.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_file_name;
            BOOST_THROW_EXCEPTION(transform_exception(empty_file_name));
        }

        BOOST_LOG_SEV(lg, debug) << "Processing arefact: " << a.name().id();

        print_operation_type(true/*add_brackets*/, a.operation().type(), s);
        print_operation_reason(true/*add_brackets*/, a.operation().reason(), s);

        auto rp(p.lexically_relative(managed_dir));
        const auto gs(rp.generic_string());
        s << gs << std::endl;
    }
}

void print_org_mode_report(std::ostream& s,
    const boost::filesystem::path& managed_dir,
    const std::list<boost::shared_ptr<dogen::physical::entities::artefact>>&
    artefacts) {

    using namespace dogen::physical;
    std::unordered_map<operation_type,
                       std::unordered_map<operation_reason,
                                          std::set<std::string>
                                          >
                       > map;

    for (auto& ptr : artefacts) {
        auto& a(*ptr);
        const auto p(a.file_path());
        if (p.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_file_name;
            BOOST_THROW_EXCEPTION(transform_exception(empty_file_name));
        }

        BOOST_LOG_SEV(lg, debug) << "Processing arefact: " << a.name().id();
        const auto& op(a.operation());
        auto rp(p.lexically_relative(managed_dir));
        map[op.type()][op.reason()].insert(rp.generic_string());
    }

    s << "* All Operations (" << artefacts.size() << ")" << std::endl;
    for (const auto& first_pair : map) {
        s << "** Operation: ";
        print_operation_type(false/*add_brackets*/, first_pair.first, s);

        std::size_t count(0);
        for (const auto& second_pair : first_pair.second)
            count += second_pair.second.size();

        s << "(" << count << ")" << std::endl;

        for (const auto& second_pair : first_pair.second) {
            s << "*** Reason: ";
            print_operation_reason(false/*add_brackets*/, second_pair.first, s);
            s << " (" << second_pair.second.size() << ")" << std::endl;

            for (const auto& l : second_pair.second)
                s << "- " << l << std::endl;
        }
    }
}

void write_report(const std::string& contents, const std::string& model_name,
    const std::string& extension,
    const boost::filesystem::path& output_directory) {
    BOOST_LOG_SEV(lg, debug) << "Outputting report to: " << output_directory;

    using boost::filesystem::create_directories;
    create_directories(output_directory);

    boost::filesystem::path p(output_directory);
    p /= model_name + "_report" + extension;

    BOOST_LOG_SEV(lg, debug) << "Writing report file: " << p.generic_path()
                             << ". Size: " << contents.size();

    using dogen::utility::filesystem::write_file_content;
    write_file_content(p, contents);
}

}

namespace dogen::physical::transforms {

void generate_report_transform::
apply(const context& ctx, const entities::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "generate operation report transform", transform_id, m.name().simple(),
        *ctx.tracer(), m);

    /*
     * If the user did not request diffing, there is nothing to do.
     */
    if (!ctx.reporting_configuration()) {
        BOOST_LOG_SEV(lg, debug) << "Operatinal reporting not enabled.";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Creating report for model: "
                             << m.name().simple();
    std::ostringstream ss;
    const auto& cfg(*ctx.reporting_configuration());
    BOOST_LOG_SEV(lg, debug) << "Style requested: " << cfg.style();

    const auto artefacts(gather_artefacts(m));
    const auto md(m.managed_directories().front());
    std::string extension;
    switch(cfg.style()) {
    case reporting_style::plain:
        print_plain_report(ss, md, artefacts);
        extension = text_extension;
        break;
    case reporting_style::org_mode:
        print_org_mode_report(ss, md, artefacts);
        extension = org_extension;
        break;
    default: {
        const auto s(boost::lexical_cast<std::string>(cfg.style()));
        BOOST_LOG_SEV(lg, error) << unexpected_reporting_style << s;
        BOOST_THROW_EXCEPTION(
            transform_exception(unexpected_reporting_style + s));
    } }

    const auto c(ss.str());
    write_report(c, m.name().simple(), extension, cfg.output_directory());

    BOOST_LOG_SEV(lg, debug) << "Finished generating operational report.";
}

}

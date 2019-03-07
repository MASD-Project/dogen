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
#include <iostream> // FIXME
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen/io/reporting_style_io.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.extraction/types/transforms/transform_exception.hpp"
#include "masd.dogen.extraction/types/transforms/generate_report_transform.hpp"

namespace {

const std::string transform_id(
    "extraction.transforms.generate_report_transform");

const std::string reason_invalid("invalid");
const std::string reason_newly_generated("newly generated");
const std::string reason_changed_generated("changed generated");
const std::string reason_unchanged_generated("unchanged generated");
const std::string reason_already_exists("already exists");
const std::string reason_ignore_generated("ignore generated");
const std::string reason_force_write("force write");
const std::string reason_unexpected("unexpected");
const std::string reason_ignore_unexpected("ignore unexpected");

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

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

using masd::dogen::extraction::transforms::transform_exception;
using masd::dogen::extraction::meta_model::operation_type;
void print_operation_type(const operation_type ot, std::ostream& s) {
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
    s << "] ";
}

using masd::dogen::extraction::meta_model::operation_reason;
void print_operation_reason(const operation_reason reason, std::ostream& s) {
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
    default:
        BOOST_LOG_SEV(lg, error) << unexpected_operation_reason;
        BOOST_THROW_EXCEPTION(transform_exception(unexpected_operation_reason));
    }
    s << "] ";
}

void print_plain_report(std::ostream& s,
    const masd::dogen::extraction::meta_model::model& m) {
    const auto base(m.managed_directories().front());
    for (auto& a : m.artefacts()) {
        // FIXME: HACK: we seemt to have some blank artefacts atm.
        if (a.path().empty())
            continue;

        BOOST_LOG_SEV(lg, debug) << "Processing arefact: "
                                 << a.path().filename();

        print_operation_type(a.operation().type(), s);
        print_operation_reason(a.operation().reason(), s);

        auto rp(a.path().lexically_relative(base));
        const auto gs(rp.generic_string());
        s << gs << std::endl;
    }
}

void print_org_mode_report(std::ostream& s,
    const masd::dogen::extraction::meta_model::model& m) {

    using namespace masd::dogen::extraction;
    std::unordered_map<operation_type,
                       std::unordered_map<operation_reason,
                                          std::list<std::string>
                                          >
                       > map;

    const auto base(m.managed_directories().front());
    for (auto& a : m.artefacts()) {
        // FIXME: HACK: we seemt to have some blank artefacts atm.
        if (a.path().empty())
            continue;

        BOOST_LOG_SEV(lg, debug) << "Processing arefact: "
                                 << a.path().filename();

        const auto& op(a.operation());
        auto rp(a.path().lexically_relative(base));
        map[op.type()][op.reason()].push_back(rp.generic_string());
    }

    for (const auto& first_pair : map) {
        s << "* ";
        print_operation_type(first_pair.first, s);
        s << std::endl;
        for (const auto& second_pair : first_pair.second) {
            s << "** ";
            print_operation_reason(second_pair.first, s);
            s << std::endl;
            for (const auto& l : second_pair.second)
                s << l << std::endl;
        }
    }
}

void write_report(const std::string& contents, const std::string& model_name,
    const boost::filesystem::path& output_directory) {
    BOOST_LOG_SEV(lg, debug) << "Outputting report to: " << output_directory;

    using boost::filesystem::create_directories;
    create_directories(output_directory);

    boost::filesystem::path p(output_directory);
    p /= model_name + "_report.txt";

    BOOST_LOG_SEV(lg, debug) << "Writing report file: " << p.generic()
                             << ". Size: " << contents.size();

    using masd::dogen::utility::filesystem::write_file_content;
    write_file_content(p, contents);
}

}

namespace masd::dogen::extraction::transforms {

void generate_report_transform::
transform(const context& ctx, const meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "generate operation report transform", transform_id, m.name(),
        *ctx.tracer());

    /*
     * If the user did not request diffing, there is nothing to do.
     */
    if (!ctx.reporting_configuration()) {
        BOOST_LOG_SEV(lg, debug) << "Operatinal reporting not enabled.";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Creating report for model: " << m.name();
    std::ostringstream ss;
    const auto& cfg(*ctx.reporting_configuration());
    BOOST_LOG_SEV(lg, debug) << "Style requested: " << cfg.style();

    switch(cfg.style()) {
    case reporting_style::plain:
        print_plain_report(ss, m);
        break;
    case reporting_style::org_mode:
        print_org_mode_report(ss, m);
        break;
    default: {
        const auto s(boost::lexical_cast<std::string>(cfg.style()));
        BOOST_LOG_SEV(lg, error) << unexpected_reporting_style << s;
        BOOST_THROW_EXCEPTION(
            transform_exception(unexpected_reporting_style + s));
    } }

    const auto c(ss.str());
    write_report(c, m.name(), cfg.output_directory());

    BOOST_LOG_SEV(lg, debug) << "Finished generating operational report.";
}

}

/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#define BOOST_RESULT_OF_USE_DECLTYPE
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/config/validator.hpp"
#include "dogen/generator/housekeeper.hpp"
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/modeling/dia_to_sml.hpp"
#include "dogen/generator/outputters/factory.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/generator/modeling/director.hpp"
#include "dogen/generator/backends/factory.hpp"
#include "dogen/generator/generator.hpp"

using namespace dogen::utility::log;

namespace {

const std::string codegen_error("Error occurred during code generation: ");
const std::string incorrect_stdout_config(
    "Configuration for output to stdout is incorrect");

auto lg(logger_factory("generator"));

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

}

namespace dogen {
namespace generator {

generator::generator(const config::settings& s)
    : verbose_(s.troubleshooting().verbose()), settings_(s) {

    if (settings_.output().output_to_stdout())
        throw generation_failure(incorrect_stdout_config);

    config::validator::validate(s);
}

generator::
generator(const config::settings& s, const output_fn& o)
    : verbose_(s.troubleshooting().verbose()), settings_(s), output_(o) {

    if (!settings_.output().output_to_stdout() || !output_)
        throw generation_failure(incorrect_stdout_config);

    config::validator::validate(s);
}

bool generator::housekeeping_required() const {
    return
        !settings_.troubleshooting().stop_after_merging() &&
        !settings_.troubleshooting().stop_after_formatting() &&
        settings_.output().delete_extra_files() &&
        settings_.output().output_to_file();
}

void generator::output(const outputters::outputter::value_type& o) const {
    if (settings_.troubleshooting().stop_after_formatting()) {
        BOOST_LOG_SEV(lg, warn) << "Stopping after formatting so not outputting";
        return;
    }

    if (o.empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, nothing to output.";

        return;
    }

    const auto lambda([&](outputters::outputter::ptr p) { p->output(o); });
    outputters::factory f(settings_.output(), output_);
    boost::for_each(f.create(), lambda);
}

void generator::generate(backends::backend& b) const {
    const auto r(b.generate());
    output(r);

    if (!housekeeping_required())
        return;

    using boost::adaptors::transformed;
    using boost::filesystem::path;
    std::set<path> expected_files;
    boost::copy(r | transformed([&](std::pair<path, std::string> p) {
                return p.first;
            }),
        std::inserter(expected_files, expected_files.end()));

    housekeeper hk(b.managed_directories(), expected_files, verbose_);
    hk.tidy_up();
}

void generator::generate(const sml::model& m) const {
    const auto lambda([&](backends::backend::ptr p) { generate(*p); });
    backends::factory f(m, settings_);
    boost::for_each(f.create(), lambda);
}

boost::optional<sml::model> generator::merge_models() const {
    modeling::director d(settings_);
    const auto r(d.create_model());

    if (settings_.troubleshooting().stop_after_merging()) {
        BOOST_LOG_SEV(lg, info) << "Stopping after merging so not returning"
                                << " merged model";

        return boost::optional<sml::model>();
    }
    return r;
}

void generator::generate() const {
    BOOST_LOG_SEV(lg, info) << "Code generator started.";
    BOOST_LOG_SEV(lg, debug) << "Settings: " << settings_;

    try {
        const auto o(merge_models());
        if (o)
            generate(*o);
    } catch (boost::exception& e) {
        std::ostringstream s;
        s << "Code generation failure.";
        e << errmsg_info(s.str());
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Code generator finished.";
}

} }

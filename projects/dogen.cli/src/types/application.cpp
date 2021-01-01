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
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <boost/variant.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen/types/specs.hpp"
#include "dogen/types/reporting_style.hpp"
#include "dogen/lexical_cast/reporting_style_lc.hpp"
#include "dogen.cli/types/configuration_validator.hpp"
#include "dogen.cli/types/application_exception.hpp"
#include "dogen.cli/types/application.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cli.application"));

const std::string unsupported_style("Reporting style is not supported: ");

using dogen::generator;
using dogen::converter;
using dogen::spec_dumper;
using dogen::cli::configuration;
using dogen::cli::application_exception;
using dogen::cli::generation_configuration;
using dogen::cli::conversion_configuration;
using dogen::cli::dumpspecs_configuration;

/**
 * @brief Wrap text.
 *
 * Copied from https://www.rosettacode.org/wiki/Word_wrap#C.2B.2B
 */
std::string wrap(const char *text, size_t line_length = 72) {
    std::istringstream words(text);
    std::ostringstream wrapped;
    std::string word;

    if (words >> word) {
        wrapped << word;
        size_t space_left = line_length - word.length();
        while (words >> word) {
            if (space_left < word.length() + 1) {
                wrapped << '\n' << word;
                space_left = line_length - word.length();
            } else {
                wrapped << ' ' << word;
                space_left -= word.length() + 1;
            }
        }
    }
    return wrapped.str();
}

void print_specs_plain(const dogen::specs& s, std::ostream& o) {
    if (s.categories().empty()) {
        o << "No specs found" << std::endl;
        return;
    }

    bool is_first(true);
    for (const auto& g : s.categories()) {
        if (!is_first)
            o << std::endl;

        o << "Category: " << g.name() << std::endl
          << "Purpose: " << g.description() << std::endl;

        for (const auto& e : g.entries()) {
            o << "    " << e.name() << ": "
              << e.description() << std::endl;
        }
        is_first = false;
    }
}

void print_specs_org_mode(const dogen::specs& s, std::ostream& o) {
    o << "* All" << std::endl << std::endl
      << "Dump of all specifications for Dogen." << std::endl << std::endl;

    if (s.categories().empty()) {
        o << "No specs found" << std::endl;
        return;
    }

    for (const auto& g : s.categories()) {
        o << "** " << g.name() << std::endl << std::endl
          << g.description() << std::endl << std::endl;

        for (const auto& e : g.entries()) {
            o << "*** " << e.name() << std::endl << std::endl
              << wrap(e.description().c_str()) << std::endl << std::endl;
        }
    }
}

void print_specs(const dogen::specs& s, const dogen::reporting_style rs,
    std::ostream& o) {
    using dogen::reporting_style;
    if (rs == reporting_style::plain)
        print_specs_plain(s, o);
    else if (rs == reporting_style::org_mode)
        print_specs_org_mode(s, o);
    else {
        const auto str(boost::lexical_cast<std::string>(rs));
        BOOST_LOG_SEV(lg, warn) << unsupported_style << str;
        BOOST_THROW_EXCEPTION(application_exception(unsupported_style + str));
    }
}

/**
 * @brief Given the configuration selected by the user, dispatches to
 * the appropriate activity.
 */
class activity_dispatcher : public boost::static_visitor<> {
public:
    activity_dispatcher(const converter& c, const generator& g,
        const spec_dumper& sd, const configuration& cfg)
        : converter_(c), generator_(g), dumper_(sd), configuration_(cfg) {}

public:
    /**
     * @brief Dispatches to the converter.
     */
    void operator()(const conversion_configuration& cfg) const {
        converter_.convert(configuration_.api(), cfg.source(),
            cfg.destination());
    }

    /**
     * @brief Dispatches to the generator.
     */
    void operator()(const generation_configuration& cfg) const {
        generator_.generate(configuration_.api(), cfg.target(),
            cfg.reference_model_directories(), cfg.output_directory());
    }

    /**
     * @brief Dispatches to the spec dumper.
     */
    void operator()(const dumpspecs_configuration& cfg) const {
        const auto s(dumper_.dump(configuration_.api()));
        print_specs(s, cfg.style(), std::cout);
    }

private:
    const converter& converter_;
    const generator& generator_;
    const spec_dumper& dumper_;
    const configuration& configuration_;
};

}

namespace dogen::cli {

application::
application(const converter& c, const generator& g, const spec_dumper& sd)
    : converter_(c), generator_(g), dumper_(sd) {}

void application::run(const configuration& cfg) const {
    BOOST_LOG_SEV(lg, debug) << "Application started.";

    /*
     * Before anything else, lets make sure the configuration makes
     * sense. No point in proceeding otherwise.
     */
    configuration_validator::validate(cfg);
    activity_dispatcher d(converter_, generator_, dumper_, cfg);
    boost::apply_visitor(d, cfg.cli().activity());

    BOOST_LOG_SEV(lg, debug) << "Application finished.";
}

}

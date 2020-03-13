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
#include <ostream>
#include <boost/variant/apply_visitor.hpp>
#include "dogen.cli/io/cli_configuration_io.hpp"
#include "dogen.cli/io/dumpspecs_configuration_io.hpp"
#include "dogen.cli/io/conversion_configuration_io.hpp"
#include "dogen.cli/io/generation_configuration_io.hpp"

namespace boost {

struct boost_variant_dogen_cli_generation_configuration_dogen_cli_conversion_configuration_dogen_cli_dumpspecs_configuration_visitor : public boost::static_visitor<> {
    boost_variant_dogen_cli_generation_configuration_dogen_cli_conversion_configuration_dogen_cli_dumpspecs_configuration_visitor(std::ostream& s) : stream_(s) {
        s << "{ " << "\"__type__\": " << "\"boost::variant\"" << ", ";
        s << "\"data\": ";
    }

    ~boost_variant_dogen_cli_generation_configuration_dogen_cli_conversion_configuration_dogen_cli_dumpspecs_configuration_visitor() { stream_ << " }"; }

    void operator()(const dogen::cli::generation_configuration& v) const {
        stream_ << v;
    }

    void operator()(const dogen::cli::conversion_configuration& v) const {
        stream_ << v;
    }

    void operator()(const dogen::cli::dumpspecs_configuration& v) const {
        stream_ << v;
    }

private:
    std::ostream& stream_;
};

inline std::ostream& operator<<(std::ostream& s, const boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration, dogen::cli::dumpspecs_configuration>& v) {
    boost::apply_visitor(boost_variant_dogen_cli_generation_configuration_dogen_cli_conversion_configuration_dogen_cli_dumpspecs_configuration_visitor(s), v);
    return s;
}

}

namespace dogen::cli {

std::ostream& operator<<(std::ostream& s, const cli_configuration& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cli::cli_configuration\"" << ", "
      << "\"activity\": " << v.activity() << ", "
      << "\"byproduct_directory\": " << "\"" << v.byproduct_directory().generic_string() << "\""
      << " }";
    return(s);
}

}

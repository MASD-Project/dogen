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
#include <boost/throw_exception.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "masd.dogen/version.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.coding/io/meta_model/generation_marker_io.hpp"
#include "masd.dogen.generation/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation/types/formatters/generation_marker_formatter.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("generation.generation_marker_formatter"));

const std::string default_message("This file was generated by Dogen.");
const std::string default_warning("WARNING: do not edit this file.");
const std::string generation_timestamp("Generation timestamp: ");
const std::string product_version("Generated by MASD Dogen v" DOGEN_VERSION);

}

namespace masd::dogen::generation::formatters {

void generation_marker_formatter::
format(std::ostream& s, const coding::meta_model::generation_marker& gm) const {
    if (gm.message().empty())
        s << default_message << std::endl;
    else
        s << gm.message() << std::endl;

    if (gm.add_date_time()) {
        using namespace boost::posix_time;
        ptime now(second_clock::local_time());
        s << generation_timestamp << to_iso_extended_string(now) << std::endl;
    }

    if (gm.add_dogen_version())
        s << product_version << std::endl;

    if (gm.add_warning())
        s << default_warning << std::endl;
}

}

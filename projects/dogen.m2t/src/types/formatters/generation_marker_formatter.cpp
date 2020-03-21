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
#include "dogen/config.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/io/entities/decoration/generation_marker_io.hpp"
#include "dogen.m2t/types/formatters/formatting_error.hpp"
#include "dogen.m2t/types/formatters/generation_marker_formatter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("m2t.generation_marker_formatter"));

const std::string default_message("This file was generated by Dogen.");
const std::string default_warning("WARNING: do not edit this file manually.");
const std::string generation_timestamp_msg("Generation timestamp: ");
const std::string model_sha1_hash_msg("Model SHA1 hash: ");
const std::string product_version("Generated by MASD Dogen v" DOGEN_VERSION);

}

namespace dogen::m2t::formatters {

void generation_marker_formatter::format(std::ostream& s,
    const std::string& generation_timestamp,
    const std::string& origin_shah1_hash,
    const logical::entities::decoration::generation_marker& gm) const {
    BOOST_LOG_SEV(lg, trace) << "Marker: " << gm;

    if (gm.message().empty())
        s << default_message << std::endl;
    else
        s << gm.message() << std::endl;

    if (gm.add_date_time())
        s << generation_timestamp_msg << generation_timestamp << std::endl;

    if (gm.add_origin_sha1_hash())
        s << model_sha1_hash_msg << origin_shah1_hash << std::endl;

    if (gm.add_warning())
        s << default_warning << std::endl;

    if (gm.add_dogen_version())
        s << product_version << std::endl;
}

}

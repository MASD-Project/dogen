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
#include <istream>
#include <boost/filesystem/fstream.hpp>
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.utility/filesystem/file.hpp"
#include "masd.dogen.formatting/types/hydration_error.hpp"
#include "masd.dogen.formatting/types/licence_text_hydrator.hpp"

using namespace masd::dogen::utility::log;

namespace {

auto lg(logger_factory("formatting.licence_text_hydrator"));
const std::string failed_to_open_file("Failed to open file: ");

}

namespace masd::dogen::formatting {

std::string licence_text_hydrator::hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, debug) << "Reading stream.";
    const auto r(dogen::utility::filesystem::read_file_content(s));
    BOOST_LOG_SEV(lg, debug) << "Read stream successfully.";
    return r;
}

std::string licence_text_hydrator::
hydrate(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Reading file: " << gs;

    boost::filesystem::ifstream s(p);
    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << ": " << gs;
        BOOST_THROW_EXCEPTION(hydration_error(failed_to_open_file + gs));
    }

    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Read file successfully.";
    return r;
}

}

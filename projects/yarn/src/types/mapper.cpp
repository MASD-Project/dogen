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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/types/mapper.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.mapper"));

}

namespace dogen {
namespace yarn {

mapper::mapper(const mapping_repository& /*mrp*/) /*: mapping_repository_(mrp)*/ { }

intermediate_model
mapper::map(const languages to, const intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started mapping. Model: " << im.name().id();
    BOOST_LOG_SEV(lg, debug) << "Mapping to: " << to;

    auto r(im);
    r.input_language(to);
    r.output_languages().clear();
    r.output_languages().push_back(to);

    BOOST_LOG_SEV(lg, debug) << "Output language: " << r.output_languages();
    BOOST_LOG_SEV(lg, debug) << "Finished mapping.";

    return r;
}

} }

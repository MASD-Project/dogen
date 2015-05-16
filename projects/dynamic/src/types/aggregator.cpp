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
#include <unordered_map>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/types/aggregator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.aggregator"));

const std::string duplicate_field_definition(
    "Field definition already inserted: ");

}

namespace dogen {
namespace dynamic {

std::list<std::pair<std::string, std::list<std::string> > >
aggregator::aggregate(
    const std::list<std::pair<std::string, std::string>>& raw_data) const {

    for (const auto pair : raw_data) {
    }

    std::list<std::pair<std::string, std::list<std::string> > > r;
    return r;
}

} }

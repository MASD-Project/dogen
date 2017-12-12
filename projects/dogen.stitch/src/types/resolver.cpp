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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/stitch/types/resolution_error.hpp"
#include "dogen/stitch/types/resolver.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("stitch.resolver"));

const std::string key_not_found("Key not found: ");

}

namespace dogen {
namespace stitch {

resolver::resolver(const std::unordered_map<std::string, std::string>& kvps)
    : kvps_(kvps) {}

std::string resolver::resolve(const std::string& k) const {
    const auto i (kvps_.find(k));
    if (i == kvps_.end()) {
        BOOST_LOG_SEV(lg, error) << key_not_found << k;
        BOOST_THROW_EXCEPTION(resolution_error(key_not_found + k));
    }
    return i->second;
}

} }

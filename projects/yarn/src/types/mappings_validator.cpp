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
#include "dogen/yarn/types/validation_error.hpp"
#include "dogen/yarn/types/mappings_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.mappings_validator"));

const std::string default_mapping_set_name("default.mapping_set");
const std::string missing_default_mapping_set(
    "Could not find the default mapping set: " + default_mapping_set_name);

}

namespace dogen {
namespace yarn {

void mappings_validator::validate(const std::unordered_map<std::string,
    std::list<mapping>>& mappings_by_set_name) const {

    bool found_default(false);
    for (const auto& pair : mappings_by_set_name) {
        const auto& n(pair.first);

        if (n == default_mapping_set_name)
            found_default = true;

        //const auto& mappings(pair.second);
    }

    /*
     * The default mapping set must be present.
     */
    if (!found_default) {
        BOOST_LOG_SEV(lg, error) << missing_default_mapping_set;
        BOOST_THROW_EXCEPTION(validation_error(missing_default_mapping_set));
    }
}

} }

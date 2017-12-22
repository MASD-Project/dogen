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
#include <unordered_set>
#include <boost/throw_exception.hpp>
#include "dogen.utility/io/unordered_set_io.hpp"
#include "dogen.utility/log/logger.hpp"
#include "dogen.templating/types/wale/validation_error.hpp"
#include "dogen.templating/types/wale/validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("templating.wale.validator"));

const std::string key_error("Expected key not supplied: ");

}

namespace dogen {
namespace templating {
namespace wale {

void validator::validate(const text_template& tt) const {
    std::unordered_set<std::string> s;
    for (const auto& kvp : tt.properties().supplied_kvps())
        s.insert(kvp.first);

    BOOST_LOG_SEV(lg, debug) << " Supplied keys: " << s;

    const auto& e(tt.properties().expected_keys());
    BOOST_LOG_SEV(lg, debug) << " Expected keys: " << e;

    /*
     * Ensure that all expected keys have been supplied. We may have
     * received additional keys, but we don't care about those.
     */
    for (const auto ek : e) {
        const auto i(s.find(ek));
        if (i == s.end()) {
            BOOST_LOG_SEV(lg, error) << key_error + ek;
            BOOST_THROW_EXCEPTION(validation_error(key_error + ek));
        }
    }
}

} } }

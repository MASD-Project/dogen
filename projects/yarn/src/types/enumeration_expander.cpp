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
#include <set>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/enumeration_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.enumeration_expander"));

const std::string duplicate_enumerator("Duplicate enumerator name: ");

}

namespace dogen {
namespace yarn {

void enumeration_expander::expand(intermediate_model& im) {

    /*
     * Setup the invalid enumeration.
     */
    dogen::yarn::enumerator invalid;

    if (im.language() == languages::csharp)
        invalid.name("Invalid");
    else
        invalid.name("invalid");

    invalid.documentation("Represents an uninitialised enum");
    invalid.value("0");

    for (auto& pair : im.enumerations()) {
        auto& e(pair.second);

        std::vector<enumerator> enumerators;
        enumerators.reserve(e.enumerators().size() + 1);
        enumerators.push_back(invalid);

        /*
         * Update the value of each enumerator, and ensure the
         * enumerator names are unique. Note that position zero is
         * already taken by "invalid".
         */
        unsigned int pos(1);
        std::set<std::string> enumerator_names;
        for (const auto& en : e.enumerators()) {
            const auto n(en.name());
            const auto i(enumerator_names.find(n));
            if (i != enumerator_names.end()) {
                BOOST_LOG_SEV(lg, error) << duplicate_enumerator << n;
                BOOST_THROW_EXCEPTION(
                    expansion_error(duplicate_enumerator + n));
            }

            auto copy(en);
            copy.value(boost::lexical_cast<std::string>(pos));
            enumerators.push_back(copy);
            ++pos;
        }
        e.enumerators(enumerators);
    }
}

} }

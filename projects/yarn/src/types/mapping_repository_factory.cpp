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
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/mapping_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.mapping_repository_factory"));

const std::string missing_upsilon("Upsilon mapping was not provided. LAM ID: ");
const std::string duplicate_lam_id("Duplicate language agnostic id: ");
const std::string duplicate_upsilon_id("Duplicate upsilon id: ");

}

namespace dogen {
namespace yarn {

mapping_repository
mapping_repository_factory::make(const std::list<element_mapping>& ems) const {
    mapping_repository r;
    for (const auto& em : ems) {
        const auto lam_id(em.id());
        const auto i(em.names_by_language().find(languages::upsilon));
        if (i == em.names_by_language().end()) {
            BOOST_LOG_SEV(lg, error) << missing_upsilon << lam_id;
            BOOST_THROW_EXCEPTION(building_error(missing_upsilon + lam_id));
        }
        const std::string upsilon_id(i->second.id());

        for (const auto& pair : em.names_by_language()) {
            const auto l(pair.first);
            if (l == languages::upsilon)
                continue;

            const auto& n(pair.second);
            {
                const auto pair(std::make_pair(lam_id, n));
                auto& map(r.by_language_agnostic_id()[l]);
                const auto inserted(map.insert(pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_lam_id << lam_id;
                    BOOST_THROW_EXCEPTION(
                        building_error(duplicate_lam_id + lam_id));
                }
            }

            {
                const auto pair(std::make_pair(upsilon_id, n));
                auto& map(r.by_upsilon_id()[l]);
                const auto inserted(map.insert(pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_upsilon_id
                                             << upsilon_id;
                    BOOST_THROW_EXCEPTION(
                        building_error(duplicate_upsilon_id + upsilon_id));
                }
            }
        }
    }
    return r;
}

} }

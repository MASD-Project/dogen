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
#include "dogen/annotations/types/building_error.hpp"
#include "dogen/annotations/types/repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.repository_factory"));

const std::string duplicate_qualified_name(
    "Qualified name defined more than once: ");

}

namespace dogen {
namespace annotations {

type_repository
repository_factory::make(const std::list<type>& fds) const {
    type_repository r;
    r.all_types(fds);

    for (const auto& fd : fds) {
        const auto n(fd.name().qualified());
        const auto pair(std::make_pair(n, fd));
        const auto result(r.types_by_name().insert(pair));
        if (!result.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << n;
            BOOST_THROW_EXCEPTION(building_error(duplicate_qualified_name + n));
        }

        const auto& oh(fd.ownership_hierarchy());
        if (!oh.facet_name().empty())
            r.types_by_facet_name()[oh.facet_name()].push_back(fd);

        if (!oh.formatter_name().empty())
            r.types_by_formatter_name()[oh.formatter_name()]
                .push_back(fd);

        if (!oh.model_name().empty())
            r.types_by_model_name()[oh.model_name()]
                .push_back(fd);
    }

    return r;
}

} }

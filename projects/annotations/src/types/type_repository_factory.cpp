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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/set_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/annotations/io/type_repository_io.hpp"
#include "dogen/annotations/io/ownership_hierarchy_io.hpp"
#include "dogen/annotations/types/instantiator.hpp"
#include "dogen/annotations/types/building_error.hpp"
#include "dogen/annotations/types/json_hydrator.hpp"
#include "dogen/annotations/types/type_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.type_repository_factory"));

const std::string duplicate_qualified_name(
    "Qualified name defined more than once: ");

}

namespace dogen {
namespace annotations {

std::list<type> type_repository_factory::hydrate_directories(
    const std::forward_list<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, info) << "Finding all files in: " << dirs;
    const auto files(dogen::utility::filesystem::find_files(dirs));
    BOOST_LOG_SEV(lg, info) << "Files found: " << files;

    json_hydrator jh;
    std::list<type> r;
    for (const auto& f : files) {
        auto fds(jh.hydrate(f));
        r.splice(r.end(), fds);
    }
    BOOST_LOG_SEV(lg, info) << "Finished hydrating all files.";
    return r;
}

std::list<type> type_repository_factory::instantiate_templates(
    const std::forward_list<ownership_hierarchy>& oh,
    const std::list<type>& fds) const {
    std::list<type> r;

    const instantiator ins(oh);
    unsigned int counter(0);
    for (const auto fd : fds) {
        if (!ins.is_instantiable(fd)) {
            r.push_back(fd);
            continue;
        }

        r.splice(r.end(), ins.instantiate(fd));
        ++counter;
    }

    BOOST_LOG_SEV(lg, debug) << "Number of templates instantiated: " << counter;
    return r;
}

type_repository type_repository_factory::
create_repository(const std::list<type>& fds) const {

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

type_repository type_repository_factory::make(
    const std::forward_list<ownership_hierarchy>& ohs,
    const std::forward_list<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, info) << "Generating repository.";
    BOOST_LOG_SEV(lg, info) << "Ownership hierarchy: " << ohs;

    const auto original(hydrate_directories(dirs));
    const auto instantiated(instantiate_templates(ohs, original));
    const auto r(create_repository(instantiated));

    BOOST_LOG_SEV(lg, info) << "Generated repository: " << r;
    return r;
}

} }

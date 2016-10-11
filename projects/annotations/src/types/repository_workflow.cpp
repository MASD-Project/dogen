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
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/annotations/io/repository_io.hpp"
#include "dogen/annotations/io/ownership_hierarchy_io.hpp"
#include "dogen/annotations/types/instantiator.hpp"
#include "dogen/annotations/types/workflow_error.hpp"
#include "dogen/annotations/types/hydration_workflow.hpp"
#include "dogen/annotations/types/repository_factory.hpp"
#include "dogen/annotations/types/repository_workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.repository_workflow"));

}

namespace dogen {
namespace annotations {

std::list<type> repository_workflow::hydrate_directories_activity(
    const std::forward_list<boost::filesystem::path>& dirs) const {
    hydration_workflow w;
    return w.hydrate(dirs);
}

std::list<type> repository_workflow::instantiate_templates_activity(
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

repository repository_workflow::create_repository_activity(
    const std::list<type>& fds) const {
    repository_factory f;
    return f.make(fds);
}

repository repository_workflow::execute(
    const std::forward_list<ownership_hierarchy>& oh,
    const std::forward_list<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, info) << "Generating repository.";
    BOOST_LOG_SEV(lg, info) << "Ownership hierarchy: " << oh;

    const auto original(hydrate_directories_activity(dirs));
    const auto instantiated(instantiate_templates_activity(oh, original));
    const auto r(create_repository_activity(instantiated));

    BOOST_LOG_SEV(lg, info) << "Generated repository: " << r;
    return r;
}

} }

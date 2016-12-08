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
#include <boost/make_shared.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/name_flattener.hpp"
#include "dogen/quilt.csharp/types/fabric/visual_studio_project.hpp"
#include "dogen/quilt.csharp/types/fabric/visual_studio_solution.hpp"
#include "dogen/quilt.csharp/types/fabric/visual_studio_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quit.csharp.fabric.visual_studio_project_factory"));

const std::string dot(".");
const std::string proj_extension(".csproj");
const std::string sln_extension(".sln");

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace fabric {

std::string visual_studio_factory::
obtain_project_name(const yarn::intermediate_model& im) const {
    yarn::name_flattener nfl(false/*detect_model_name*/);
    const auto ns(nfl.flatten(im.name()));

    using boost::algorithm::join;
    const auto r(join(ns, dot));
    return r;
}

boost::shared_ptr<yarn::element> visual_studio_factory::
make_solution(const std::string& project_name,
    const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Visual Studio Solution.";

    yarn::name_factory nf;
    const auto sn(project_name + sln_extension);
    const auto n(nf.build_element_in_model(im.name(), sn));

    auto r(boost::make_shared<visual_studio_solution>());
    r->name(n);
    r->origin_type(im.origin_type());

    BOOST_LOG_SEV(lg, debug) << "Generated Visual Studio Solution.";

    return r;
}

boost::shared_ptr<yarn::element> visual_studio_factory::
make_project(const std::string& project_name,
    const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Visual Studio Project.";

    yarn::name_factory nf;
    const auto sn(project_name + proj_extension);
    const auto n(nf.build_element_in_model(im.name(), sn));

    auto r(boost::make_shared<visual_studio_project>());
    r->name(n);
    r->origin_type(im.origin_type());
    r->project_name(project_name);

    BOOST_LOG_SEV(lg, debug) << "Generated Visual Studio Project.";

    return r;
}

std::list<boost::shared_ptr<yarn::element>> visual_studio_factory::
make(const yarn::intermediate_model& im) const {
    const auto pn(obtain_project_name(im));

    std::list<boost::shared_ptr<yarn::element>> r;
    r.push_back(make_solution(pn, im));
    r.push_back(make_project(pn, im));

    return r;
}

} } } }

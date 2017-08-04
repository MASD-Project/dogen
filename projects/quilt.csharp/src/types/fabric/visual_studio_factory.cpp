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
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/types/helpers/name_flattener.hpp"
#include "dogen/quilt.csharp/types/fabric/traits.hpp"
#include "dogen/quilt.csharp/types/fabric/meta_name_factory.hpp"
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

visual_studio_factory::type_group visual_studio_factory::make_type_group(
    const annotations::type_repository& atrp) const {

    type_group r;
    const annotations::type_repository_selector s(atrp);

    const auto& psg(traits::visual_studio_project_solution_guid());
    r.project_solution_guid = s.select_type_by_name(psg);

    const auto& pg(traits::visual_studio_project_guid());
    r.project_guid = s.select_type_by_name(pg);

    return r;
}

visual_studio_configuration visual_studio_factory::
make_configuration(const type_group& tg,
    const annotations::annotation& ra) const {

    visual_studio_configuration r;
    const annotations::entry_selector s(ra);

    const auto& psg(tg.project_solution_guid);
    r.project_solution_guid(s.get_text_content_or_default(psg));

    const auto& pg(tg.project_guid);
    r.project_guid(s.get_text_content_or_default(pg));

    return r;
}

visual_studio_configuration visual_studio_factory::
make_configuration(const annotations::type_repository& atrp,
    const annotations::annotation& ra) const {

    const auto tg(make_type_group(atrp));
    const auto r(make_configuration(tg, ra));
    return r;
}

std::string visual_studio_factory::
obtain_project_name(const yarn::meta_model::intermediate_model& im) const {
    yarn::helpers::name_flattener nfl(false/*detect_model_name*/);
    const auto ns(nfl.flatten(im.name()));

    using boost::algorithm::join;
    const auto r(join(ns, dot));
    return r;
}

boost::shared_ptr<yarn::meta_model::element> visual_studio_factory::
make_solution(const visual_studio_configuration cfg,
    const std::string& project_name,
    const yarn::meta_model::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Visual Studio Solution.";

    yarn::helpers::name_factory nf;
    const auto sn(project_name + sln_extension);
    const auto n(nf.build_element_in_model(im.name(), sn));

    auto r(boost::make_shared<visual_studio_solution>());
    r->name(n);
    r->meta_name(meta_name_factory::make_visual_studio_solution_name());
    r->origin_type(im.origin_type());
    r->project_name(project_name);
    r->project_guid(cfg.project_guid());
    r->project_solution_guid(cfg.project_solution_guid());

    BOOST_LOG_SEV(lg, debug) << "Generated Visual Studio Solution.";

    return r;
}

boost::shared_ptr<yarn::meta_model::element> visual_studio_factory::
make_project(const visual_studio_configuration cfg,
    const std::string& project_name,
    const yarn::meta_model::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Visual Studio Project.";

    yarn::helpers::name_factory nf;
    const auto sn(project_name + proj_extension);
    const auto n(nf.build_element_in_model(im.name(), sn));

    auto r(boost::make_shared<visual_studio_project>());
    r->name(n);
    r->meta_name(meta_name_factory::make_visual_studio_project_name());
    r->origin_type(im.origin_type());
    r->project_name(project_name);
    r->project_guid(cfg.project_guid());

    BOOST_LOG_SEV(lg, debug) << "Generated Visual Studio Project.";

    return r;
}

std::list<boost::shared_ptr<yarn::meta_model::element>> visual_studio_factory::
make(const annotations::type_repository& atrp,
    const yarn::meta_model::intermediate_model& im) const {

    const auto pn(obtain_project_name(im));
    const auto ra(im.root_module()->annotation());
    const auto cfg(make_configuration(atrp, ra));

    std::list<boost::shared_ptr<yarn::meta_model::element>> r;
    r.push_back(make_solution(cfg, pn, im));
    r.push_back(make_project(cfg, pn, im));

    return r;
}

} } } }

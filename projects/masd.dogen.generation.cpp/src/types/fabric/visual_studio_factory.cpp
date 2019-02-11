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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.annotations/types/entry_selector.hpp"
#include "masd.dogen.annotations/types/type_repository_selector.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/helpers/name_factory.hpp"
#include "masd.dogen.coding/types/helpers/name_flattener.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_project.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_solution.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(
        "quit.cpp.fabric.visual_studio_project_factory"));

const std::string dot(".");
const std::string proj_extension(".vcxproj");
const std::string sln_extension(".sln");

}

namespace masd::dogen::generation::cpp::fabric {

visual_studio_factory::type_group visual_studio_factory::make_type_group(
    const annotations::type_repository& atrp) const {

    type_group r;
    const annotations::type_repository_selector s(atrp);

    using formatters::traits;
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
obtain_project_name(const coding::meta_model::model& m) const {
    coding::helpers::name_flattener nfl(false/*detect_model_name*/);
    const auto ns(nfl.flatten(m.name()));

    using boost::algorithm::join;
    const auto r(join(ns, dot));
    return r;
}

boost::shared_ptr<coding::meta_model::element>
visual_studio_factory::make_solution(const visual_studio_configuration cfg,
    const std::string& project_name,
    const coding::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Visual Studio Solution.";

    coding::helpers::name_factory nf;
    const auto sn(project_name + "-vc" + sln_extension);
    const auto n(nf.build_element_in_model(m.name(), sn));

    auto r(boost::make_shared<visual_studio_solution>());
    r->name(n);
    r->meta_name(meta_name_factory::make_visual_studio_solution_name());
    r->origin_type(coding::meta_model::origin_types::target);
    r->project_name(project_name);
    r->project_guid(cfg.project_guid());
    r->project_solution_guid(cfg.project_solution_guid());

    BOOST_LOG_SEV(lg, debug) << "Generated Visual Studio Solution.";

    return r;
}

boost::shared_ptr<coding::meta_model::element>
visual_studio_factory::make_project(const visual_studio_configuration cfg,
    const std::string& project_name,
    const coding::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Visual Studio Project.";

    coding::helpers::name_factory nf;
    const auto sn(project_name + proj_extension);
    const auto n(nf.build_element_in_model(m.name(), sn));

    auto r(boost::make_shared<visual_studio_project>());
    r->name(n);
    r->meta_name(meta_name_factory::make_visual_studio_project_name());
    r->origin_type(coding::meta_model::origin_types::target);
    r->project_name(project_name);
    r->project_guid(cfg.project_guid());

    BOOST_LOG_SEV(lg, debug) << "Generated Visual Studio Project.";

    return r;
}

std::list<boost::shared_ptr<coding::meta_model::element>> visual_studio_factory::
make(const annotations::type_repository& atrp,
    const coding::meta_model::model& m) const {

    const auto pn(obtain_project_name(m));
    const auto ra(m.root_module()->annotation());
    const auto cfg(make_configuration(atrp, ra));

    std::list<boost::shared_ptr<coding::meta_model::element>> r;
    r.push_back(make_solution(cfg, pn, m));
    r.push_back(make_project(cfg, pn, m));

    return r;
}

}

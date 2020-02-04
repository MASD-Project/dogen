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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.assets/types/meta_model/structural/module.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.assets/types/helpers/name_flattener.hpp"
#include "dogen.generation.csharp/types/fabric/traits.hpp"
#include "dogen.generation.csharp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.csharp/types/fabric/visual_studio_project.hpp"
#include "dogen.generation.csharp/types/fabric/visual_studio_solution.hpp"
#include "dogen.generation.csharp/types/fabric/visual_studio_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quit.csharp.fabric.visual_studio_project_factory"));

const std::string dot(".");
const std::string proj_extension(".csproj");
const std::string sln_extension(".sln");

}

namespace dogen::generation::csharp::fabric {

using assets::meta_model::origin_types;
using assets::meta_model::technical_space;

visual_studio_factory::feature_group
visual_studio_factory::make_feature_group(
    const variability::meta_model::feature_model& fm) const {

    feature_group r;
    const variability::helpers::feature_selector s(fm);

    const auto& psg(traits::visual_studio_project_solution_guid());
    r.project_solution_guid = s.get_by_name(psg);

    const auto& pg(traits::visual_studio_project_guid());
    r.project_guid = s.get_by_name(pg);

    return r;
}

visual_studio_configuration visual_studio_factory::
make_configuration(const feature_group& tg,
    const variability::meta_model::configuration& cfg) const {

    visual_studio_configuration r;
    const variability::helpers::configuration_selector s(cfg);

    const auto& psg(tg.project_solution_guid);
    r.project_solution_guid(s.get_text_content_or_default(psg));

    const auto& pg(tg.project_guid);
    r.project_guid(s.get_text_content_or_default(pg));

    return r;
}

visual_studio_configuration visual_studio_factory::
make_configuration(const variability::meta_model::feature_model& fm,
    const variability::meta_model::configuration& cfg) const {

    const auto fg(make_feature_group(fm));
    const auto r(make_configuration(fg, cfg));
    return r;
}

std::string visual_studio_factory::
obtain_project_name(const generation::meta_model::model& m) const {
    assets::helpers::name_flattener nfl(false/*detect_model_name*/);
    const auto ns(nfl.flatten(m.name()));

    using boost::algorithm::join;
    const auto r(join(ns, dot));
    return r;
}

boost::shared_ptr<assets::meta_model::element> visual_studio_factory::
make_solution(const visual_studio_configuration cfg,
    const std::string& project_name,
    const generation::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Visual Studio Solution.";

    assets::helpers::name_factory nf;
    const auto sn(project_name + sln_extension);
    const auto n(nf.build_element_in_model(m.name(), sn));

    auto r(boost::make_shared<visual_studio_solution>());
    r->name(n);
    r->meta_name(meta_name_factory::make_visual_studio_solution_name());
    r->origin_type(origin_types::target);
    r->intrinsic_technical_space(technical_space::sln);
    r->project_name(project_name);
    r->project_guid(cfg.project_guid());
    r->project_solution_guid(cfg.project_solution_guid());
    r->configuration(
        boost::make_shared<variability::meta_model::configuration>());
    r->configuration()->name().simple(r->name().simple());
    r->configuration()->name().qualified(r->name().qualified().dot());

    BOOST_LOG_SEV(lg, debug) << "Generated Visual Studio Solution.";

    return r;
}

boost::shared_ptr<assets::meta_model::element> visual_studio_factory::
make_project(const visual_studio_configuration cfg,
    const std::string& project_name,
    const generation::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Visual Studio Project.";

    assets::helpers::name_factory nf;
    const auto sn(project_name + proj_extension);
    const auto n(nf.build_element_in_model(m.name(), sn));

    auto r(boost::make_shared<visual_studio_project>());
    r->name(n);
    r->meta_name(meta_name_factory::make_visual_studio_project_name());
    r->origin_type(origin_types::target);
    r->intrinsic_technical_space(technical_space::xml);
    r->project_name(project_name);
    r->project_guid(cfg.project_guid());
    r->configuration(
        boost::make_shared<variability::meta_model::configuration>());
    r->configuration()->name().simple(r->name().simple());
    r->configuration()->name().qualified(r->name().qualified().dot());

    BOOST_LOG_SEV(lg, debug) << "Generated Visual Studio Project.";

    return r;
}

std::list<boost::shared_ptr<assets::meta_model::element>>
visual_studio_factory::make(const variability::meta_model::feature_model& /*fm*/,
    const generation::meta_model::model& /*m*/) const {
    /*
    const auto pn(obtain_project_name(m));
    const auto rcfg(*m.root_module()->configuration());
    const auto cfg(make_configuration(fm, rcfg));
    */

    std::list<boost::shared_ptr<assets::meta_model::element>> r;
    /*
    r.push_back(make_solution(cfg, pn, m));
    r.push_back(make_project(cfg, pn, m));
    */

    return r;
}

}

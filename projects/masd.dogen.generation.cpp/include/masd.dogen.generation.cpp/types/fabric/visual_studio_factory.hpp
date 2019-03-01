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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_VISUAL_STUDIO_FACTORY_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_VISUAL_STUDIO_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.annotations/types/type.hpp"
#include "masd.dogen.annotations/types/annotation.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.generation/types/meta_model/model.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_configuration.hpp"

namespace masd::dogen::generation::cpp::fabric {

class visual_studio_factory final {
private:
    struct type_group {
        annotations::type project_solution_guid;
        annotations::type project_guid;
    };

    type_group make_type_group(const annotations::type_repository& atrp) const;

    visual_studio_configuration make_configuration(const type_group& tg,
        const annotations::annotation& ra) const;

    visual_studio_configuration make_configuration(
        const annotations::type_repository& atrp,
        const annotations::annotation& ra) const;

private:
    std::string obtain_project_name(
        const generation::meta_model::model& m) const;

private:
    boost::shared_ptr<coding::meta_model::element>
    make_solution(const visual_studio_configuration cfg,
        const std::string& project_name,
        const generation::meta_model::model& m) const;

    boost::shared_ptr<coding::meta_model::element>
    make_project(const visual_studio_configuration cfg,
        const std::string& project_name,
        const generation::meta_model::model& m) const;

public:
    std::list<boost::shared_ptr<coding::meta_model::element>>
    make(const annotations::type_repository& atrp,
        const generation::meta_model::model& m) const;
};

}

#endif

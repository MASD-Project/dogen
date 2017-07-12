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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_VISUAL_STUDIO_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_VISUAL_STUDIO_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"
#include "dogen/quilt.cpp/types/fabric/visual_studio_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

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
        const yarn::meta_model::intermediate_model& im) const;

private:
    boost::shared_ptr<yarn::meta_model::element>
    make_solution(const visual_studio_configuration cfg,
        const std::string& project_name,
        const yarn::meta_model::intermediate_model& im) const;

    boost::shared_ptr<yarn::meta_model::element>
    make_project(const visual_studio_configuration cfg,
        const std::string& project_name,
        const yarn::meta_model::intermediate_model& im) const;

public:
    std::list<boost::shared_ptr<yarn::meta_model::element>>
    make(const annotations::type_repository& atrp,
        const yarn::meta_model::intermediate_model& im) const;
};

} } } }

#endif

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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_ELEMENT_VISITOR_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.generation.cpp/types/fabric/registrar_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/element_visitor.hpp"
#include "masd.dogen.generation.cpp/types/fabric/cmakelists_fwd.hpp"
#include "masd.dogen.generation.cpp/types/fabric/master_header_fwd.hpp"
#include "masd.dogen.generation.cpp/types/fabric/msbuild_targets_fwd.hpp"
#include "masd.dogen.generation.cpp/types/fabric/common_odb_options_fwd.hpp"
#include "masd.dogen.generation.cpp/types/fabric/object_odb_options_fwd.hpp"
#include "masd.dogen.generation.cpp/types/fabric/forward_declarations_fwd.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_project_fwd.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_solution_fwd.hpp"

namespace masd::dogen::generation::cpp::fabric {

/**
 * @brief Visitor for element
 */
class element_visitor : public masd::dogen::coding::meta_model::element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    using masd::dogen::coding::meta_model::element_visitor::visit;

    /**
     * @brief Accept visits for type masd::dogen::generation::cpp::fabric::cmakelists
     */
    /**@{*/
    virtual void visit(const masd::dogen::generation::cpp::fabric::cmakelists&) const { }
    virtual void visit(const masd::dogen::generation::cpp::fabric::cmakelists&) { }
    virtual void visit(masd::dogen::generation::cpp::fabric::cmakelists&) const { }
    virtual void visit(masd::dogen::generation::cpp::fabric::cmakelists&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::generation::cpp::fabric::common_odb_options
     */
    /**@{*/
    virtual void visit(const masd::dogen::generation::cpp::fabric::common_odb_options&) const { }
    virtual void visit(const masd::dogen::generation::cpp::fabric::common_odb_options&) { }
    virtual void visit(masd::dogen::generation::cpp::fabric::common_odb_options&) const { }
    virtual void visit(masd::dogen::generation::cpp::fabric::common_odb_options&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::generation::cpp::fabric::forward_declarations
     */
    /**@{*/
    virtual void visit(const masd::dogen::generation::cpp::fabric::forward_declarations&) const { }
    virtual void visit(const masd::dogen::generation::cpp::fabric::forward_declarations&) { }
    virtual void visit(masd::dogen::generation::cpp::fabric::forward_declarations&) const { }
    virtual void visit(masd::dogen::generation::cpp::fabric::forward_declarations&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::generation::cpp::fabric::master_header
     */
    /**@{*/
    virtual void visit(const masd::dogen::generation::cpp::fabric::master_header&) const { }
    virtual void visit(const masd::dogen::generation::cpp::fabric::master_header&) { }
    virtual void visit(masd::dogen::generation::cpp::fabric::master_header&) const { }
    virtual void visit(masd::dogen::generation::cpp::fabric::master_header&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::generation::cpp::fabric::msbuild_targets
     */
    /**@{*/
    virtual void visit(const masd::dogen::generation::cpp::fabric::msbuild_targets&) const { }
    virtual void visit(const masd::dogen::generation::cpp::fabric::msbuild_targets&) { }
    virtual void visit(masd::dogen::generation::cpp::fabric::msbuild_targets&) const { }
    virtual void visit(masd::dogen::generation::cpp::fabric::msbuild_targets&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::generation::cpp::fabric::object_odb_options
     */
    /**@{*/
    virtual void visit(const masd::dogen::generation::cpp::fabric::object_odb_options&) const { }
    virtual void visit(const masd::dogen::generation::cpp::fabric::object_odb_options&) { }
    virtual void visit(masd::dogen::generation::cpp::fabric::object_odb_options&) const { }
    virtual void visit(masd::dogen::generation::cpp::fabric::object_odb_options&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::generation::cpp::fabric::registrar
     */
    /**@{*/
    virtual void visit(const masd::dogen::generation::cpp::fabric::registrar&) const { }
    virtual void visit(const masd::dogen::generation::cpp::fabric::registrar&) { }
    virtual void visit(masd::dogen::generation::cpp::fabric::registrar&) const { }
    virtual void visit(masd::dogen::generation::cpp::fabric::registrar&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::generation::cpp::fabric::visual_studio_project
     */
    /**@{*/
    virtual void visit(const masd::dogen::generation::cpp::fabric::visual_studio_project&) const { }
    virtual void visit(const masd::dogen::generation::cpp::fabric::visual_studio_project&) { }
    virtual void visit(masd::dogen::generation::cpp::fabric::visual_studio_project&) const { }
    virtual void visit(masd::dogen::generation::cpp::fabric::visual_studio_project&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::generation::cpp::fabric::visual_studio_solution
     */
    /**@{*/
    virtual void visit(const masd::dogen::generation::cpp::fabric::visual_studio_solution&) const { }
    virtual void visit(const masd::dogen::generation::cpp::fabric::visual_studio_solution&) { }
    virtual void visit(masd::dogen::generation::cpp::fabric::visual_studio_solution&) const { }
    virtual void visit(masd::dogen::generation::cpp::fabric::visual_studio_solution&) { }
    /**@}*/
};

inline element_visitor::~element_visitor() noexcept { }

}

#endif

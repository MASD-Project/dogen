/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_SML_TYPES_MODEL_ELEMENT_VISITOR_HPP
#define DOGEN_SML_TYPES_MODEL_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/entity_fwd.hpp"
#include "dogen/sml/types/model_element_fwd.hpp"
#include "dogen/sml/types/module_fwd.hpp"
#include "dogen/sml/types/service_fwd.hpp"
#include "dogen/sml/types/typed_element_fwd.hpp"
#include "dogen/sml/types/value_fwd.hpp"

namespace dogen {
namespace sml {

class model_element_visitor {
public:
    virtual ~model_element_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::sml::module
     */
    /**@{*/
    virtual void visit(const dogen::sml::module&) const { }
    virtual void visit(const dogen::sml::module&) { }
    virtual void visit(dogen::sml::module&) const { }
    virtual void visit(dogen::sml::module&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::sml::value
     */
    /**@{*/
    virtual void visit(const dogen::sml::value&) const { }
    virtual void visit(const dogen::sml::value&) { }
    virtual void visit(dogen::sml::value&) const { }
    virtual void visit(dogen::sml::value&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::sml::entity
     */
    /**@{*/
    virtual void visit(const dogen::sml::entity&) const { }
    virtual void visit(const dogen::sml::entity&) { }
    virtual void visit(dogen::sml::entity&) const { }
    virtual void visit(dogen::sml::entity&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::sml::service
     */
    /**@{*/
    virtual void visit(const dogen::sml::service&) const { }
    virtual void visit(const dogen::sml::service&) { }
    virtual void visit(dogen::sml::service&) const { }
    virtual void visit(dogen::sml::service&) { }
    /**@}*/
};

inline model_element_visitor::~model_element_visitor() noexcept { }

} }

#endif

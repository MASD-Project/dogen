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
#ifndef DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_TYPES_BASE_VISITOR_HPP
#define DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_TYPES_BASE_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/trivial_inheritance/types/descendant2_fwd.hpp"
#include "dogen/test_models/trivial_inheritance/types/descendant3_fwd.hpp"

namespace dogen {
namespace test_models {
namespace trivial_inheritance {

/**
 * @brief Visitor for base
 */
class base_visitor {
public:
    virtual ~base_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::test_models::trivial_inheritance::descendant2
     */
    /**@{*/
    virtual void visit(const dogen::test_models::trivial_inheritance::descendant2&) const { }
    virtual void visit(const dogen::test_models::trivial_inheritance::descendant2&) { }
    virtual void visit(dogen::test_models::trivial_inheritance::descendant2&) const { }
    virtual void visit(dogen::test_models::trivial_inheritance::descendant2&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::test_models::trivial_inheritance::descendant3
     */
    /**@{*/
    virtual void visit(const dogen::test_models::trivial_inheritance::descendant3&) const { }
    virtual void visit(const dogen::test_models::trivial_inheritance::descendant3&) { }
    virtual void visit(dogen::test_models::trivial_inheritance::descendant3&) const { }
    virtual void visit(dogen::test_models::trivial_inheritance::descendant3&) { }
    /**@}*/
};

inline base_visitor::~base_visitor() noexcept { }

} } }

#endif

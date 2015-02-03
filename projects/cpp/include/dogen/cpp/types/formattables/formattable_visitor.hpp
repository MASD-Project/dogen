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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FORMATTABLE_VISITOR_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FORMATTABLE_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/cpp/types/formattables/class_info_fwd.hpp"
#include "dogen/cpp/types/formattables/cmakelists_info_fwd.hpp"
#include "dogen/cpp/types/formattables/concept_info_fwd.hpp"
#include "dogen/cpp/types/formattables/enum_info_fwd.hpp"
#include "dogen/cpp/types/formattables/exception_info_fwd.hpp"
#include "dogen/cpp/types/formattables/namespace_info_fwd.hpp"
#include "dogen/cpp/types/formattables/new_class_info_fwd.hpp"
#include "dogen/cpp/types/formattables/odb_options_info_fwd.hpp"
#include "dogen/cpp/types/formattables/primitive_info_fwd.hpp"
#include "dogen/cpp/types/formattables/registrar_info_fwd.hpp"
#include "dogen/cpp/types/formattables/visitor_info_fwd.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class formattable_visitor {
public:
    virtual ~formattable_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::cpp::formattables::class_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::class_info&) const { }
    virtual void visit(const dogen::cpp::formattables::class_info&) { }
    virtual void visit(dogen::cpp::formattables::class_info&) const { }
    virtual void visit(dogen::cpp::formattables::class_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::cmakelists_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::cmakelists_info&) const { }
    virtual void visit(const dogen::cpp::formattables::cmakelists_info&) { }
    virtual void visit(dogen::cpp::formattables::cmakelists_info&) const { }
    virtual void visit(dogen::cpp::formattables::cmakelists_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::enum_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::enum_info&) const { }
    virtual void visit(const dogen::cpp::formattables::enum_info&) { }
    virtual void visit(dogen::cpp::formattables::enum_info&) const { }
    virtual void visit(dogen::cpp::formattables::enum_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::exception_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::exception_info&) const { }
    virtual void visit(const dogen::cpp::formattables::exception_info&) { }
    virtual void visit(dogen::cpp::formattables::exception_info&) const { }
    virtual void visit(dogen::cpp::formattables::exception_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::registrar_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::registrar_info&) const { }
    virtual void visit(const dogen::cpp::formattables::registrar_info&) { }
    virtual void visit(dogen::cpp::formattables::registrar_info&) const { }
    virtual void visit(dogen::cpp::formattables::registrar_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::odb_options_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::odb_options_info&) const { }
    virtual void visit(const dogen::cpp::formattables::odb_options_info&) { }
    virtual void visit(dogen::cpp::formattables::odb_options_info&) const { }
    virtual void visit(dogen::cpp::formattables::odb_options_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::namespace_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::namespace_info&) const { }
    virtual void visit(const dogen::cpp::formattables::namespace_info&) { }
    virtual void visit(dogen::cpp::formattables::namespace_info&) const { }
    virtual void visit(dogen::cpp::formattables::namespace_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::visitor_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::visitor_info&) const { }
    virtual void visit(const dogen::cpp::formattables::visitor_info&) { }
    virtual void visit(dogen::cpp::formattables::visitor_info&) const { }
    virtual void visit(dogen::cpp::formattables::visitor_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::new_class_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::new_class_info&) const { }
    virtual void visit(const dogen::cpp::formattables::new_class_info&) { }
    virtual void visit(dogen::cpp::formattables::new_class_info&) const { }
    virtual void visit(dogen::cpp::formattables::new_class_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::concept_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::concept_info&) const { }
    virtual void visit(const dogen::cpp::formattables::concept_info&) { }
    virtual void visit(dogen::cpp::formattables::concept_info&) const { }
    virtual void visit(dogen::cpp::formattables::concept_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::formattables::primitive_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::formattables::primitive_info&) const { }
    virtual void visit(const dogen::cpp::formattables::primitive_info&) { }
    virtual void visit(dogen::cpp::formattables::primitive_info&) const { }
    virtual void visit(dogen::cpp::formattables::primitive_info&) { }
    /**@}*/
};

inline formattable_visitor::~formattable_visitor() noexcept { }

} } }

#endif

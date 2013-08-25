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
#ifndef DOGEN_OM_TYPES_CPP_FEATURE_VISITOR_HPP
#define DOGEN_OM_TYPES_CPP_FEATURE_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/om/types/cpp_argument_fwd.hpp"
#include "dogen/om/types/cpp_class_fwd.hpp"
#include "dogen/om/types/cpp_enumeration_fwd.hpp"
#include "dogen/om/types/cpp_function_fwd.hpp"
#include "dogen/om/types/cpp_header_guard_fwd.hpp"
#include "dogen/om/types/cpp_ifdef_fwd.hpp"
#include "dogen/om/types/cpp_include_directive_fwd.hpp"
#include "dogen/om/types/cpp_member_function_fwd.hpp"
#include "dogen/om/types/cpp_member_variable_fwd.hpp"
#include "dogen/om/types/cpp_namespace_fwd.hpp"
#include "dogen/om/types/cpp_pragma_fwd.hpp"
#include "dogen/om/types/cpp_typedef_fwd.hpp"
#include "dogen/om/types/cpp_variable_fwd.hpp"

namespace dogen {
namespace om {

class cpp_feature_visitor {
public:
    virtual ~cpp_feature_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::om::cpp_namespace
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_namespace&) const { }
    virtual void visit(const dogen::om::cpp_namespace&) { }
    virtual void visit(dogen::om::cpp_namespace&) const { }
    virtual void visit(dogen::om::cpp_namespace&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_class
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_class&) const { }
    virtual void visit(const dogen::om::cpp_class&) { }
    virtual void visit(dogen::om::cpp_class&) const { }
    virtual void visit(dogen::om::cpp_class&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_member_function
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_member_function&) const { }
    virtual void visit(const dogen::om::cpp_member_function&) { }
    virtual void visit(dogen::om::cpp_member_function&) const { }
    virtual void visit(dogen::om::cpp_member_function&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_function
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_function&) const { }
    virtual void visit(const dogen::om::cpp_function&) { }
    virtual void visit(dogen::om::cpp_function&) const { }
    virtual void visit(dogen::om::cpp_function&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_enumeration
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_enumeration&) const { }
    virtual void visit(const dogen::om::cpp_enumeration&) { }
    virtual void visit(dogen::om::cpp_enumeration&) const { }
    virtual void visit(dogen::om::cpp_enumeration&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_member_variable
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_member_variable&) const { }
    virtual void visit(const dogen::om::cpp_member_variable&) { }
    virtual void visit(dogen::om::cpp_member_variable&) const { }
    virtual void visit(dogen::om::cpp_member_variable&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_variable
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_variable&) const { }
    virtual void visit(const dogen::om::cpp_variable&) { }
    virtual void visit(dogen::om::cpp_variable&) const { }
    virtual void visit(dogen::om::cpp_variable&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_argument
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_argument&) const { }
    virtual void visit(const dogen::om::cpp_argument&) { }
    virtual void visit(dogen::om::cpp_argument&) const { }
    virtual void visit(dogen::om::cpp_argument&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_header_guard
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_header_guard&) const { }
    virtual void visit(const dogen::om::cpp_header_guard&) { }
    virtual void visit(dogen::om::cpp_header_guard&) const { }
    virtual void visit(dogen::om::cpp_header_guard&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_include_directive
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_include_directive&) const { }
    virtual void visit(const dogen::om::cpp_include_directive&) { }
    virtual void visit(dogen::om::cpp_include_directive&) const { }
    virtual void visit(dogen::om::cpp_include_directive&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_ifdef
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_ifdef&) const { }
    virtual void visit(const dogen::om::cpp_ifdef&) { }
    virtual void visit(dogen::om::cpp_ifdef&) const { }
    virtual void visit(dogen::om::cpp_ifdef&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_typedef
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_typedef&) const { }
    virtual void visit(const dogen::om::cpp_typedef&) { }
    virtual void visit(dogen::om::cpp_typedef&) const { }
    virtual void visit(dogen::om::cpp_typedef&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::om::cpp_pragma
     */
    /**@{*/
    virtual void visit(const dogen::om::cpp_pragma&) const { }
    virtual void visit(const dogen::om::cpp_pragma&) { }
    virtual void visit(dogen::om::cpp_pragma&) const { }
    virtual void visit(dogen::om::cpp_pragma&) { }
    /**@}*/
};

inline cpp_feature_visitor::~cpp_feature_visitor() noexcept { }

} }

#endif

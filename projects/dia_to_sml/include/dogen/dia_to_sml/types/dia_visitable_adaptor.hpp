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
#ifndef DOGEN_DIA_TO_SML_TYPES_DIA_VISITABLE_ADAPTOR_HPP
#define DOGEN_DIA_TO_SML_TYPES_DIA_VISITABLE_ADAPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dia/types/object.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/dia/types/composite.hpp"
#include "dogen/dia_to_sml/types/object_types.hpp"
#include "dogen/dia_to_sml/types/stereotypes.hpp"
#include "dogen/dia_to_sml/types/dia_visitor.hpp"

namespace dogen {
namespace dia_to_sml {

class dia_visitable_adaptor {
public:
    dia_visitable_adaptor() = default;
    dia_visitable_adaptor(const dia_visitable_adaptor&) = default;
    ~dia_visitable_adaptor() = default;
    dia_visitable_adaptor(dia_visitable_adaptor&&) = default;
    dia_visitable_adaptor& operator=(const dia_visitable_adaptor&) = default;

private:
    /**
     * @brief Parses the dia attribute as a string, returning its value.
     */
    std::string parse_string_attribute(const dia::attribute& a) const;

    /**
     * @brief Given a string with a dia object type, returns the
     * appropriate enum.
     */
    object_types parse_object_type(const std::string& ot) const;

    /**
     * @brief Given a string with a dia stereotype, returns the
     * appropriate enum.
     */
    stereotypes parse_stereotype(const std::string& st) const;

public:
    /**
     * @brief Visits a dia object.
     */
    /**@{*/
    void accept(const dia::object& o, const dia_visitor& v);
    void accept(const dia::object& o, dia_visitor& v);
    /**@}*/

    /**
     * @brief Visits a dia composite attribute.
     */
    /**@{*/
    void accept(const dia::composite& c, const dia_visitor& v);
    void accept(const dia::composite& c, dia_visitor& v);
    /**@}*/
};

} }

#endif

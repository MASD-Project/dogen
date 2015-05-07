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
#ifndef DOGEN_CPP_TYPES_EXPANSION_INCLUSION_DEPENDENCIES_ASSISTANT_HPP
#define DOGEN_CPP_TYPES_EXPANSION_INCLUSION_DEPENDENCIES_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/cpp/types/expansion/inclusion_directives_repository.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

class inclusion_dependencies_assistant {
public:
    inclusion_dependencies_assistant(const inclusion_directives_repository& rp,
        const dynamic::schema::object& o);

public:
    /**
     * @brief Returns true if the io facet is enabled.
     */
    bool is_io_enabled() const;

    /**
     * @brief Returns true if integrated io is enabled against the
     * supplied formatter name.
     */
    bool is_integrated_io_enabled(const std::string& formatter_name) const;

    /**
     * @brief Returns true if the serialisation facet is enabled.
     */
    bool is_serialization_enabled() const;

    /**
     * @brief Returns the inclusion directive for the supplied qname's
     * serialization forward declaration.
     */
    std::string select_serialization_forward_declaration_inclusion_directive(
        const sml::qname& qn) const;

    /**
     * @brief Returns the inclusion directive for the supplied qname's
     * types forward declaration.
     */
    std::string select_types_forward_declaration_inclusion_directive(
        sml::qname& qn) const;

    /**
     * @brief Returns all inclusion directives for the supplied qnames
     * types forward declaration.
     */
    std::list<std::string>
    select_types_forward_declaration_inclusion_directives(
        const std::list<sml::qname>& qn) const;

    /**
     * @brief Returns the inclusion directive for the supplied qname's
     * types class header.
     */
    std::string select_types_class_header_inclusion_directive(
        const sml::qname& qn) const;

    /**
     * @brief Returns all inclusion directives for the supplied qnames
     * types forward declaration.
     */
    std::list<std::string> select_types_class_header_inclusion_directives(
        const std::list<const sml::qname>& qn) const;

private:
    const inclusion_directives_repository& repository_;
    const dynamic::schema::object& object_;
};

} } }

#endif

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
#ifndef DOGEN_CODEC_TYPES_HELPERS_BUILDER_HPP
#define DOGEN_CODEC_TYPES_HELPERS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.codec/types/entities/object.hpp"
#include "dogen.codec/types/entities/model.hpp"

namespace dogen::codec::helpers {

/**
 * @brief Builds a codec model from objects.
 *
 * Expects the objects to have been supplied in dependency order.
 */
class builder final {
private:
    /*
     * @brief Responsible for tracking the qualified name of the
     * element for elements corresponding to Dia's UML large package,
     * as well as an iterator to the element itself in the model.
     */
    struct uml_large_package_properties {
        std::string name;
        std::list<codec::entities::element>::iterator element;
    };

public:
    explicit builder(
        const std::unordered_map<std::string, std::list<std::string>>&
        parent_id_to_child_ids);

private:
    /**
     * @brief Updates the parenting information for the given object
     * 1identified by the dia ID.
     */
    void update_parentage(const std::string& id, const std::string& n);

    /**
     * @brief Returns the list of names of parents for a given dia
     * object id. If none exist, the list is empty.
     */
    const std::list<std::string>&
    parents_for_object(const std::string& id) const;

    /**
     * @brief Returns the qualified name of the containing object, or
     * an empty string.
     */
    std::string contained_by(const std::string& id) const;

private:
    /**
     * @brief Handles the processing of UML large packages.
     */
    void handle_uml_large_package(const entities::object& o,
        const std::string& n);

    /**
     * @brief Handles the processing of UML notes.
     */
    void handle_uml_note(const entities::object& o);

public:
    /**
     * @brief Adds a processed object to the builder.
     */
    void add(const entities::object& o);

    /**
     * @brief Generates the external model.
     */
    codec::entities::model build();

private:
    const std::unordered_map<std::string, std::list<std::string>>&
    parent_id_to_child_ids_;
    std::unordered_map<std::string, uml_large_package_properties>
    id_to_uml_large_package_properties_;
    std::unordered_map<std::string, std::list<std::string>>
    child_id_to_parent_names_;
    codec::entities::model model_;
};

}

#endif

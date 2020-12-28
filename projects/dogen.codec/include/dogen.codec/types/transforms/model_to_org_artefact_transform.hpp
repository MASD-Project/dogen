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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_MODEL_TO_ORG_ARTEFACT_TRANSFORM_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_MODEL_TO_ORG_ARTEFACT_TRANSFORM_HPP

#include "dogen.org/types/entities/drawer_content.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <iosfwd>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.org/types/entities/document.hpp"
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.codec/types/entities/attribute.hpp"
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/entities/artefact.hpp"
#include "dogen.codec/types/transforms/context.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Processes the artefact as if encoded as a org-mode document,
 * converting it into an instance of the codec model.
 */
class model_to_org_artefact_transform final {
private:
    /**
     * @brief Creates a KVP content for a drawer based on supplied
     * inputs.
     */
    static org::entities::drawer_content to_drawer_content(
        const std::string& key, const std::string& value);

    /**
     * @brief Converts different kinds of codec elements into the
     * contents of a property drawer.
     *
     * @pre Drawer is already setup externally.
     */
    /**@{*/
    static void add_to_property_drawer(
        const std::list<identification::entities::stereotype>& sts,
        org::entities::drawer& d);
    static void add_to_property_drawer(const std::list<std::string>& parents,
        org::entities::drawer& d);
    static void add_to_property_drawer(const entities::element& e,
        org::entities::drawer& d);
    static void add_to_property_drawer(
        const std::list<identification::entities::tagged_value>& tvs,
        org::entities::drawer& d);
    /**@}*/

    /**
     * @brief Creates a tag for the element type.
     */
    static org::entities::tag to_tag(const entities::element& e);

    /**
     * @brief Creates an org-mode headline representing the attribute.
     */
    static org::entities::headline to_headline(const unsigned int level,
        const entities::attribute& attr);

    /**
     * @brief Creates an org-mode headline representing the element.
     */
    static org::entities::headline to_headline(const unsigned int level,
        const entities::element& e);

    /**
     * @brief Walks up the codec model, from parent to children,
     * recursively and generates org mode headlines for each one.
     */
    static std::list<org::entities::headline>
    walk_parent_to_child(const unsigned int level,
    const std::string& id, const std::unordered_map<std::string,
    std::list<entities::element>>& parent_to_child_map);


    /**
     * @brief Creates an org mode document from a codec model.
     */
    static org::entities::document to_document(const codec::entities::model& m);

public:
    static entities::artefact
    apply(const transforms::context& ctx, const boost::filesystem::path& p,
        const entities::model& m);
};

}

#endif

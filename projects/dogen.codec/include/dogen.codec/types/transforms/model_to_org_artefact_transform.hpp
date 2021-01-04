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

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <iosfwd>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.org/types/entities/block.hpp"
#include "dogen.org/types/entities/block_type.hpp"
#include "dogen.org/types/entities/document.hpp"
#include "dogen.org/types/entities/drawer_content.hpp"
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
    struct key_value_pairs {
        std::size_t max_key;
        std::size_t max_value;
        std::list<std::pair<std::string, std::string>> contents;
        key_value_pairs() : max_key(), max_value() {}
    };

    /**
     * @brief Adds key value pairs to the KVP collection.
     */
    /**@{*/
    static void add_kvp(const std::string& key, const std::string& value,
        key_value_pairs& kvps);
    static void add_kvp(
        const std::list<identification::entities::stereotype>& sts,
        key_value_pairs& kvps);
    static void add_kvp(const std::list<std::string>& parents,
        key_value_pairs& kvps);
    static void add_kvp(const entities::element& e,
        key_value_pairs& kvps);
    static void add_kvp(
        const std::list<identification::entities::tagged_value>& tvs,
        key_value_pairs& kvps);
    /**@}*/

    /**
     * @brief Converts the KVPs to a property drawer.
     */
    static org::entities::drawer
    to_property_drawer(const key_value_pairs& kvps);

private:
    /**
     * @brief Converts the identifier to a headline title.
     */
    static std::string identifier_to_headline_title(
        const std::string& identifier);

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
     * @brief Creates an org mode block.
     */
    /**@{*/
    static org::entities::block to_block(const std::string& content,
        const org::entities::block_type bt, const std::string& parameter);
    static org::entities::block to_block(const std::string& content,
        const org::entities::block_type bt);
    /**@}*/

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

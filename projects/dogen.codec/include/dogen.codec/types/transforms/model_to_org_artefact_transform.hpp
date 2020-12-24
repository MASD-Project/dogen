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
    static std::string make_headline(const unsigned int level,
        const std::string& title, const std::string& tag);

private:
    static void insert_tagged_values(std::ostream& s,
        const std::list<identification::entities::tagged_value>& tvs);
    static void insert_stereotypes(std::ostream& s,
        const std::list<identification::entities::stereotype>& sts);
    static void insert_parents(std::ostream& s,
        const std::list<std::string>& parents);
    static void insert_attribute(std::ostream& s,
        const unsigned int level, const entities::attribute& a);
    static void insert_element(std::ostream& s,
        const unsigned int level, const entities::element& e);
    static void walk_parent_to_child(std::ostream& s, const unsigned int level,
        const std::string& id, const std::unordered_map<std::string,
        std::list<entities::element>>& parent_to_child_map);
    static std::string to_string(const codec::entities::model& m);

public:
    static entities::artefact
    apply(const transforms::context& ctx, const boost::filesystem::path& p,
        const entities::model& m);
};

}

#endif

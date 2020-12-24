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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_JSON_ARTEFACT_TO_MODEL_TRANSFORM_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_JSON_ARTEFACT_TO_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen.identification/types/entities/stereotype.hpp"
#include "dogen.identification/types/entities/tagged_value.hpp"
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.codec/types/entities/attribute.hpp"
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/entities/artefact.hpp"
#include "dogen.codec/types/transforms/context.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Processes the artefact as if encoded using JSON, converting
 * it into an instance of the codec model.
 */
class json_artefact_to_model_transform final {
private:
    /**
     * @brief Reads the stereotypes, if any exists.
     */
    static std::list<identification::entities::stereotype>
    read_stereotypes(const boost::property_tree::ptree& pt);

    /**
     * @brief Reads the parents, if any exists.
     */
    static std::list<std::string>
    read_parents(const boost::property_tree::ptree& pt);

    /**
     * @brief Reads the documentation, if any exists.
     */
    static std::string
    read_documentation(const boost::property_tree::ptree& pt);

    /**
     * @brief Reads the tagged values, if any exists.
     */
    static std::list<identification::entities::tagged_value>
    read_tagged_values(const boost::property_tree::ptree& pt);

private:
    /**
     * @brief Reads the attributes, if any.
     */
    static codec::entities::attribute
    read_attribute(const boost::property_tree::ptree& pt);

    /**
     * @brief Reads an element according to its meta-type by
     * dispatching to the correct read functions.
     */
    static codec::entities::element
    read_element(const boost::property_tree::ptree& pt, const std::string& id);

    /**
     * @brief Reads the entire stream as a property tree.
     */
    static codec::entities::model read_stream(std::istream& s);

public:
    static entities::model
    apply(const transforms::context& ctx, const entities::artefact& a);
};

}

#endif

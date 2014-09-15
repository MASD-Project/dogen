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
#ifndef DOGEN_SML_TYPES_JSON_HYDRATOR_HPP
#define DOGEN_SML_TYPES_JSON_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/property_tree/ptree.hpp>
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Reads SML models from a well-defined JSON representation.
 */
class json_hydrator {
public:
    json_hydrator() = default;
    json_hydrator(const json_hydrator&) = default;
    json_hydrator(json_hydrator&&) = default;
    ~json_hydrator() noexcept = default;

private:
    /**
     * @brief Returns the model name for all qnames other than the
     * model itself.
     *
     * This hack is required purely for the hardware model, which has
     * no model name for types, etc.
     */
    std::string model_name(const model& m) const;

    /**
     * @brief Reads a module path from the property tree and uses it
     * to populate the qname.
     *
     * If the model does not contain all modules implied by the module
     * path, it adds them to the model.
     */
    void read_module_path(const boost::property_tree::ptree& pt, model& m,
        qname& qn) const;

    /**
     * @brief Reads all meta-data tags from the property tree, and
     * tags the Taggable type with them.
     */
    void read_tags(const boost::property_tree::ptree& source,
        boost::property_tree::ptree& destination) const;

    /**
     * @brief Reads an SML type from the property tree.
     */
    void read_type(const boost::property_tree::ptree& pt, model& m) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    model read_stream(std::istream& s) const;

private:
    /**
     * @brief Perform all of the adjustments required to the model
     * such as generating inferred modules, etc.
     */
    void post_process(model& m) const;

public:
    /**
     * @brief Hydrates the model from the JSON stream.
     */
    model hydrate(std::istream& s) const;
};

} }

#endif

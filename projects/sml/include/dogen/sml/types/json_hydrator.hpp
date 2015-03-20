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
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/workflow.hpp"
#include "dogen/dynamic/schema/types/scope_types.hpp"
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Reads SML models from a well-defined JSON representation.
 */
class json_hydrator {
public:
    json_hydrator(const json_hydrator&) = default;
    json_hydrator(json_hydrator&&) = default;
    ~json_hydrator() noexcept = default;

public:
    explicit json_hydrator(const dynamic::schema::workflow& w);

private:
    /**
     * @brief Returns the generation type for the model, depending on
     * whether it is a target model or not.
     */
    generation_types generation_type(const bool is_target) const;

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
     * @brief Creates the dynamic object by reading meta-data from the
     * property tree.
     */
    dynamic::schema::object
    create_dynamic_extensions(const boost::property_tree::ptree& pt,
        const dynamic::schema::scope_types st) const;

    /**
     * @brief Reads an SML element from the property tree.
     */
    void read_element(const boost::property_tree::ptree& pt, model& m) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    model read_stream(std::istream& s, const bool is_target) const;

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

    /**
     * @brief Opens up the file at path and then hydrates the model
     * from the JSON stream.
     */
    model hydrate(const boost::filesystem::path& p) const;

private:
    const dynamic::schema::workflow schema_workflow_;
};

} }

#endif

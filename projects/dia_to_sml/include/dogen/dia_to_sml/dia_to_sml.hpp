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
#ifndef DOGEN_DIA_TO_SML_DIA_TO_SML_HPP
#define DOGEN_DIA_TO_SML_DIA_TO_SML_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/dia/types/diagram.hpp"
#include "dogen/sml/types/package.hpp"
#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/dia/types/object.hpp"
#include "dogen/dia_to_sml/dia_object_to_sml_pod.hpp"
#include "dogen/dia_to_sml/dia_object_to_sml_package.hpp"
#include "dogen/dia_to_sml/dia_object_to_sml_enumeration.hpp"
#include "dogen/dia_to_sml/dia_object_to_sml_exception.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Transforms a Dia diagram from its object model into SML.
 */
class dia_to_sml {
public:
    dia_to_sml() = delete;
    dia_to_sml& operator=(const dia_to_sml&) = delete;
    dia_to_sml(const dia_to_sml&) = delete;
    dia_to_sml(dia_to_sml&&) = default;

public:
    /**
     * @brief Initialises the transformer
     *
     * @param diagram source of the transformation
     * @param model_name name of the model represented by the diagram
     * @param external_package_path external packages which contain the
     * model to generate
     * @param is_target true if this model is the code generation
     * target, false otherwise.
     * @param verbose output debugging information for troubleshooting
     */
    dia_to_sml(const dia::diagram& diagram, const std::string& model_name,
        const std::string& external_package_path, bool is_target, bool verbose);

private:
    /**
     * @brief Populates the internal data structures with Dia objects.
     *
     * Creates a directed acyclic graph of dependencies between Dia
     * objects, and separates all the relationships from the rest for
     * second-pass processing.
     */
    void setup_data_structures(const std::vector<dia::object>& objects);

private:
    bool is_ignorable_object(const dia::object& o);

public:
    /**
     * @brief Execute the transformation from a Dia diagram into a SML model.
     */
    sml::model transform();

private:
    const dia::diagram diagram_;
    const std::string model_name_;
    const std::list<std::string> external_package_path_;
    const bool is_target_;
    const bool verbose_;
    std::unordered_map<std::string, sml::package> packages_;
    dia_object_to_sml_package package_transformer_;
    dia_object_to_sml_pod pod_transformer_;
    dia_object_to_sml_enumeration enumeration_transformer_;
    dia_object_to_sml_exception exception_transformer_;
};

} }

#endif

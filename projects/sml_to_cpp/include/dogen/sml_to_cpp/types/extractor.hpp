/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2013 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_SML_TO_CPP_TYPES_EXTRACTOR_HPP
#define DOGEN_SML_TO_CPP_TYPES_EXTRACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/concept.hpp"
#include "dogen/sml_to_cpp/types/boost_model_helper.hpp"
#include "dogen/sml_to_cpp/types/std_model_helper.hpp"
#include "dogen/sml_to_cpp/types/relationships.hpp"

namespace dogen {
namespace sml_to_cpp {

class extractor {
public:
    extractor() = delete;
    extractor(const extractor&) = default;
    ~extractor() = default;
    extractor(extractor&&) = default;
    extractor& operator=(const extractor&) = delete;

public:
    typedef const std::unordered_map<
    sml::qname,
    boost::shared_ptr<sml::object>
    > object_map;
    typedef const std::unordered_map<sml::qname, sml::concept> concept_map;

public:
    explicit extractor(const sml::model& m) : model_(m), boost_(), std_() { }

private:
    /**
     * @brief Collects all the properties associated with the refined
     * concepts.
     */
    void properties_for_concept(const sml::object& ao,
        std::list<sml::property>& properties) const;

    /**
     * @brief Iterates through the nested qname recursively, picking
     * up dependencies as it goes along.
     */
    void recurse_nested_qnames(const sml::nested_qname& nqn,
        relationships& rel, bool& is_pointer) const;

public:
    /**
     * @brief Flattens the given object into all qnames it is related
     * to, except itself.
     *
     * The qnames include all types used by the properties of the
     * object, as well as its parent, if any.
     */
    relationships
    extract_dependency_graph(const sml::object& ao) const;

    /**
     * @brief Flattens the given qname into a object inheritance
     * graph, with the qname as the root.
     *
     * The qnames include all descendants of the originally supplied
     * type.
     */
    relationships extract_inheritance_graph(const sml::qname& qn) const;

private:
    const sml::model& model_;
    const boost_model_helper boost_;
    const std_model_helper std_;
};

} }

#endif

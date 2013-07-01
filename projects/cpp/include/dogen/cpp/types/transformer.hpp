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
#ifndef DOGEN_CPP_TYPES_TRANSFORMER_HPP
#define DOGEN_CPP_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <tuple>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/nested_type_info.hpp"
#include "dogen/cpp/types/registrar_info.hpp"
#include "dogen/cpp/types/visitor_info.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Transforms an SML type into its corresponding CPP type.
 */
class transformer {
public:
    transformer() = delete;
    transformer(const transformer&) = default;
    ~transformer() = default;
    transformer& operator=(const transformer&) = delete;
    transformer(transformer&& rhs) = default;

public:
    explicit transformer(const sml::model& m);

public:
    typedef boost::optional<class_info> optional_class_info;

private:
    /**
     * @brief Collects all the properties associated with a concept,
     * and any otheer concepts it may refine.
     */
    void properties_for_concept(const sml::qname& qn,
        std::list<sml::property>& properties,
        std::unordered_set<sml::qname>& processed_qnames) const;

private:
    /**
     * @brief Converts an SML qname into a C++ qualified name.
     */
    std::string
    transform_into_qualified_name(const sml::qname& qn) const;

    /**
     * @brief Flattens all the SML namespace information stored in qname
     * into a list of strings with C++ namespaces.
     */
    std::list<std::string>
    transform_into_namespace_list(const sml::qname& qn) const;

    /**
     * @brief Transforms an SML property to an enumerator info.
     */
    enumerator_info transform_enumerator(const sml::enumerator& e) const;

    /**
     * @brief Transforms the SML nested qname into a nested type info.
     */
    void transform(const sml::nested_qname& nqn,
        cpp::nested_type_info& nti, std::string& complete_name,
        bool& requires_stream_manipulators) const;

    /**
     * @brief Transforms an SML property into a property info.
     *
     * The four Boolean values on the tuple work as follows:
     *
     * @li position 1: if true, the property has a top-level primitive
     * type.
     *
     * @li position 2: if true, the property requires stream
     * manipulators.
     *
     * @li position 3: if true, the property invalidates the compiler
     * generated move constructor.
     *
     * @li position 4: if true, the property invalidates the compiler
     * generated default constructor.
     */
    std::tuple<property_info, bool, bool, bool, bool>
    transform(const sml::property p, const bool is_immutable,
        const bool is_fluent) const;

public:
    /**
     * @brief Transforms a SML value containing an enumeration into an
     * enumeration info.
     */
    enum_info transform_enumeration(const sml::enumeration& e) const;

    /**
     * @brief Transforms a SML value containing an exception into an
     * exception info.
     */
    exception_info transform_exception(const sml::value_object& e) const;

    /**
     * @brief Transforms a SML module into a namespace info.
     */
    namespace_info transform(const sml::module& p) const;

    /**
     * @brief Transforms a SML model into a namespace info.
     *
     * @todo Create an attribute of type module in model.
     */
    namespace_info transform_model_into_namespace() const;

    /**
     * @brief Transforms a SML model into a registrar info.
     */
    registrar_info transform_model_into_registrar() const;

    /**
     * @brief Transform a SML pod into a class info.
     *
     * @param ao pod to transform.
     * @param pci if the pod has a parent, its class info.
     * @param opci if the parent pod was not the root parent, the root parent.
     */
    class_info transform(const sml::abstract_object& ao,
        const optional_class_info pci = optional_class_info(),
        const optional_class_info opci = optional_class_info()) const;

    /**
     * @brief Transform a SML object representing a visitor into a
     * visitor info.
     *
     * @pre value object must have a visitor type.
     */
    visitor_info transform_into_visitor(const sml::value_object& ao) const;

private:
    const sml::model& model_;
};

} }

#endif

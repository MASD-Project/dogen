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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_TRANSFORMER_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <tuple>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/nested_name.hpp"
#include "dogen/cpp/types/formattables/entity.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp/types/formattables/enum_info.hpp"
#include "dogen/cpp/types/formattables/concept_info.hpp"
#include "dogen/cpp/types/formattables/visitor_info.hpp"
#include "dogen/cpp/types/formattables/property_info.hpp"
#include "dogen/cpp/types/formattables/exception_info.hpp"
#include "dogen/cpp/types/formattables/namespace_info.hpp"
#include "dogen/cpp/types/formattables/primitive_info.hpp"
#include "dogen/cpp/types/formattables/forward_declarations_info.hpp"
#include "dogen/cpp/types/settings/opaque_settings_builder.hpp"
#include "dogen/cpp/types/settings/bundle_repository.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Transforms an Yarn type into its corresponding C++ type.
 */
class transformer {
public:
    transformer(const settings::opaque_settings_builder& osb,
        const settings::bundle_repository& brp,
        const formatter_properties_repository& frp,
        const yarn::intermediate_model& m);

private:
    /**
     * @brief Populates all properties at the formattables base class level.
     */
    void
    populate_formattable_properties(const yarn::name& n, formattable& f) const;

    /**
     * @brief Populates all properties at the entity base class level.
     */
    void populate_entity_properties(const yarn::name& n,
        const std::string& documentation, entity& e) const;

private:
    /**
     * @brief Transforms the Yarn nested name into a nested type info.
     */
    void to_nested_type_info(const yarn::nested_name& nn,
        nested_type_info& nti, std::string& complete_name,
        bool& requires_stream_manipulators) const;

    /**
     * @brief Transforms an Yarn property into a property info.
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
    std::tuple<property_info, bool, bool, bool>
    to_property_info(const yarn::property p, const bool is_immutable,
        const bool is_fluent) const;

    /**
     * @brief Transforms an Yarn property to an enumerator info.
     */
    enumerator_info to_enumerator_info(const yarn::enumerator& e) const;

    /**
     * @brief Transforms a Yarn value containing an enumeration into an
     * enumeration info.
     */
    std::shared_ptr<enum_info> to_enum_info(const yarn::enumeration& e) const;

    /**
     * @brief Transforms a Yarn module into a namespace info.
     */
    std::shared_ptr<namespace_info>
    to_namespace_info(const yarn::module& m) const;

    /**
     * @brief Transforms a Yarn value containing an exception into an
     * exception info.
     */
    std::shared_ptr<exception_info>
    to_exception_info(const yarn::object& o) const;

    /**
     * @brief Transform a Yarn object into a class info.
     *
     * @param ao object to transform.
     */
    std::shared_ptr<class_info> to_class_info(const yarn::object& o) const;

    /**
     * @brief Transform a Yarn object representing a visitor into a
     * visitor info.
     *
     * @pre value object must have a visitor type.
     */
    std::shared_ptr<visitor_info> to_visitor_info(const yarn::object& o) const;

    /**
     * @brief Creates a forward declaration for the object.
     */
    std::shared_ptr<forward_declarations_info>
    to_forward_declarations_info(const yarn::object& o) const;

    /**
     * @brief Creates a forward declaration for the enumeration.
     */
    std::shared_ptr<forward_declarations_info>
    to_forward_declarations_info(const yarn::enumeration& e) const;

public:
    /**
     * @brief Transform an Yarn enumeration into a C++ entity.
     */
    std::forward_list<std::shared_ptr<formattable> >
    transform(const yarn::enumeration& e) const;

    /**
     * @brief Transform an Yarn module into a C++ entity.
     */
    std::forward_list<std::shared_ptr<formattable> >
    transform(const yarn::module& m) const;

    /**
     * @brief Transform an Yarn concept into a C++ entity.
     */
    std::forward_list<std::shared_ptr<formattable> >
    transform(const yarn::concept& c) const;

    /**
     * @brief Transform an Yarn primitive into a C++ entity.
     */
    std::forward_list<std::shared_ptr<formattable> >
    transform(const yarn::primitive& p) const;

    /**
     * @brief Transform an Yarn object into a C++ entity.
     */
    std::forward_list<std::shared_ptr<formattable> >
    transform(const yarn::object& o) const;

private:
    const settings::opaque_settings_builder& opaque_settings_builder_;
    const settings::bundle_repository& bundle_repository_;
    const formatter_properties_repository& formatter_properties_repository_;
    const yarn::intermediate_model& model_;
};

} } }

#endif

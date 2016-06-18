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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_TRANSFORMER_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_TRANSFORMER_HPP

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
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/quilt.cpp/types/properties/entity.hpp"
#include "dogen/quilt.cpp/types/properties/formattable.hpp"
#include "dogen/quilt.cpp/types/properties/class_info.hpp"
#include "dogen/quilt.cpp/types/properties/property_info.hpp"
#include "dogen/quilt.cpp/types/properties/forward_declarations_info.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

/**
 * @brief Transforms an Yarn type into its corresponding C++ type.
 */
class transformer {
public:
    explicit transformer(const yarn::model& m);

private:
    /**
     * @brief Populates all properties at the properties base class level.
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
    void to_nested_type_info(const yarn::name_tree& nt,
        nested_type_info& nti, std::string& complete_name,
        bool& requires_stream_manipulators) const;

    /**
     * @brief Transforms an Yarn attribute into a property info.
     *
     * The four Boolean values on the tuple work as follows:
     *
     * @li position 1: if true, the attribute has a top-level primitive
     * type.
     *
     * @li position 2: if true, the attribute requires stream
     * manipulators.
     *
     * @li position 3: if true, the attribute invalidates the compiler
     * generated move constructor.
     *
     * @li position 4: if true, the attribute invalidates the compiler
     * generated default constructor.
     */
    std::tuple<property_info, bool, bool, bool>
    to_property_info(const yarn::attribute a, const bool is_immutable,
        const bool is_fluent) const;

    /**
     * @brief Transform a Yarn object into a class info.
     *
     * @param ao object to transform.
     */
    std::shared_ptr<class_info> to_class_info(const yarn::object& o) const;

    /**
     * @brief Creates a forward declaration for the object.
     */
    std::shared_ptr<forward_declarations_info>
    to_forward_declarations_info(const yarn::object& o) const;

    /**
     * @brief Creates a forward declaration for the exception.
     */
    std::shared_ptr<forward_declarations_info>
    to_forward_declarations_info(const yarn::exception& e) const;

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
     * @brief Transform an Yarn object into a C++ entity.
     */
    std::forward_list<std::shared_ptr<formattable> >
    transform(const yarn::object& o) const;

    /**
     * @brief Transform an Yarn exception into a C++ entity.
     */
    std::forward_list<std::shared_ptr<formattable> >
    transform(const yarn::exception& e) const;

private:
    const yarn::model& model_;
};

} } } }

#endif

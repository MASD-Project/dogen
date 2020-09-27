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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_TYPES_TRAITS_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_TYPES_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen::text::cpp::transforms::types {

struct traits {
    /**
     * @brief Name of this facet.
     */
    static std::string facet_qn();
    static std::string facet_sn();

    /**
     * @brief Name of the canonical archetype for this facet.
     */
    static std::string canonical_archetype();

    /**
     * @brief Name of the class header archetype.
     */
    static std::string class_header_archetype_qn();
    static std::string class_header_archetype_sn();

    /**
     * @brief Name of the forward declaration's archetype.
     */
    static std::string class_forward_declarations_archetype_qn();
    static std::string class_forward_declarations_archetype_sn();

    /**
     * @brief Name of the archetype for the archetype class header
     * transform.
     */
    static std::string archetype_class_header_transform_archetype_qn();
    static std::string archetype_class_header_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the archetype class header
     * factory.
     */
    static std::string archetype_class_header_factory_archetype_qn();
    static std::string archetype_class_header_factory_archetype_sn();

    /**
     * @brief Name of the archetype for the archetype class
     * implementation transform.
     */
    static std::string archetype_class_implementation_transform_archetype_qn();
    static std::string archetype_class_implementation_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the archetype class
     * implementation factory.
     */
    static std::string archetype_class_implementation_factory_archetype_qn();
    static std::string archetype_class_implementation_factory_archetype_sn();

    /**
     * @brief Name of the archetype for the facet class header
     * transform.
     */
    static std::string facet_class_header_transform_archetype_qn();
    static std::string facet_class_header_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the facet class header
     * factory.
     */
    static std::string facet_class_header_factory_archetype_qn();
    static std::string facet_class_header_factory_archetype_sn();

    /**
     * @brief Name of the archetype for the facet class implementation
     * transform.
     */
    static std::string facet_class_implementation_transform_archetype_qn();
    static std::string facet_class_implementation_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the facet class implementation
     * factory.
     */
    static std::string facet_class_implementation_factory_archetype_qn();
    static std::string facet_class_implementation_factory_archetype_sn();

    /**
     * @brief Name of the archetype for the backend class header
     * transform.
     */
    static std::string backend_class_header_transform_archetype_qn();
    static std::string backend_class_header_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the backend class header
     * factory.
     */
    static std::string backend_class_header_factory_archetype_qn();
    static std::string backend_class_header_factory_archetype_sn();

    /**
     * @brief Name of the archetype for the backend class
     * implementation.
     */
    static std::string backend_class_implementation_transform_archetype_qn();
    static std::string backend_class_implementation_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the backend class
     * implementation factory.
     */
    static std::string backend_class_implementation_factory_archetype_qn();
    static std::string backend_class_implementation_factory_archetype_sn();

    /**
     * @brief Name of the archetype for the class header archetype.
     */
    static std::string part_class_header_transform_archetype_qn();
    static std::string part_class_header_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the class header archetype.
     */
    static std::string part_class_header_factory_archetype_qn();
    static std::string part_class_header_factory_archetype_sn();

    /**
     * @brief Name of the archetype for the class implementation
     * archetype.
     */
    static std::string part_class_implementation_transform_archetype_qn();
    static std::string part_class_implementation_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the class implementation
     * archetype.
     */
    static std::string part_class_implementation_factory_archetype_qn();
    static std::string part_class_implementation_factory_archetype_sn();

    /**
     * @brief Name of the archetype for the class header archetype.
     */
    static std::string archetype_kind_class_header_transform_archetype_qn();
    static std::string archetype_kind_class_header_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the class header archetype.
     */
    static std::string archetype_kind_class_header_factory_archetype_qn();
    static std::string archetype_kind_class_header_factory_archetype_sn();

    /**
     * @brief Name of the archetype for the class implementation
     * archetype.
     */
    static std::string archetype_kind_class_implementation_transform_archetype_qn();
    static std::string archetype_kind_class_implementation_transform_archetype_sn();

    /**
     * @brief Name of the archetype for the class implementation
     * archetype.
     */
    static std::string archetype_kind_class_implementation_factory_archetype_qn();
    static std::string archetype_kind_class_implementation_factory_archetype_sn();

    /**
     * @brief Name of the forward declaration's archetype.
     */
    static std::string visitor_forward_declarations_archetype_qn();
    static std::string visitor_forward_declarations_archetype_sn();

    /**
     * @brief Name of the forward declaration's archetype.
     */
    static std::string primitive_forward_declarations_archetype_qn();
    static std::string primitive_forward_declarations_archetype_sn();

    /**
     * @brief Name of the class implementation archetype.
     */
    static std::string class_implementation_archetype_qn();
    static std::string class_implementation_archetype_sn();

    /**
     * @brief Name of the enumeration header archetype.
     */
    static std::string enum_header_archetype_qn();
    static std::string enum_header_archetype_sn();

    /**
     * @brief Name of the exception header archetype.
     */
    static std::string exception_header_archetype_qn();
    static std::string exception_header_archetype_sn();

    /**
     * @brief Name of the namespace header archetype.
     */
    static std::string namespace_header_archetype_qn();
    static std::string namespace_header_archetype_sn();

    /**
     * @brief Name of the visitor header archetype.
     */
    static std::string visitor_header_archetype_qn();
    static std::string visitor_header_archetype_sn();

    /**
     * @brief Name of the built-in header archetype.
     */
    static std::string builtin_header_archetype_qn();
    static std::string builtin_header_archetype_sn();

    /**
     * @brief Name of the primitive header archetype.
     */
    static std::string primitive_header_archetype_qn();
    static std::string primitive_header_archetype_sn();

    /**
     * @brief Name of the primitive implementation archetype.
     */
    static std::string primitive_implementation_archetype_qn();
    static std::string primitive_implementation_archetype_sn();

    static std::string feature_template_bundle_header_archetype_qn();
    static std::string feature_template_bundle_header_archetype_sn();

    static std::string feature_template_bundle_implementation_archetype_qn();
    static std::string feature_template_bundle_implementation_archetype_sn();

    static std::string feature_bundle_header_archetype_qn();
    static std::string feature_bundle_header_archetype_sn();

    static std::string feature_bundle_implementation_archetype_qn();
    static std::string feature_bundle_implementation_archetype_sn();

    static std::string variability_initializer_header_archetype_qn();
    static std::string variability_initializer_header_archetype_sn();

    static std::string variability_initializer_implementation_archetype_qn();
    static std::string variability_initializer_implementation_archetype_sn();

    /**
     * @brief Name of the entry point.
     */
    static std::string main_archetype_qn();
    static std::string main_archetype_sn();
};

}

#endif

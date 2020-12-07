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
#ifndef DOGEN_TEXT_TYPES_FORMATTERS_ASSISTANT_HPP
#define DOGEN_TEXT_TYPES_FORMATTERS_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include <boost/iostreams/filtering_stream.hpp>
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.text/types/entities/model.hpp"

namespace dogen::text::formatters {

/**
 * @brief Provides a number of formatting utilities.
 */
class assistant final {
public:
    assistant(const text::entities::model& lps,
        const logical::entities::element& e, physical::entities::artefact& a,
        const bool requires_header_guard);

private:
    /**
     * @brief Ensures the required configuration is available and set
     * to reasonable values.
     */
    void validate() const;

public:
    template<typename T>
    static const T&
    as(const logical::entities::element& e) {
        return dynamic_cast<const T&>(e);
    }

public:
    /**
     * @brief Returns the text to use for a given class for the @code
     * final keyword. If non-empty, includes a trailing space.
     */
    std::string make_final_keyword_text(
        const logical::entities::structural::object& o) const;

    /**
     * @brief Returns the override keyword, if supported by the
     * current standard.
     */
    std::string make_override_keyword_text() const;

    /**
     * @brief Returns the noexcept keyword, if supported by the
     * current standard.
     */
    std::string make_noexcept_keyword_text() const;

    /**
     * @brief Returns the by-ref to use given the property.
     */
    static std::string
    make_by_ref_text(const logical::entities::attribute& attr);

    /**
     * @brief Makes the return type of a setter, taking into account
     * fluency.
     */
    static std::string make_setter_return_type(
        const std::string& containing_type_name,
        const logical::entities::attribute& attr);

public:
        /**
     * @brief Obtains the qualified name.
     */
    /**@{*/
    std::string get_qualified_name(
        const identification::entities::logical_name& n) const;
    std::string get_qualified_name(
        const identification::entities::logical_name_tree& nt) const;
    /**@}*/

    /**
     * @brief Obtains the qualified namespace for this name.
     *
     * The qualified namespace contains all modules, but not the
     * element name itself.
     */
    std::string get_qualified_namespace(
        const identification::entities::logical_name& n) const;

    /**
     * @brief Obtains the model name as a string.
     */
    std::string
    get_identifiable_model_name(
        const identification::entities::logical_name& n) const;

    /**
     * @brief Obtains the model name as a set of strings separated by
     * dots.
     */
    std::string
    get_dot_separated_model_name(
        const identification::entities::logical_name& n) const;

    /**
     * @brief Obtains the product name. This is defined to be the
     * first external module, if any exists.
     */
    std::string get_product_name(
        const identification::entities::logical_name& n) const;

public:
    /**
     * @brief If true, the current standard is set to c++ 98.
     */
    bool is_cpp_standard_98() const;

    /**
     * @brief If true, the current standard is set to c++ 17.
     */
    bool is_cpp_standard_17() const;

    /**
     * @brief If true, the current standard supports defaulted
     * functions.
     */
    bool supports_defaulted_functions() const;

    /**
     * @brief If true, the current standard supports defaulted
     * functions.
     */
    bool supports_move_operator() const;

public:
    /**
     * @brief If true, the current element requires nested namespaces.
     */
    bool requires_nested_namespaces() const;

    /**
     * @brief If true, the current element requires a manually
     * implemented default constructor.
     */
    bool requires_manual_default_constructor() const;

    /**
     * @brief If true, the current element requires a manually
     * implemented move constructor.
     */
    bool requires_manual_move_constructor() const;

    /**
     * @brief If true, the current element requires stream
     * manipulators to be setup.
     */
    bool requires_stream_manipulators() const;

private:
    std::ostringstream stream_;
    boost::iostreams::filtering_ostream filtering_stream_;
    const logical::entities::element& element_;
    const text::entities::model& lps_;
    physical::entities::artefact& artefact_;
    const bool requires_header_guard_;
};

}

#endif

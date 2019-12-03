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
#ifndef DOGEN_GENERATION_CPP_TYPES_FORMATTERS_ASSISTANT_HPP
#define DOGEN_GENERATION_CPP_TYPES_FORMATTERS_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include "dogen.archetypes/types/location.hpp"
#include "dogen.extraction/types/meta_model/artefact.hpp"
#include "dogen.generation/types/formatters/scoped_namespace_formatter.hpp"
#include "dogen.generation/types/formatters/scoped_boilerplate_formatter.hpp"
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/name_tree.hpp"
#include "dogen.generation.cpp/types/formatters/context.hpp"
#include "dogen.generation.cpp/types/formattables/helper_properties.hpp"

namespace dogen::generation::cpp::formatters {

/**
 * @brief Provides a number of utilities to formatters.
 */
class assistant final {
public:
    assistant(const context& ctx, const assets::meta_model::element& e,
        const archetypes::location& al,
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
    as(const assets::meta_model::element& e) {
        return dynamic_cast<const T&>(e);
    }

    /**
     * @brief Returns the text to use for a given class for the @code
     * final keyword. If non-empty, includes a trailing space.
     */
    std::string
    make_final_keyword_text(const assets::meta_model::structural::object& o) const;

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
    make_by_ref_text(const assets::meta_model::attribute& attr);

    /**
     * @brief Makes the return type of a setter, taking into account
     * fluency.
     */
    static std::string make_setter_return_type(
        const std::string& containing_type_name,
        const assets::meta_model::attribute& attr);

    /**
     * @brief Obtains the qualified name.
     */
    /**@{*/
    std::string get_qualified_name(const assets::meta_model::name& n) const;
    std::string get_qualified_name(const assets::meta_model::name_tree& nt) const;
    /**@}*/

    /**
     * @brief Obtains the qualified namespace for this name.
     *
     * The qualified namespace contains all modules, but not the
     * element name itself.
     */
    std::string get_qualified_namespace(const assets::meta_model::name& n) const;

    /**
     * @brief Obtains the model name as a string.
     */
    std::string
    get_identifiable_model_name(const assets::meta_model::name& n) const;

    /**
     * @brief Obtains the model name as a set of strings separated by
     * dots.
     */
    std::string
    get_dot_separated_model_name(const assets::meta_model::name& n) const;

    /**
     * @brief Obtains the product name. This is defined to be the
     * first external module, if any exists.
     */
    std::string get_product_name(const assets::meta_model::name& n) const;

private:
    /**
     * @brief
     */
    const formattables::element_properties& obtain_element_properties(
        const std::string& element_id) const;

    /**
     * @brief Obtains the artefact properties for the supplied
     * archetype.
     *
     * @pre Artefact properties must exist for the archetype.
     */
    const formattables::artefact_properties& obtain_artefact_properties(
        const std::string& element_id, const std::string& archetype) const;

    const assets::meta_model::artefact_properties& obtain_new_artefact_properties(
        const assets::meta_model::element& e, const std::string& archetype) const;

    /**
     * @brief Obtains the facet configuration for the facet
     * identified by facet name.
     *
     * @pre Facet configuration must exist for the facet.
     */
    formattables::facet_properties
    obtain_facet_properties(const std::string& facet_name) const;

    /**
     * @brief Returns true if the archetype is enabled, false
     * otherwise.
     */
    bool is_archetype_enabled(const std::string& archetype) const;

    /**
     * @brief Returns true if the facet is enabled, false otherwise.
     */
    bool is_facet_enabled(const std::string& facet) const;

    /**
     * @brief Returns the folder for the current facet.
     */
    std::string get_facet_directory_for_facet(
        const std::string& facet_name) const;

public:
    std::string get_odb_facet_directory() const;

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

public:
    /**
     * @brief returns the c++ namespaces for the name.
     */
    std::list<std::string>
    make_namespaces(const assets::meta_model::name& n,
        const bool detect_model_name = true) const;

 public:
    /**
     * @brief Returns true if serialization is enabled locally.
     */
    bool is_serialization_enabled() const;

    /**
     * @brief Returns true if io is enabled locally.
     */
    bool is_io_enabled() const;

    /**
     * @brief Returns true if io is enabled locally.
     */
    bool is_lexical_cast_enabled() const;

    /**
     * @brief Returns true if odb is enabled globally.
     */
    bool is_odb_facet_enabled() const;

    /**
     * @brief Returns true if tests is enabled globally.
     */
    bool is_tests_enabled() const;

    /**
     * @brief Returns true if hash is enabled locally.
     */
    bool is_hash_enabled() const;

    /**
     * @brief Returns true if test data is enabled globally.
     */
    bool is_test_data_enabled() const;

    /**
     * @brief Returns true if the current formatter belongs to the io
     * facet.
     */
    bool is_io() const;

    /**
     * @brief Returns true if the types facet is required to support
     * streaming or if we are in io facet.
     */
    bool is_streaming_enabled(const formattables::helper_properties& hp) const;

public:
    /**
     * @brief Returns a scoped boilerplate formatter.
     */
    generation::formatters::scoped_boilerplate_formatter
    make_scoped_boilerplate_formatter(const assets::meta_model::element& e);

    /**
     * @brief Returns a scoped namespace formatter.
     */
    generation::formatters::scoped_namespace_formatter
    make_scoped_namespace_formatter(const std::list<std::string>& ns);

    /**
     * @brief Creates the decoration preamble.
     */
    void make_decoration_preamble(const assets::meta_model::element& e);

public:
    /**
     * @brief Adds a top-level comment with doxygen keywords.
     */
    void comment(const std::string& c);

    /**
     * @brief Adds comments for the starting of a method group,
     * including comment blocks.
     */
    void comment_start_method_group(const std::string& documentation,
        const bool add_comment_blocks = true);

    /**
     * @brief Adds comments for the end of a method group, including
     * comment blocks.
     */
    void comment_end_method_group(const std::string& documentation,
        const bool add_comment_blocks = true);

    /**
     * @brief Returns @code c as as an inline comment.
     */
    std::string comment_inline(const std::string& c) const;

private:
    std::list<std::shared_ptr<formatters::helper_formatter_interface>>
    get_helpers(const formattables::helper_properties& hp) const;

    std::string streaming_for_type(const formattables::streaming_properties& sp,
        const std::string& s) const;

public:
    /**
     * @brief Creates any helper methods that may be required for this
     * formatter.
     */
    void add_helper_methods(const std::string& element_id);

    /**
     * @brief Returns the correct streaming invocation for the
     * supplied type.
     */
    /**@{*/
    std::string streaming_for_type(const formattables::helper_descriptor& hd,
        const std::string& s) const;
    std::string streaming_for_type(const assets::meta_model::name& n,
        const std::string& s) const;
    /**@}*/

    /**
     * @brief Returns true if the type can be hashed without requiring a
     * helper method.
     */
    bool requires_hashing_helper_method(
        const assets::meta_model::attribute& attr) const;

public:
    /**
     * @brief Returns the subset of names for which the supplied
     * archetype is enabled.
     */
    std::list<assets::meta_model::name>
    names_with_enabled_archetype(const std::string& archetype,
        const std::list<assets::meta_model::name> names) const;

public:
    const formattables::artefact_properties& artefact_properties() const;
    const assets::meta_model::artefact_properties&
    new_artefact_properties() const;

public:
    /**
     * @brief Returns the stream that is currently being populated.
     */
    std::ostream& stream();

    /**
     * @brief Generates a file with the current contents of the
     * stream.
     */
    extraction::meta_model::artefact make_artefact() const;

private:
    std::ostringstream stream_;
    boost::iostreams::filtering_ostream filtering_stream_;
    const assets::meta_model::element& element_;
    const context& context_;
    formattables::artefact_properties artefact_properties_;
    assets::meta_model::artefact_properties new_artefact_properties_;
    const archetypes::location archetype_location_;
    const bool requires_header_guard_;
};

}

#endif

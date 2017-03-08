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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_ASSISTANT_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_ASSISTANT_HPP

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
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/letter_cases.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_properties.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

/**
 * @brief Provides a number of utilities to formatters.
 */
class assistant final {
public:
    assistant(const context& ctx, const annotations::archetype_location& al,
        const bool requires_header_guard, const std::string& id);

private:
    /**
     * @brief Ensures the required configuration is available and set
     * to reasonable values.
     */
    void validate() const;

public:
    template<typename T>
    static const T&
    as(const std::string& /*archetype*/, const yarn::element& e) {
        return dynamic_cast<const T&>(e);
    }

    /**
     * @brief Returns the text to use for a given class for the @code
     * final keyword. If non-empty, includes a trailing space.
     */
    std::string make_final_keyword_text(const yarn::object& o) const;

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
    static std::string make_by_ref_text(const yarn::attribute& attr);

    /**
     * @brief Makes the return type of a setter, taking into account
     * fluency.
     */
    static std::string make_setter_return_type(
        const std::string& containing_type_name, const yarn::attribute& attr);

    /**
     * @brief Obtains the qualified name.
     */
    /**@{*/
    std::string get_qualified_name(const yarn::name& n) const;
    std::string get_qualified_name(const yarn::name_tree& nt) const;
    /**@}*/

    /**
     * @brief Obtains the model name as a string.
     */
    std::string get_identifiable_model_name(const yarn::name& n) const;

    /**
     * @brief Obtains the product name. This is defined to be the
     * first external module, if any exists.
     */
    std::string get_product_name(const yarn::name& n) const;

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
     * @brief Returns the property as a member variable.
     */
    std::string make_member_variable_name(const yarn::attribute& attr) const;

    /**
     * @brief Returns the property as a getter.
     */
    std::string make_getter_setter_name(const yarn::attribute& attr) const;

    /**
     * @brief returns the c++ namespaces for the name.
     */
    std::list<std::string> make_namespaces(const yarn::name& n) const;

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
     * @brief Returns true if odb is enabled globally.
     */
    bool is_odb_facet_enabled() const;

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
    dogen::formatters::cpp::scoped_boilerplate_formatter
    make_scoped_boilerplate_formatter();

    /**
     * @brief Returns a scoped namespace formatter.
     */
    dogen::formatters::cpp::scoped_namespace_formatter
    make_scoped_namespace_formatter(const std::list<std::string>& ns);

    /**
     * @brief Creates the decoration preamble.
     */
    /**@{*/
    void make_decoration_preamble();
    void make_decoration_preamble(
        const boost::optional<dogen::formatters::decoration_properties> dc);
    /**@}*/

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
    std::string streaming_for_type(const yarn::name& n,
        const std::string& s) const;
    /**@}*/

    /**
     * @brief Returns true if the type can be hashed without requiring a
     * helper method.
     */
    bool requires_hashing_helper_method(const yarn::attribute& attr) const;

public:
    /**
     * @brief Retrieves the ODB pragmas for the element.
     */
    std::list<std::string> get_odb_pragmas() const;

    /**
     * @brief Retrieves the ODB pragmas for a given attribute.
     */
    std::list<std::string> get_odb_pragmas(const std::string& attr_id) const;

    /**
     * @brief Returns the ODB type for the current element.
     */
    std::string get_odb_type() const;

    /**
     * @brief Returns the type of letter casing to use.
     */
    std::string get_letter_case(const yarn::letter_cases lc) const;

public:
    /**
     * @brief Returns the subset of names for which the supplied
     * archetype is enabled.
     */
    std::list<yarn::name>
    names_with_enabled_archetype(const std::string& archetype,
        const std::list<yarn::name> names) const;

public:
    const formattables::artefact_properties& artefact_properties() const;

public:
    /**
     * @brief Returns the stream that is currently being populated.
     */
    std::ostream& stream();

    /**
     * @brief Generates a file with the current contents of the
     * stream.
     */
    dogen::formatters::artefact make_artefact() const;

private:
    std::ostringstream stream_;
    boost::iostreams::filtering_ostream filtering_stream_;
    const std::string element_id_;
    const context& context_;
    formattables::artefact_properties artefact_properties_;
    const annotations::archetype_location archetype_location_;
    const bool requires_header_guard_;
};

} } } }

#endif

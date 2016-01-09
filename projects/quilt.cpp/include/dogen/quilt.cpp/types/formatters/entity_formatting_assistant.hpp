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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_ENTITY_FORMATTING_ASSISTANT_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_ENTITY_FORMATTING_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include "dogen/dynamic/types/ownership_hierarchy.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/quilt.cpp/types/settings/odb_settings.hpp"
#include "dogen/quilt.cpp/types/settings/opaque_settings.hpp"
#include "dogen/quilt.cpp/types/formatters/file_types.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/quilt.cpp/types/formattables/entity.hpp"
#include "dogen/quilt.cpp/types/formattables/class_info.hpp"
#include "dogen/quilt.cpp/types/formattables/property_info.hpp"
#include "dogen/quilt.cpp/types/formatters/nested_type_formatting_assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_assistant.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

/**
 * @brief Provides a number of utilities to formatters that generate
 * files for entities.
 */
class entity_formatting_assistant final : public formatting_assistant {
public:
    ~entity_formatting_assistant() noexcept;

public:
    /**
     * @brief Returns the text to use for a given class for the @code
     * final keyword. If non-empty, includes a trailing space.
     */
    static std::string
    make_final_keyword_text(const formattables::class_info& c);

    /**
     * @brief Returns the by-ref to use given the property.
     */
    static std::string make_by_ref_text(const formattables::property_info& p);

    /**
     * @brief Makes the return type of a setter, taking into account
     * fluency.
     */
    static std::string
    make_setter_return_type(const std::string& containing_type_name,
        const formattables::property_info& p);

public:
    entity_formatting_assistant(const formattables::entity& e,
        const context& ctx, const dynamic::ownership_hierarchy& oh,
        const formatters::file_types ft);

private:
    /**
     * @brief Obtains the formatter settings for the formatter as
     * given by the ownership hierarchy.
     */
    formattables::formatter_properties
    obtain_formatter_properties(const std::string& formatter_name) const;

    /**
     * @brief Returns true if the formatter is enabled, false
     * otherwise.
     */
    bool is_formatter_enabled(const std::string& formatter_name) const;

    /**
     * @brief Returns true if the facet is integrated with the current
     * formatter.
     */
    bool is_facet_integrated(const std::string& facet_name) const;

public:
    /**
     * @brief Returns the property as a member variable.
     */
    std::string make_member_variable_name(
        const formattables::property_info& p) const;

    /**
     * @brief Returns the property as a getter.
     */
    std::string make_getter_setter_name(
        const formattables::property_info& p) const;

public:
    /**
     * @brief Returns true if serialization is enabled.
     */
    bool is_serialization_enabled() const;

    /**
     * @brief Returns true if io is enabled.
     */
    bool is_io_enabled() const;

    /**
     * @brief Returns true if io is integrated with the current
     * formatter.
     */
    bool is_io_integrated() const;

    /**
     * @brief Returns true if hash is enabled.
     */
    bool is_hash_enabled() const;

    /**
     * @brief Returns true if test data is enabled.
     */
    bool is_test_data_enabled() const;

    /**
     * @brief Returns true if the complete constructor is disabled,
     * false otherwise.
     */
    bool is_complete_constructor_disabled() const;

    /**
     * @brief Returns true if XML serialization is disabled, false
     * otherwise.
     */
    bool is_xml_serialization_disabled() const;

public:
    /**
     * @brief Ensures all expected settings are available and set to
     * valid values.
     */
    void validate() const;

    /**
     * @brief Returns a scoped boilerplate formatter.
     */
    dogen::formatters::cpp::scoped_boilerplate_formatter
    make_scoped_boilerplate_formatter();

    /**
     * @brief Returns a scoped namespace formatter.
     */
    dogen::formatters::cpp::scoped_namespace_formatter
    make_scoped_namespace_formatter();

    /**
     * @brief Creates a nested type formatting assistant, latched on
     * the properties. Requires entity to be a class info.
     */
    nested_type_formatting_assistant
    make_nested_type_formatting_assistant();

    /**
     * @brief Generates a file with the current contents of the
     * stream.
     */
    dogen::formatters::file make_file(const bool overwrite = true) const;

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

public:
    /**
     * @brief Creates any helper methods that may be required for this
     * formatter.
     */
    void add_helper_methods();

    /**
     * @brief Returns true if the type can be hashed without requiring a
     * helper method.
     */
    bool requires_hashing_helper_method(
        const formattables::nested_type_info& t) const;

private:
    /**
     * @brief Retrieves the ODB settings from the opaque settings
     * container, if they do exist.
     */
    boost::shared_ptr<settings::odb_settings>
        get_odb_settings(const std::unordered_map<std::string,
            boost::shared_ptr<settings::opaque_settings> >& os) const;

public:
    /**
     * @brief Retrieves the ODB settings from the opaque settings
     * container, if they do exist.
     */
    boost::shared_ptr<settings::odb_settings> get_odb_settings() const;

    /**
     * @brief Retrieves the ODB settings for a given property from the
     * opaque settings container, if they do exist.
     */
    boost::shared_ptr<settings::odb_settings>
    get_odb_settings(const std::string& property_id) const;

private:
    const formattables::entity& entity_;
    const context& context_;
    const formattables::formatter_properties formatter_properties_;
    const dynamic::ownership_hierarchy ownership_hierarchy_;
    const formatters::file_types file_type_;
};

} } } }

#endif

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
#include "dogen/dynamic/types/ownership_hierarchy.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/quilt.cpp/types/settings/odb_settings.hpp"
#include "dogen/quilt.cpp/types/settings/opaque_settings.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/formattables/entity.hpp"
#include "dogen/quilt.cpp/types/formatters/file_types.hpp"
#include "dogen/quilt.cpp/types/formattables/class_info.hpp"
#include "dogen/quilt.cpp/types/formattables/property_info.hpp"
#include "dogen/quilt.cpp/types/formatters/nested_type_formatting_assistant.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

/**
 * @brief Provides a number of utilities to formatters.
 */
class assistant final {
public:
    assistant(const context& ctx, const dynamic::ownership_hierarchy& oh,
        const formatters::file_types ft);

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

    /**
     * @brief Creates a qualified name
     */
    std::string make_qualified_name(const yarn::name& n) const;

private:
    void ensure_formatter_properties_are_present() const;

    /**
     * @brief Obtains the formatter settings for the formatter as
     * given by the ownership hierarchy.
     */
    boost::optional<formattables::formatter_properties>
    obtain_formatter_properties(const std::string& formatter_name) const;

    /**
     * @brief Returns true if the formatter is enabled, false
     * otherwise.
     */
    bool is_formatter_enabled(const std::string& formatter_name) const;

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

    /**
     * @brief returns the c++ namespaces for the name.
     */
    std::list<std::string> make_namespaces(const yarn::name& n) const;

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
    make_scoped_namespace_formatter(const std::list<std::string>& ns);

    /**
     * @brief Creates a nested type formatting assistant, latched on
     * the properties. Requires entity to be a class info.
     */
    nested_type_formatting_assistant
    make_nested_type_formatting_assistant();

    /**
     * @brief Creates the preamble.
     */
    void make_annotation_preamble(
        const boost::optional<dogen::formatters::general_settings> gs);

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

private:
    /**
     * @brief Creates all the helper methods by recursing into the
     * nested type info.
     */
    void recursive_helper_method_creator(const formattables::class_info& owner,
        const yarn::name_tree& nt,
        std::unordered_set<std::string>& types_done);

public:
    /**
     * @brief Creates any helper methods that may be required for this
     * formatter.
     */
    void add_helper_methods(const formattables::class_info& owner,
        const std::list<formattables::property_info>& properties);

    /**
     * @brief Creates any helper methods that may be required for this
     * formatter.
     */
    void add_helper_methods(const formattables::class_info& c);

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

public:
    /**
     * @brief Returns the stream that is currently being populated.
     */
    std::ostream& stream();

    /**
     * @brief Generates a file with the current contents of the
     * stream.
     */
    dogen::formatters::file make_file(const boost::filesystem::path& full_path,
        const bool overwrite = true) const;

private:
    std::ostringstream stream_;
    boost::iostreams::filtering_ostream filtering_stream_;
    const context& context_;
    const boost::optional<formattables::formatter_properties>
    formatter_properties_;
    const dynamic::ownership_hierarchy ownership_hierarchy_;
    const formatters::file_types file_type_;
};

} } } }

#endif

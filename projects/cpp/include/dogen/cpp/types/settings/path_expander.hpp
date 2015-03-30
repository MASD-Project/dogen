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
#ifndef DOGEN_CPP_TYPES_SETTINGS_PATH_EXPANDER_HPP
#define DOGEN_CPP_TYPES_SETTINGS_PATH_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/schema/types/scope_types.hpp"
#include "dogen/cpp/types/settings/path_settings.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/cpp/types/formatters/formatter_interface.hpp"
#include "dogen/dynamic/expansion/types/expander_interface.hpp"
#include "dogen/cpp/types/settings/path_settings_factory_fwd.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Adds the file path fields to the dynamic object.
 */
class path_expander final : public dynamic::expansion::expander_interface {
public:
    /**
     * @brief Name property for other expanders that need to declare
     * it as a dependency.
     */
    static std::string static_name();

public:
    path_expander();
    ~path_expander() noexcept;

private:
    /**
     * @brief All relevant properties we need to remember for each formatter.
     */
    struct formatter_properties {
        std::string formatter_name;
        dynamic::schema::field_definition file_path;
        boost::optional<dynamic::schema::field_definition> inclusion_directive;
        boost::optional<dynamic::schema::field_definition> header_guard;
        path_settings settings;
    };

    /**
     * @brief Sets up formatter fields.
     */
    void setup_formatter_fields(const dynamic::schema::repository& rp,
        const std::string& formatter_name,
        formatter_properties& fp) const;

    /**
     * @brief Creates the set of formatter properties for a given
     * formatter.
     */
    formatter_properties make_formatter_properties(
        const dynamic::schema::repository& rp,
        const std::string& formatter_name,
        const std::unordered_map<std::string, path_settings>& ps) const;

    /**
     * @brief Generates all of the formatter properties, using the
     * repository data and the registered formatters.
     */
    std::unordered_map<std::string, formatter_properties>
        make_formatter_properties(const dynamic::schema::repository& rp,
            const dynamic::schema::object& root) const;

private:
    /**
     * @brief Returns the model's root dynamic object.
     */
    dynamic::schema::object obtain_root_object(const sml::model& m) const;

    /**
     * @brief Throws if not yet setup.
     */
    void ensure_is_setup() const;

    /**
     * @brief Builds a relative path from the top-level include
     * directory for the supplied qualified name.
     */
    boost::filesystem::path make_inclusion_path(const path_settings& ps,
        const sml::qname& qn) const;

    /**
     * @brief Builds an absolute path for the supplied qualified name.
     */
    boost::filesystem::path make_file_path(const path_settings& ps,
        const boost::filesystem::path& inclusion_path,
        const sml::qname& qn) const;

    /**
     * @brief Converts a relative path to an inclusion directive.
     */
    std::string to_inclusion_directive(const boost::filesystem::path& p) const;

    /**
     * @brief Converts a relative path to a header file into a C++
     * header guard name.
     */
    std::string to_header_guard_name(const boost::filesystem::path& p) const;

private:
    /**
     * @brief Handles the dynamic expansion of the file path.
     */
    void expand_file_path(const formatter_properties& fp,
        const boost::filesystem::path& file_path,
        dynamic::schema::object& o) const;

    /**
     * @brief Handles the dynamic expansion of the header guard.
     */
    void expand_header_guard(const formatter_properties& fp,
        const boost::filesystem::path& inclusion_path,
        dynamic::schema::object& o) const;

    /**
     * @brief Handles the dynamic expansion of the include directive.
     */
    void expand_include_directive(const formatter_properties& fp,
        const boost::filesystem::path& inclusion_path,
        dynamic::schema::object& o) const;

public:
    std::string name() const override;

    const std::forward_list<std::string>& dependencies() const override;

    void setup(const dynamic::expansion::expansion_context& ec) override;

    void expand(const sml::qname& qn, const dynamic::schema::scope_types& st,
        dynamic::schema::object& o) const override;

private:
    bool requires_file_path_expansion_;
    std::shared_ptr<const path_settings_factory> factory_;
    std::unordered_map<std::string, formatter_properties> formatter_properties_;
};

} } }

#endif

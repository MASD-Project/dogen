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
#ifndef DOGEN_CPP_TYPES_EXPANSION_INCLUSION_DEPENDENCIES_EXPANDER_HPP
#define DOGEN_CPP_TYPES_EXPANSION_INCLUSION_DEPENDENCIES_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/sml/types/qname.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/dynamic/expansion/types/expander_interface.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

/**
 * @brief Performs the include dependencies expansion required by the
 * c++ model.
 */
class inclusion_dependencies_expander
    : public dynamic::expansion::expander_interface {
public:
    ~inclusion_dependencies_expander() noexcept;

private:
    /**
     * @brief Field definitions we need to remember for each formatter.
     */
    struct field_definitions {
        boost::optional<dynamic::schema::field_definition> inclusion_dependency;
    };

    /**
     * @brief Sets up all field definitions for a given formatter.
     */
    field_definitions field_definitions_for_formatter_name(
        const dynamic::schema::repository& rp,
        const std::string& formatter_name) const;

    /**
     * @brief Generates all of the formatter field definitions, using
     * the repository data and the registered formatters.
     */
    std::unordered_map<std::string, field_definitions>
    setup_field_definitions(const dynamic::schema::repository& rp,
        const formatters::container& fc) const;

private:
    /**
     * @brief Handles the dynamic expansion of the include
     * dependencies for a given formatter.
     */
    void expand_inclusion_dependencies(const std::string& formatter_name,
        const field_definitions& fd, const std::list<std::string>& deps,
        dynamic::schema::object& o) const;

public:
    std::string name() const override;

    const std::forward_list<std::string>& dependencies() const override;

    dynamic::expansion::expansion_types expansion_type() const override;

    void setup(const dynamic::expansion::expansion_context& ec) override;

    void expand(const sml::qname& qn, const dynamic::schema::scope_types& st,
        dynamic::schema::object& o) const override;

private:
    std::unordered_map<std::string, field_definitions> field_definitions_;
    std::unordered_map<sml::qname,
                       std::unordered_map<std::string, std::list<std::string> >
                       > inclusion_dependencies_;
};

} } }

#endif

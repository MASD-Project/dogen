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
#ifndef DOGEN_CPP_TYPES_EXPANSION_ENABLED_FLAG_EXPANDER_HPP
#define DOGEN_CPP_TYPES_EXPANSION_ENABLED_FLAG_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/dynamic/expansion/types/expander_interface.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

class enabled_flag_expander
    : public dynamic::expansion::expander_interface {
public:
    ~enabled_flag_expander() noexcept;

private:
    /**
     * @brief Field definitions we need to remember for each formatter.
     */
    struct field_definitions {
        dynamic::schema::field_definition facet_enabled;
        dynamic::schema::field_definition formatter_enabled;
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
     * @brief Properties at the formatter level.
     */
    struct formatter_properties {
        bool facet_enabled;
        bool formatter_enabled;
    };

private:
    /**
     * @brief Returns a qualified field name.
     */
    std::string qualify(const std::string& prefix,
        const std::string& field_name) const;

    /**
     * @brief Obtains the root object for the model.
     */
    dynamic::schema::object
    obtain_root_object(const sml::model& m) const;

    /**
     * @brief
     */
    std::unordered_map<std::string, formatter_properties>
    setup_formatter_properties() const;

private:
    std::unordered_map<std::string, formatter_properties> formatter_proprties_;
};

} } }

#endif

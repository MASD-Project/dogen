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
#ifndef DOGEN_CPP_TYPES_SETTINGS_INCLUSION_DIRECTIVES_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_INCLUSION_DIRECTIVES_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/cpp/types/formatters/formatter_interface.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/settings/inclusion_directives_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {


class inclusion_directives_settings_factory {
public:
    inclusion_directives_settings_factory(const dynamic::repository& rp,
        const formatters::container& fc);

private:
    /**
     * @brief All relevant properties we need to remember for each formatter.
     */
    struct formatter_properties {
        std::string formatter_name;
        dynamic::field_definition inclusion_directive;
        dynamic::field_definition inclusion_required;
    };

    /**
     * @brief Creates the set of formatter properties for a given
     * formatter.
     */
    formatter_properties make_formatter_properties(
        const dynamic::repository& rp,
        const formatters::formatter_interface& f) const;

    /**
     * @brief Generates all of the formatter properties, using the
     * repository data and the registered formatters.
     */
    std::unordered_map<std::string, formatter_properties>
    make_formatter_properties(const dynamic::repository& rp,
        const formatters::container& fc) const;

    /**
     * @brief Gets up the top-level (non-formatter specific) inclusion
     * required field.
     */
    dynamic::field_definition get_top_level_inclusion_required_field(
        const dynamic::repository& rp) const;

private:
    /**
     * @brief Obtains the inclusion directive for a given formatter.
     */
    boost::optional<std::string> obtain_inclusion_directive_for_formatter(
        const formatter_properties& fp,
        const dynamic::object& o) const;

    /**
     * @brief Obtains the inclusion required flag for a given formatter.
     */
    bool obtain_inclusion_required_for_formatter(
        const formatter_properties& fp,
        const dynamic::object& o) const;

    /**
     * @brief Obtains the value of the inclusion required flag.
     */
    bool obtain_top_level_inclusion_required(
        const dynamic::object& o) const;

public:
    /**
     * @brief Produce the inclusion directive settings for all
     * formatters.
     */
    inclusion_directives_settings make(const dynamic::object& o) const;

private:
    const std::unordered_map<std::string, formatter_properties>
    formatter_properties_;
    dynamic::field_definition inclusion_required_;
};

} } }

#endif

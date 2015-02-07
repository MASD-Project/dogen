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
#ifndef DOGEN_CPP_TYPES_SETTINGS_SELECTOR_HPP
#define DOGEN_CPP_TYPES_SETTINGS_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/qname.hpp"
#include "dogen/formatters/types/annotation.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/cpp/types/settings/settings.hpp"
#include "dogen/cpp/types/settings/cpp_settings.hpp"
#include "dogen/cpp/types/settings/facet_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Performs a number of queries over settings data.
 */
class selector {
public:
    /**
     * @brief Initialise the selector.
     *
     * @param s data to select from.
     */
    selector(const settings& s);

public:
    /**
     * @brief Returns the general settings for the supplied entity
     * identity.
     */
    const dogen::formatters::general_settings& select_general_settings(
        const std::string& identity) const;

    /**
     * @brief Returns the annotation for the supplied entity identity.
     */
    const dogen::formatters::annotation& select_annotation(
        const std::string& identity) const;

    /**
     * @brief Returns the c++ settings.
     */
    const cpp_settings& select_cpp_settings() const;

    /**
     * @brief Returns the facet settings for the supplied facet name.
     *
     * @pre There must exist settings for the supplied facet name.
     */
    const facet_settings&
    select_facet_settings(const std::string& facet_name) const;

    /**
     * @brief Returns the formatter settings for the supplied
     * entity identity and formatter name.
     *
     * @pre There must exist settings for the supplied entity identity
     * and formatter name.
     */
    const formatter_settings&
    select_formatter_settings(const std::string& identity,
        const std::string& formatter_name) const;

    /**
     * @brief Returns the formatter settings for the supplied
     * qualified name and formatter name.
     *
     * @pre There must exist settings for the supplied qualified name
     * and formatter name.
     */
    const formatter_settings&
    select_formatter_settings(const sml::qname& qn,
        const std::string& formatter_name) const;

public:
    /**
     * @brief Returns the underlying settings.
     *
     * FIXME: hack for now
     */
    const cpp::settings::settings& settings() const;

private:
    const cpp::settings::settings& settings_;
};

} } }

#endif

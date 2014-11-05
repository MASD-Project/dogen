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
#ifndef DOGEN_CPP_TYPES_REGISTRAR_HPP
#define DOGEN_CPP_TYPES_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include <unordered_map>
#include "dogen/cpp/types/facet_settings.hpp"
#include "dogen/cpp/types/formatters/class_formatter_interface.hpp"

namespace dogen {
namespace cpp {

class registrar {
public:
    typedef std::forward_list<
        std::shared_ptr<formatters::class_formatter_interface>
    > class_formatters_type;

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

    /**
     * @brief Registers default facet settings for a given facet.
     */
    void register_default_facet_settings(const std::string& facet_id,
        const facet_settings& s);

    /**
     * @brief Registers a class formatter.
     */
    void register_formatter(
        std::shared_ptr<formatters::class_formatter_interface> f);

    /**
     * @brief Returns all available class formatters.
     */
    const class_formatters_type& class_formatters() const;

    /**
     * @brief Returns all default settings for all facets.
     */
    const std::unordered_map<std::string, facet_settings>&
    default_facet_settings_by_facet_id() const;

private:
    class_formatters_type class_formatters_;
    std::unordered_map<std::string, facet_settings>
    default_facet_settings_by_facet_id_;
};

} }

#endif

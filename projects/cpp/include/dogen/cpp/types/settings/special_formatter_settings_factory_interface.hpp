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
#ifndef DOGEN_CPP_TYPES_SETTINGS_SPECIAL_FORMATTER_SETTINGS_FACTORY_INTERFACE_HPP
#define DOGEN_CPP_TYPES_SETTINGS_SPECIAL_FORMATTER_SETTINGS_FACTORY_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/cpp/types/settings/special_formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class special_formatter_settings_factory_interface {
public:
    special_formatter_settings_factory_interface() = default;
    special_formatter_settings_factory_interface(
        const special_formatter_settings_factory_interface&) = delete;
    special_formatter_settings_factory_interface(
        special_formatter_settings_factory_interface&&) = default;
    virtual ~special_formatter_settings_factory_interface() noexcept = 0;

public:
    /**
     * @brief Name of the formatter for which the settings will be
     * made.
     */
    virtual std::string formatter_name() const = 0;

    /**
     * @brief Produces the special settings for this formatter.
     */
    virtual boost::shared_ptr<special_formatter_settings>
    make(const dynamic::schema::object& o) const = 0;
};

} } }

#endif

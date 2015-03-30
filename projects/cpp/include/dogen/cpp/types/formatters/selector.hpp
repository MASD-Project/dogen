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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_SELECTOR_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class selector {
public:
    selector(const dynamic::schema::repository& rp,
        const dynamic::schema::object& o);

private:
    /**
     * @brief Returns a qualified field name.
     */
    std::string qualify(const std::string& prefix,
        const std::string& field_name) const;

public:
    /**
     * @brief Returns true if the supplied formatter is enabled, false
     * otherwise.
     */
    bool is_formatter_enabled(const std::string& formatter_name) const;

    /**
     * @brief Returns true if the supplied facet is part of the
     * integrated facets for the supplied formatter.
     */
    bool is_facet_integrated(const std::string& formatter_name,
        const std::string& facet_name) const;

private:
    const dynamic::schema::repository& repository_;
    const dynamic::schema::object& object_;
    const dynamic::schema::field_selector field_selector_;
};

} } }

#endif

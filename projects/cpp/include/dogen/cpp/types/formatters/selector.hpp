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
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_selector.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class selector {
public:
    selector(const dynamic::repository& rp, const dynamic::object& o);

public:
    /**
     * @brief Returns true if the supplied formatter is enabled, false
     * otherwise.
     */
    bool is_formatter_enabled(const std::string& formatter_name) const;

    /**
     * @brief Returns true if the supplied facet is enabled, false
     * otherwise.
     */
    bool is_facet_enabled(const std::string& facet_name) const;

    /**
     * @brief Returns true if the supplied facet is part of the
     * integrated facets for the supplied formatter.
     */
    bool is_facet_integrated(const std::string& formatter_name,
        const std::string& facet_name) const;

public:
    /**
     * @brief Returns true if the io facet is enabled.
     */
    bool is_io_enabled() const;

    /**
     * @brief Returns true if the io facet is enabled and integrated
     * against the types facet.
     */
    bool is_integrated_io_enabled() const;

    /**
     * @brief Returns true if the serialization fact is enabled.
     */
    bool is_serialization_enabled() const;

    /**
     * @brief Returns true if the hash fact is enabled.
     */
    bool is_hash_enabled() const;

private:
    const dynamic::repository& repository_;
    const dynamic::object& object_;
    const dynamic::field_selector field_selector_;
};

} } }

#endif

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
#ifndef DOGEN_SML_TYPES_INDEXER_INTERFACE_HPP
#define DOGEN_SML_TYPES_INDEXER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/abstract_object.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Indexes model information and provides a querying interface.
 */
class indexer_interface {
public:
    indexer_interface() = default;
    indexer_interface(const indexer_interface&) = delete;
    indexer_interface(indexer_interface&&) = delete;
    indexer_interface& operator=(const indexer_interface&) = delete;

public:
    virtual ~indexer_interface() noexcept { }

public:
    /**
     * @brief Get all properties associated with this object.
     *
     * This includes properties obtained via concepts, local
     * properties, inherited properties, etc.
     *
     */
    virtual std::list<property>
    all_properties(const abstract_object& o) const = 0;

    /**
     * @brief Get the properties "local" to the object.
     *
     * Local properties are defined to be properties that belong to
     * the type directly, and those that belong to concepts that the
     * object models. Properties that belong to concepts modeled by
     * parent classes are not included.
     *
     */
    virtual std::list<property>
    local_properties(const abstract_object& o) const = 0;

    /**
     * @brief Properties that the type inherited.
     *
     * Includes properties obtained by direct parents -
     * e.g. equivalent to calling all properties on each parent.
     *
     * @return map with properties, by parent.
     */
    virtual std::unordered_map<qname, std::list<property> >
    inehrited_properties(const abstract_object& o) const = 0;
};

} }

#endif

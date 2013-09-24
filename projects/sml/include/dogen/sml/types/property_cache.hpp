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
#ifndef DOGEN_SML_TYPES_PROPERTY_CACHE_HPP
#define DOGEN_SML_TYPES_PROPERTY_CACHE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/property_cache_interface.hpp"

namespace dogen {
namespace sml {

class property_cache : public property_cache_interface {
public:
    property_cache(const property_cache&) = default;
    property_cache(property_cache&&) = default;
    property_cache& operator=(const property_cache&) = default;

public:
    property_cache();
    virtual ~property_cache() noexcept { }

public:
public:
    /**
     * @brief Populates all the data structures required for querying.
     *
     * @param m model to populate the cache with.
     */
    void populate(const sml::model& m);

    /**
     * @brief Returns true if populating has been done, false otherwise.
     */
    bool is_populated() const;

private:
    /**
     * @brief If not populated throws a population error.
     */
    void ensure_populated() const;

public:
    /**
     * @pre is_populated must be true.
     */
    std::list<property>
    get_all_properties(const abstract_object& o) const override;

    /**
     * @pre is_populated must be true.
     */
    std::list<property>
    get_local_properties(const abstract_object& o) const override;

    /**
     * @pre is_populated must be true.
     */
    std::unordered_map<qname, std::list<property> >
    get_inehrited_properties(const abstract_object& o) const override;

private:
    bool is_populated_;
    std::unordered_map<qname, std::list<property> > all_properties_;
    std::unordered_map<qname, std::list<property> > local_properties_;
    std::unordered_map<qname, std::list<property> > inherited_properties_;
};

} }

#endif

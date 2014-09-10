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
#ifndef DOGEN_SML_TYPES_META_DATA_ENRICHER_INTERFACE_HPP
#define DOGEN_SML_TYPES_META_DATA_ENRICHER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/optional.hpp>
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/concept.hpp"

namespace dogen {
namespace sml {
namespace meta_data {

/**
 * @brief Enriches a subset of the meta-data for a given target.
 */
class enricher_interface {
public:
    enricher_interface() = default;
    enricher_interface(const enricher_interface&) = delete;
    enricher_interface(enricher_interface&&) = default;
    virtual ~enricher_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for this enriches.
     */
    virtual std::string id() const = 0;

    /**
     * @brief List of unique identifiers of other enrichers that must
     * be executed before this enrichers.
     */
    virtual std::list<std::string> dependencies() const = 0;

    /**
     * @brief Enrich concept tags.
     */
    virtual void enrich(const model& model,
        boost::optional<const module> parent_module,
        concept& target) = 0;

    /**
     * @brief Enrich module tags.
     */
    virtual void enrich(const model& model,
        boost::optional<const module> parent_module,
        module& target) = 0;

    /**
     * @brief Enrich type tags.
     */
    virtual void enrich(const model& model,
        boost::optional<const module> parent_module,
        type& target) = 0;
};

} } }

#endif

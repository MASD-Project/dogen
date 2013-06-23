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
#ifndef DOGEN_SML_TYPES_RESOLVER_HPP
#define DOGEN_SML_TYPES_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/reference.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Resolves type references within a model.
 */
class resolver {
public:
    resolver() = delete;
    resolver(const resolver&) = default;
    ~resolver() = default;
    resolver(resolver&&) = default;
    resolver& operator=(const resolver&) = default;

public:
    /**
     * @brief Initialises resolver to resolve model m.
     *
     * @param model to resolve.
     *
     * @pre Model must continue to live until resolution has been
     * completed.
     */
    explicit resolver(model& m);

private:
    /**
     * @brief Resolves a partially formed qname into a full qname.
     */
    qname resolve_partial_type(const qname& n) const;

    /**
     * @brief Resolves all references contained in a nested qname.
     */
    void resolve_partial_type(nested_qname& t) const;

    /**
     * @brief Resolves all references contained in the pod's
     * properties.
     */
    std::vector<property> resolve_properties(const pod& pod);

    /**
     * @brief Resolves inheritance related references.
     */
    void resolve_parent(const pod& pod);

    /**
     * @brief Resolve model references.
     */
    void resolve_references();

    /**
     * @brief Resolution must not yet have taken place.
     */
    void require_not_has_resolved() const;

public:
    /**
     * @brief Returns true if resolution has already been performed,
     * false otherwise.
     */
    bool has_resolved() const { return has_resolved_; }

    /**
     * @brief Add a reference to a dependent model.
     *
     * @pre Resolution has not been performed yet.
     */
    void add_reference(const reference& ref);

    /**
     * @brief Resolve all references to types within model.
     *
     * @pre Resolution has not been performed yet.
     */
    void resolve();

private:
    model& model_;
    bool has_resolved_;
    std::unordered_map<std::string, reference> references_;
};

} }

#endif

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
#ifndef DOGEN_TACK_TYPES_INJECTOR_HPP
#define DOGEN_TACK_TYPES_INJECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include "dogen/tack/types/model.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Injects types into a model.
 *
 * Injector is responsible for analysing all of the types defined by
 * the user and deciding:
 *
 * @li whether to augment that type; that is, due to the configuration
 * of that type, we may need to add additional properties to the
 * type. This is the case with versioning, for example.
 *
 * @li whether to create supporting types that enhance the current
 * type. This is the case with the generation of visitors, etc.
 *
 * Note: we have taken the simplistic approach of looping over the
 * object collection as many times as required, to keep the logic
 * simple. We should probably optimise this at some point.
 *
 */
class injector {
public:
    injector() = default;
    injector(const injector&) = default;
    ~injector() = default;
    injector(injector&&) = default;
    injector& operator=(const injector&) = default;

private:
    class context;

private:
    /**
     * @brief Inserts object into model's object container.
     *
     * @return True if the object did not exist in container, false
     * otherwise.
     */
    bool insert(const object& o);

    /**
     * @brief Create a visitor for the object o.
     *
     * @param o visitable object
     * @param leaves cached leaves to avoid look-up.
     *
     * @pre leaves must not be empty.
     */
    object create_visitor(const object& o,
        const std::list<qname>& leaves) const;

    /**
     * @brief Injects an accept operation for the given visitor, to
     * the supplied object and all its leaves.
     */
    void inject_visited_by(object& root, const std::list<qname>& leaves,
        const qname& visitor) const;

    /**
     * @brief Injects visitors for objects that require them.
     */
    void inject_visitors();

    /**
     * @brief Injects the global module, and makes all modules that do
     * not have a containing namespace be contained by it.
     */
    void inject_global_module();

public:

    /**
     * @brief Inject system defined types into the model.
     *
     * @param m Tack model to operate on.
     */
    void inject(model& m);

private:
    mutable std::shared_ptr<context> context_;
};

} }

#endif

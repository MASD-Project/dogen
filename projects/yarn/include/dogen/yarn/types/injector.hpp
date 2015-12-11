/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_YARN_TYPES_INJECTOR_HPP
#define DOGEN_YARN_TYPES_INJECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Injects types into an intermediate model.
 *
 * Injector is responsible for analysing all of the types defined by
 * the user and deciding:
 *
 * @li whether to augment that type; that is, due to the configuration
 * of that type, we may need to add additional properties to the
 * type.
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
private:
    /**
     * @brief Creates the module to represent the global namespace.
     */
    module create_global_module() const;

    /**
     * @brief Create a visitor for the object o.
     *
     * @param o visitable object
     * @param leaves cached leaves to avoid look-up.
     *
     * @pre leaves must not be empty.
     */
    visitor create_visitor(const object& o,
        const std::list<name>& leaves) const;

    /**
     * @brief Injects an accept operation for the given visitor, to
     * the supplied object and all its leaves.
     */
    void inject_visitable_by(object& root, const std::list<name>& leaves,
        const name& visitor, intermediate_model& m) const;

    /**
     * @brief Injects visitors for objects that require them.
     */
    void inject_visitors(intermediate_model& m);

    /**
     * @brief Injects the global module, and makes all modules that do
     * not have a containing namespace be contained by it.
     */
    void inject_global_module(intermediate_model& m);

public:

    /**
     * @brief Inject system defined types into the intermediate model.
     *
     * @param m Yarn model to operate on.
     */
    void inject(intermediate_model& m);
};

} }

#endif

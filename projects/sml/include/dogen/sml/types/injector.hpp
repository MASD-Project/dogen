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
#ifndef DOGEN_SML_TYPES_INJECTOR_HPP
#define DOGEN_SML_TYPES_INJECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

class injector {
public:
    injector(const injector&) = default;
    ~injector() = default;
    injector(injector&&) = default;
    injector& operator=(const injector&) = default;

public:
    injector();
    explicit injector(const bool add_versioning_types);

private:
    /**
     * @brief Creates a key for the given pod.
     *
     * @param p pod for which to create a key
     * @param is_versioned if true, create a versioned key. Otherwise,
     * creates an unversioned key.
     */
    pod create_key_system_pod(const sml::pod& p, const bool is_versioned) const;

    /**
     * @brief Performs the deprecated behaviour for key management.
     */
    void inject_legacy_keys(model& m) const;

    /**
     * @brief Injects the version property on any types marked as
     * versioned.
     */
    void inject_versioning(model& m) const;

public:

    /**
     * @brief Inject system defined types into the model.
     *
     * @param m SML model to operate on.
     */
    void inject(model& m) const;

private:
    const bool add_versioning_types_;
};

} }

#endif

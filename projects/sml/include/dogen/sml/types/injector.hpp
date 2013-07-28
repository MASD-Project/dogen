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

#include <list>
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

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
 * type. This is the case with the generation of keys, visitors, etc.
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
    /**
     * @brief Creates a key for the given entity.
     *
     * @param qn name of the entity for which to create the key
     * @param gt type of the generation to apply to the key
     * @param properties identity function for the entity
     * @param versioned if true, create a versioned key. Otherwise,
     * creates an unversioned key.
     */
    boost::shared_ptr<abstract_object> create_key(const qname& qn,
        const generation_types gt, const std::list<property>& properties,
        const bool versioned) const;

    /**
     * @brief Helper functions for create key just for the sake of
     * clarity.
     */
    /**@{*/
    boost::shared_ptr<abstract_object> create_versioned_key(const qname& qn,
        const generation_types gt, const std::list<property>& properties) const;
    boost::shared_ptr<abstract_object> create_unversioned_key(const qname& qn,
        const generation_types gt, const std::list<property>& properties) const;
    /**@}*/

    /**
     * @brief Create a visitor for the object.
     */
    boost::shared_ptr<abstract_object>
    create_key_extractor(const keyed_entity& ke) const;

    /**
     * @brief Injects versioned and unversioned keys for keyed
     * entities, and the associated key extractor.
     */
    void inject_keys(model& m) const;

    /**
     * @brief Injects the version property on the object passed in.
     */
    void inject_version(abstract_object& p) const;

    /**
     * @brief Injects the version property on any types marked as
     * versioned.
     */
    void inject_version(model& m) const;

    /**
     * @brief Create a visitor for the object.
     */
    boost::shared_ptr<abstract_object>
    create_visitor(const abstract_object& ao) const;

    /**
     * @brief Injects an accept operation for the given visitor.
     */
    void inject_accept(abstract_object& ao, const abstract_object& v) const;

    /**
     * @brief Injects visitors for objects that require them.
     */
    void inject_visitors(model& m) const;

public:

    /**
     * @brief Inject system defined types into the model.
     *
     * @param m SML model to operate on.
     */
    void inject(model& m) const;
};

} }

#endif

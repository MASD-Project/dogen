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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_KERNEL_REGISTRAR_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_KERNEL_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif


#include <list>
#include <string>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/yarn/types/meta_model/languages.hpp"
#include "dogen/yarn/types/transforms/kernel_interface.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

/**
 * @brief Keeps track of all the available kernels.
 */
class kernel_registrar {
public:
    /**
     * @brief Registers a kernel.
     */
    void register_kernel(std::shared_ptr<kernel_interface> k);

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Returns the kernel for the supplied language, if any
     * exists. Otherwise returns a null shared pointer.
     */
    std::shared_ptr<kernel_interface>
    kernel_for_language(const yarn::meta_model::languages l) const;

    /**
     * @brief Returns all available kernels, by language.
     */
    const std::unordered_map<yarn::meta_model::languages,
                             std::shared_ptr<kernel_interface>>&
    kernels_by_language() const;

    /**
     * @brief Returns all of the available archetype locations across
     * all kernels.
     */
    const std::list<annotations::archetype_location>&
    archetype_locations() const;

    /**
     * @brief Returns the archetype locations for each element type
     * index.
     */
    const std::unordered_map<std::type_index,
                             std::list<annotations::archetype_location>>&
    archetype_locations_by_element_type_index() const;

private:
    std::list<annotations::archetype_location> archetype_locations_;
    std::unordered_map<std::type_index,
                       std::list<annotations::archetype_location>>
    archetype_locations_by_element_type_index_;
    std::unordered_map<yarn::meta_model::languages,
                       std::shared_ptr<kernel_interface>> kernels_by_language_;
};

} } }

#endif

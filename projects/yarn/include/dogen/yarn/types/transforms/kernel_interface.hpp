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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_KERNEL_INTERFACE_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_KERNEL_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/yarn/types/meta_model/model.hpp"
#include "dogen/yarn/types/meta_model/languages.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/code_generation_output.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

/**
 * @brief Performs a model to text transformation of a meta-model,
 * into its supported language.
 */
class kernel_interface {
public:
    kernel_interface() = default;
    kernel_interface(const kernel_interface&) = delete;
    kernel_interface(kernel_interface&&) = default;
    virtual ~kernel_interface() noexcept = 0;

public:
    /**
     * @brief Returns the identity of this kernel.
     */
    virtual std::string id() const = 0;

    /**
     * @brief The artefact location for the kernel itself.
     *
     * Note that this is not a "true" archetype location, but a
     * location of a container of archetypes (the kernel).
     */
    virtual annotations::archetype_location archetype_location() const = 0;

    /**
     * @brief All archetype locations for the archetypes owned by this
     * kernel, listing all available kernels, facets and archetypes.
     *
     * FIXME: we need a better name for this.
     */
    virtual std::forward_list<annotations::archetype_location>
    archetype_locations() const = 0;

    /**
     * @brief Language supported by this kernel.
     */
    virtual yarn::meta_model::languages language() const = 0;

    /**
     * @brief Generates the source code for the kernel.
     */
    virtual code_generation_output
    generate(const context& ctx, const bool requires_kernel_directory,
        const meta_model::model& m) const = 0;
};

} } }

#endif

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
#ifndef DOGEN_QUILT_TYPES_BACKEND_INTERFACE_HPP
#define DOGEN_QUILT_TYPES_BACKEND_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/ownership_hierarchy.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/formatters/types/file.hpp"

namespace dogen {
namespace quilt {

/**
 * @brief Responsible for converting a Yarn model into source code
 * according to a well-defined grammar.
 */
class backend_interface {
public:
    backend_interface() = default;
    backend_interface(const backend_interface&) = delete;
    backend_interface(backend_interface&&) = default;
    virtual ~backend_interface() noexcept = 0;

public:
    /**
     * @brief Name of the backend. It must be unique.
     */
    virtual std::string name() const = 0;

    /**
     * @brief Returns all directories managed by this backend.
     */
    virtual std::forward_list<boost::filesystem::path>
    managed_directories(const options::knitting_options& ko,
        const yarn::name& model_name) const = 0;

    /**
     * @brief Complete ownership hierarchy for this backend, listing
     * all available models, facet and formatters.
     */
    virtual std::forward_list<annotations::ownership_hierarchy>
    ownership_hierarchy() const = 0;

    /**
     * @brief Generates the source code for the backend.
     *
     * @param gs General settings for the Yarn types.
     * @param m Model to generate.
     */
    virtual std::forward_list<formatters::file> generate(
        const options::knitting_options& ko,
        const annotations::type_repository& atrp,
        const yarn::model& m) const = 0;
};

} }

#endif

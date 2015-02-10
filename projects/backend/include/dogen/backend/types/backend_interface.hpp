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
#ifndef DOGEN_BACKEND_TYPES_BACKEND_INTERFACE_HPP
#define DOGEN_BACKEND_TYPES_BACKEND_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/model.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/config/types/knitting_options.hpp"

namespace dogen {
namespace backend {

/**
 * @brief Responsible for converting an SML model into source code
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
     * @brief Unique identifier for the backend, for logging purposes.
     */
    virtual std::string id() const = 0;

    /**
     * @brief Returns all directories managed by this backend.
     */
    virtual std::vector<boost::filesystem::path>
    managed_directories() const = 0;

    /**
     * @brief Ensures the backend is in a valid state to operate.
     */
    virtual void validate() const = 0;

    /**
     * @brief Generates the source code for the backend.
     *
     * @param gs General settings for the SML types.
     * @param m Model to generate.
     */
    virtual std::forward_list<formatters::file> generate(
        const config::knitting_options& o, const sml::model& m) const = 0;
};

} }

#endif

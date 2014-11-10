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
#ifndef DOGEN_CPP_TYPES_INCLUDES_BUILDER_INTERFACE_HPP
#define DOGEN_CPP_TYPES_INCLUDES_BUILDER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/consumer_interface.hpp"
#include "dogen/cpp/types/includes.hpp"
#include "dogen/cpp/types/path_spec_key.hpp"
#include "dogen/cpp/hash/path_spec_key_hash.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Builds all of the includes for a given formatter.
 */
class includes_builder_interface : public sml::consumer_interface {
public:
    includes_builder_interface() = default;
    includes_builder_interface(const includes_builder_interface&) = delete;
    includes_builder_interface(includes_builder_interface&&) = default;
    virtual ~includes_builder_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for the formatter we are building
     * includes for.
     */
    virtual std::string formatter_id() const = 0;

    /**
     * @brief Provides all the relative paths the system knows of,
     * keyed by qualified name and formatter id.
     */
    virtual void setup_relative_paths(
        const std::unordered_map<path_spec_key, boost::filesystem::path>&
        relative_paths) = 0;

    /**
     * @brief Provides the result of the building process. Expected to
     * be called after the consumption workflow has finished executing.
     */
    virtual std::unordered_map<path_spec_key, includes>
    includes_for_path_spec_key() const = 0;
};

} }

#endif

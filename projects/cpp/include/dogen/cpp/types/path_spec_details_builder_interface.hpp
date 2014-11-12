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
#ifndef DOGEN_CPP_TYPES_PATH_SPEC_DETAILS_BUILDER_INTERFACE_HPP
#define DOGEN_CPP_TYPES_PATH_SPEC_DETAILS_BUILDER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/includes.hpp"
#include "dogen/cpp/types/path_spec_key.hpp"
#include "dogen/cpp/hash/path_spec_key_hash.hpp"
#include "dogen/cpp/types/path_spec_details.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Builds a subset of the path spec details for a model.
 */
class path_spec_details_builder_interface  {
public:
    path_spec_details_builder_interface() = default;
    path_spec_details_builder_interface(
        const path_spec_details_builder_interface &) = delete;
    path_spec_details_builder_interface(
        path_spec_details_builder_interface &&) = default;
    virtual ~path_spec_details_builder_interface () noexcept = 0;

public:
    /**
     * @brief Build the details.
     *
     * @param m model for which to build the details.
     *
     * @param relative_paths relative paths the system knows of, keyed
     * by qualified name and formatter id.
     */
    virtual std::unordered_map<path_spec_key, path_spec_details> build(
        const sml::model& m,
        const std::unordered_map<path_spec_key, boost::filesystem::path>&
        relative_file_names_for_key) const = 0;
};

} }

#endif

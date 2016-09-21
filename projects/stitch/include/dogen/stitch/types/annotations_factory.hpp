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
#ifndef DOGEN_STITCH_TYPES_ANNOTATIONS_FACTORY_HPP
#define DOGEN_STITCH_TYPES_ANNOTATIONS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/stitch/types/annotations.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Creates the stitching settings.
 */
class annotations_factory {
public:
    annotations_factory(const dynamic::repository& rp);

private:
    /**
     * @brief All relevant properties we need to remember for each formatter.
     */
    struct formatter_properties {
        dynamic::field_definition stream_variable_name;
        dynamic::field_definition template_path;
        dynamic::field_definition output_path;
        dynamic::field_definition relative_output_directory;
        dynamic::field_definition inclusion_dependency;
        dynamic::field_definition containing_namespaces;
    };

    /**
     * @brief Creates the formatter properties.
     */
    formatter_properties
    make_formatter_properties(const dynamic::repository& rp) const;

private:
    /**
     * @brief Extracts the stream variable name.
     */
    std::string
    extract_stream_variable_name(const dynamic::object& o) const;

    /**
     * @brief Extracts the template path.
     */
    boost::optional<boost::filesystem::path>
    extract_template_path(const dynamic::object& o) const;

    /**
     * @brief Extracts the file path.
     */
    boost::optional<boost::filesystem::path>
    extract_output_path(const dynamic::object& o) const;

    /**
     * @brief Extracts the relative output directory.
     */
    boost::optional<boost::filesystem::path>
    extract_relative_output_directory(const dynamic::object& o) const;

    /**
     * @brief Extracts inclusion dependencies.
     */
    std::list<std::string>
    extract_inclusion_dependencies(const dynamic::object& o) const;

    /**
     * @brief Extract containing namespaces.
     */
    std::list<std::string>
    extract_containing_namespaces(const dynamic::object& o) const;

public:
    /**
     * @brief Create the stitching settings.
     */
    annotations make(const dynamic::object& o) const;

private:
    const formatter_properties formatter_properties_;
};

} }

#endif

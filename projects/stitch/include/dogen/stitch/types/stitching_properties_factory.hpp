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
#ifndef DOGEN_STITCH_TYPES_STITCHING_PROPERTIES_FACTORY_HPP
#define DOGEN_STITCH_TYPES_STITCHING_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/stitch/types/stitching_properties.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Creates the stitching settings.
 */
class stitching_properties_factory {
public:
    stitching_properties_factory(const annotations::type_repository& arp);

private:
    struct type_group {
        annotations::type stream_variable_name;
        annotations::type template_path;
        annotations::type output_path;
        annotations::type relative_output_directory;
        annotations::type inclusion_dependency;
        annotations::type containing_namespaces;
    };

    /**
     * @brief Creates the formatter properties.
     */
    type_group
    make_type_group(const annotations::type_repository& arp) const;

private:
    /**
     * @brief Extracts the stream variable name.
     */
    std::string
    extract_stream_variable_name(const annotations::annotation& a) const;

    /**
     * @brief Extracts the template path.
     */
    boost::optional<boost::filesystem::path>
    extract_template_path(const annotations::annotation& a) const;

    /**
     * @brief Extracts the file path.
     */
    boost::optional<boost::filesystem::path>
    extract_output_path(const annotations::annotation& a) const;

    /**
     * @brief Extracts the relative output directory.
     */
    boost::optional<boost::filesystem::path>
    extract_relative_output_directory(const annotations::annotation& a) const;

    /**
     * @brief Extracts inclusion dependencies.
     */
    std::list<std::string>
    extract_inclusion_dependencies(const annotations::annotation& o) const;

    /**
     * @brief Extract containing namespaces.
     */
    std::list<std::string>
    extract_containing_namespaces(const annotations::annotation& a) const;

public:
    /**
     * @brief Create the stitching settings.
     */
    stitching_properties make(const annotations::annotation& a) const;

private:
    const type_group type_group_;
};

} }

#endif

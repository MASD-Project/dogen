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
#ifndef DOGEN_CPP_TYPES_ANNOTATIONS_PATH_ANNOTATIONS_FACTORY_HPP
#define DOGEN_CPP_TYPES_ANNOTATIONS_PATH_ANNOTATIONS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_map>
#include <forward_list>
#include <boost/optional.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/quilt.cpp/types/annotations/path_annotations.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

/**
 * @brief Produces the path annotations for all formatters.
 */
class path_annotations_factory {
public:
    path_annotations_factory(const dynamic::repository& rp,
        const std::forward_list<
        std::shared_ptr<formatters::file_formatter_interface>>& formatters);

private:
    /**
     * @brief All relevant field definitions we need to remember for
     * each formatter.
     */
    struct field_definitions {
        std::string formatter_name;
        boost::optional<dynamic::field_definition> facet_directory;
        boost::optional<dynamic::field_definition> facet_postfix;
        dynamic::field_definition formatter_postfix;
        dynamic::field_definition header_file_extension;
        dynamic::field_definition implementation_file_extension;
        dynamic::field_definition include_directory_name;
        dynamic::field_definition source_directory_name;
        dynamic::field_definition disable_facet_directories;
    };

    /**
     * @brief Sets up top-level fields.
     */
    void setup_top_level_fields(const dynamic::repository& rp,
        field_definitions& fd) const;

    /**
     * @brief Sets up facet fields.
     */
    void setup_facet_fields(const dynamic::repository& rp,
        const std::string& facet_name, field_definitions& fd) const;

    /**
     * @brief Sets up formatter fields.
     */
    void setup_formatter_fields(const dynamic::repository& rp,
        const std::string& formatter_name,
        field_definitions& fp) const;

    /**
     * @brief Creates the set of field definitions for a given
     * formatter.
     */
    field_definitions make_field_definitions(
        const dynamic::repository& rp,
        const formatters::file_formatter_interface& f) const;

    /**
     * @brief Generates all of the formatter , using the
     * repository data and the registered formatters.
     */
    std::unordered_map<std::string, field_definitions>
    make_field_definitions(const dynamic::repository& rp,
        const std::forward_list<
            std::shared_ptr<formatters::file_formatter_interface>
        >& formatters) const;

private:
    /**
     * @brief Creates the path annotations for a given formatter.
     */
    path_annotations create_annotations_for_formatter(const field_definitions& fd,
        const dynamic::object& o) const;

public:
    /**
     * @brief Produce the global path annotations.
     *
     * @pre object must be the root object.
     */
    std::unordered_map<std::string, path_annotations>
    make(const dynamic::object& o) const;

private:
    const std::unordered_map<std::string, field_definitions>
    field_definitions_;
};

} } } }

#endif

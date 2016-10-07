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
#ifndef DOGEN_YARN_JSON_TYPES_HYDRATOR_HPP
#define DOGEN_YARN_JSON_TYPES_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {
namespace json {

/**
 * @brief Reads intermediate yarn models from a well-defined JSON
 * representation.
 */
class hydrator {
public:
    hydrator(const hydrator&) = default;
    hydrator(hydrator&&) = default;
    ~hydrator() noexcept = default;

public:
    explicit hydrator(const dynamic::workflow& w);

private:
    /**
     * @brief Returns the generation type for the model, depending on
     * whether it is a target model or not.
     */
    generation_types generation_type(const bool is_target) const;

    /**
     * @brief Reads the key value pairs from the property tree.
     */
    std::list<std::pair<std::string, std::string>>
    read_kvps(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Creates the dynamic object by reading meta-data from the
     * property tree.
     */
    dynamic::object create_dynamic_extensions(
        const std::list<std::pair<std::string, std::string>>& kvps,
        const dynamic::scope_types st) const;

    /**
     * @brief Reads an element from the property tree.
     */
    void read_element(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& m) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    intermediate_model read_stream(
        std::istream& s, const bool is_target) const;

    /**
     * @brief Converts a string to a value in the object types
     * enumeration.
     */
    object_types
    to_object_type(const boost::optional<std::string>& s) const;

public:
    /**
     * @brief Hydrates the model from the JSON stream.
     */
    intermediate_model hydrate(std::istream& s, const bool is_target) const;

    /**
     * @brief Opens up the file at path and then hydrates the model
     * from the JSON stream.
     */
    intermediate_model
    hydrate(const boost::filesystem::path& p, const bool is_target) const;

private:
    const dynamic::workflow dynamic_workflow_;
};

} } }

#endif

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
#ifndef DOGEN_TACK_JSON_TYPES_HYDRATOR_HPP
#define DOGEN_TACK_JSON_TYPES_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/tack/types/type.hpp"
#include "dogen/tack/types/model.hpp"

namespace dogen {
namespace tack_json {

/**
 * @brief Reads models from a well-defined JSON representation.
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
    tack::generation_types generation_type(const bool is_target) const;

    /**
     * @brief Returns the model name for all qnames other than the
     * model itself.
     *
     * This hack is required purely for the hardware model, which has
     * no model name for types, etc.
     */
    std::string model_name(const tack::model& m) const;

    /**
     * @brief Reads a module path from the property tree and uses it
     * to populate the qname.
     *
     * If the model does not contain all modules implied by the module
     * path, it adds them to the model.
     */
    void read_module_path(const boost::property_tree::ptree& pt,
        tack::model& m, tack::qname& qn) const;

    /**
     * @brief Creates the dynamic object by reading meta-data from the
     * property tree.
     */
    dynamic::object create_dynamic_extensions(
        const boost::property_tree::ptree& pt,
        const dynamic::scope_types st) const;

    /**
     * @brief Reads an element from the property tree.
     */
    void read_element(const boost::property_tree::ptree& pt,
        tack::model& m) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    tack::model read_stream(std::istream& s, const bool is_target) const;

    /**
     * @brief Converts a string to a value in the object types
     * enumeration.
     */
    tack::object_types
    to_object_type(const boost::optional<std::string>& s) const;

private:
    /**
     * @brief Perform all of the adjustments required to the model
     * such as generating inferred modules, etc.
     */
    void post_process(tack::model& m) const;

public:
    /**
     * @brief Hydrates the model from the JSON stream.
     */
    tack::model hydrate(std::istream& s) const;

    /**
     * @brief Opens up the file at path and then hydrates the model
     * from the JSON stream.
     */
    tack::model hydrate(const boost::filesystem::path& p) const;

private:
    const dynamic::workflow dynamic_workflow_;
};

} }

#endif

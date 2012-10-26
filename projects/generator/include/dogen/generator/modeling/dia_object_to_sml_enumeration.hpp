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
#ifndef DOGEN_GENERATOR_MODELING_DIA_OBJECT_TO_SML_ENUMERATION_HPP
#define DOGEN_GENERATOR_MODELING_DIA_OBJECT_TO_SML_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/dia/domain/object.hpp"
#include "dogen/sml/domain/qualified_name.hpp"
#include "dogen/sml/domain/enumeration.hpp"
#include "dogen/sml/domain/package.hpp"

namespace dogen {
namespace generator {
namespace modeling {

class dia_object_to_sml_enumeration {
public:
    dia_object_to_sml_enumeration() = delete;
    dia_object_to_sml_enumeration(const dia_object_to_sml_enumeration&) = default;
    ~dia_object_to_sml_enumeration() = default;
    dia_object_to_sml_enumeration(dia_object_to_sml_enumeration&&) = default;
    dia_object_to_sml_enumeration& operator=(const dia_object_to_sml_enumeration&) = default;

public:
    dia_object_to_sml_enumeration(const std::string& model_name,
        const std::list<std::string>& external_package_path,
        bool is_target, bool verbose);

public:
    bool is_processable(const dia::object& o) const;
    void add_object(const dia::object& o);

    std::unordered_map<sml::qualified_name, sml::enumeration>
    transform(std::unordered_map<std::string, sml::package> packages);

private:
    const std::string model_name_;
    const std::list<std::string> external_package_path_;
    const bool is_target_;
    const bool verbose_;
};

} } }

#endif

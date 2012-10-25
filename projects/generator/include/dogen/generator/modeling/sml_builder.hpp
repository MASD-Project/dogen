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
#ifndef DOGEN_GENERATOR_MODELING_SML_BUILDER_HPP
#define DOGEN_GENERATOR_MODELING_SML_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/sml/domain/model.hpp"

namespace dogen {
namespace generator {
namespace modeling {

class sml_builder {
public:
    sml_builder() = delete;
    sml_builder(const sml_builder&) = default;
    ~sml_builder() = default;
    sml_builder(sml_builder&&) = default;
    sml_builder& operator=(const sml_builder&) = default;

public:
    sml_builder(const bool verbose, const std::string& schema_name);

private:
    sml::qualified_name
    resolve_partial_type(sml::qualified_name t) const;
    std::vector<sml::property>
    resolve_properties(const sml::pod& pod);
    void resolve_parent(const sml::pod& pod);
    void resolve();
    void merge();

public:
    void add_target(sml::model model);
    void add(sml::model model);
    sml::model build();

private:
    std::string name_;
    std::list<sml::model> models_;
    sml::model merged_model_;
    const bool verbose_;
    bool has_target_;
    std::list<std::string> external_package_path_;
    const std::string schema_name_;
};

} } }

#endif

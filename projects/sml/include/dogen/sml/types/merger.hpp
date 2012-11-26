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
#ifndef DOGEN_GENERATOR_MODELING_MERGER_HPP
#define DOGEN_GENERATOR_MODELING_MERGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include "dogen/sml/types/nested_qualified_name.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

class merger {
public:
    merger() = delete;
    merger(const merger&) = default;
    ~merger() = default;
    merger(merger&&) = default;
    merger& operator=(const merger&) = default;

public:
    merger(const bool verbose, const std::string& schema_name);

private:
    void resolve_partial_type(nested_qualified_name& t) const;
    std::vector<property> resolve_properties(const pod& pod);
    void resolve_parent(const pod& pod);
    void resolve();
    std::unordered_map<std::string, reference> compute_dependencies() const;
    void combine();

public:
    void add_target(model model);
    void add(model model);
    model merge();

private:
    typedef std::unordered_map<std::string, model> models_type;

private:
    models_type models_;
    model merged_model_;
    const bool verbose_;
    bool has_target_;
    std::list<std::string> external_package_path_;
    const std::string schema_name_;
};

} }

#endif

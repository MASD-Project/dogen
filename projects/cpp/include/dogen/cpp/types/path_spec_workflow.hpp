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
#ifndef DOGEN_CPP_TYPES_PATH_SPEC_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_PATH_SPEC_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/registrar.hpp"
#include "dogen/cpp/types/path_spec_key.hpp"
#include "dogen/cpp/hash/path_spec_key_hash.hpp"
#include "dogen/cpp/types/path_spec_details.hpp"

namespace dogen {
namespace cpp {

class path_spec_workflow {
public:
    path_spec_workflow() = default;
    path_spec_workflow(const path_spec_workflow&) = delete;
    path_spec_workflow(path_spec_workflow&&) = default;
    ~path_spec_workflow() noexcept = default;

public:
    std::unordered_map<path_spec_key, path_spec_details>
    execute(const registrar& rg, const sml::model& m) const;
};

} }

#endif

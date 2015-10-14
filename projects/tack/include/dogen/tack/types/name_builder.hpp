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
#ifndef DOGEN_TACK_TYPES_NAME_BUILDER_HPP
#define DOGEN_TACK_TYPES_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/tack/types/name.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Builds a standard qualified name representation.
 */
class name_builder {
public:
    explicit name_builder(const bool building_model_name);

private:
    void create_qualified_name();

public:
    void add_model_name(const std::string& mn);
    void add_type_name(const std::string& tn);
    void add_external_module_path(const std::string& epp);
    void add_internal_module_path(const std::string& ipp);

public:
    name build();

private:
    const bool building_model_name_;
    name name_;
};

} }

#endif

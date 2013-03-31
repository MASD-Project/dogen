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
#ifndef DOGEN_CPP_TYPES_STD_MODEL_HELPER_HPP
#define DOGEN_CPP_TYPES_STD_MODEL_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/cpp/types/std_types.hpp"

namespace dogen {
namespace cpp {

class std_model_helper {
public:
    std_model_helper() = default;
    std_model_helper(const std_model_helper&) = default;
    ~std_model_helper() = default;
    std_model_helper(std_model_helper&&) = default;
    std_model_helper& operator=(const std_model_helper&) = default;

public:
    std::string model() const;
    std_types string_to_type(const std::string type) const;
    std::string type(const std_types type) const;
    bool is_primitive(const std::string s) const;
    std::string include(const std_types type) const;
};

} }

#endif

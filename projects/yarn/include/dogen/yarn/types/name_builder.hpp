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
#ifndef DOGEN_YARN_TYPES_NAME_BUILDER_HPP
#define DOGEN_YARN_TYPES_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/yarn/types/name.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Builds a name.
 */
class name_builder {
public:
    name_builder();
    explicit name_builder(const name& n);

private:
    void create_name_id();

public:
    name_builder& simple_name_contributes_to_qualifed_name(const bool v);
    name_builder& infer_simple_name_from_model_name(const bool v);

public:
    name_builder& simple_name(const std::string& sn);
    name_builder& model_name(const std::string& mn);
    name_builder& model_name(const yarn::location& l);
    name_builder& model_modules(const std::list<std::string>& mm);
    name_builder& internal_modules(const std::string& im);
    name_builder& internal_modules(const std::list<std::string>& im);
    name_builder& external_modules(const std::string& em);
    name_builder& external_modules(const std::list<std::string>& em);
    name_builder& location(const yarn::location& l);

public:
    name build();

private:
    bool simple_name_contributes_to_qualifed_name_;
    bool infer_simple_name_from_model_name_;
    name name_;
};

} }

#endif

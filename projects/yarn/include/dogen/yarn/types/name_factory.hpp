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
#ifndef DOGEN_YARN_TYPES_NAME_FACTORY_HPP
#define DOGEN_YARN_TYPES_NAME_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn/types/name.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Creates names with all the fields filled in.
 */
class name_factory {
public:
    /*
     * @brief Given a string with a model name, possibly using a
     * separator, and a string with an external module path, also
     * possibly using a separator; parses both strings and generates a
     * combined name.
     *
     * @pre @e model_name and @e module_path must not be empty.
     */
    name build_model_name(const std::string& model_name,
        const std::string& external_module_path) const;
};

} }

#endif

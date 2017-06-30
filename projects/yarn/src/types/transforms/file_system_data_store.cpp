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
#include "dogen/yarn/types/transforms/file_system_data_store.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

bool file_system_data_store::equals(const dogen::yarn::transforms::data_store_interface& other) const {
    const file_system_data_store* const p(dynamic_cast<const file_system_data_store* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool file_system_data_store::operator==(const file_system_data_store& /*rhs*/) const {
    return true;
}

} } }

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
#include <ostream>
#include "dogen.logical/io/transforms/context_io.hpp"
#include "dogen.physical/io/transforms/context_io.hpp"
#include "dogen.injection/io/transforms/context_io.hpp"
#include "dogen.generation/io/transforms/context_io.hpp"
#include "dogen.variability/io/transforms/context_io.hpp"
#include "dogen.orchestration/io/transforms/context_io.hpp"

namespace dogen::orchestration::transforms {

std::ostream& operator<<(std::ostream& s, const context& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::orchestration::transforms::context\"" << ", "
      << "\"variability_context\": " << v.variability_context() << ", "
      << "\"injection_context\": " << v.injection_context() << ", "
      << "\"assets_context\": " << v.assets_context() << ", "
      << "\"generation_context\": " << v.generation_context() << ", "
      << "\"extraction_context\": " << v.extraction_context()
      << " }";
    return(s);
}

}

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
#include "masd.dogen.orchestration/types/transforms/context.hpp"

namespace masd::dogen::orchestration::transforms {

context::context(
    const masd::dogen::injection::transforms::context& injection_context,
    const masd::dogen::coding::transforms::context& coding_context,
    const masd::dogen::generation::transforms::context& generation_context)
    : injection_context_(injection_context),
      coding_context_(coding_context),
      generation_context_(generation_context) { }

const masd::dogen::injection::transforms::context& context::injection_context() const {
    return injection_context_;
}

const masd::dogen::coding::transforms::context& context::coding_context() const {
    return coding_context_;
}

const masd::dogen::generation::transforms::context& context::generation_context() const {
    return generation_context_;
}

}

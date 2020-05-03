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
#include "dogen.text.cpp/types/transforms/context.hpp"

namespace dogen::text::cpp::transforms {

context::context(
    const std::unordered_set<text::entities::element_archetype>&
    enabled_archetype_for_element,
    const formattables::element_properties& element_properties,
    const formattables::model& fm,
    const std::unordered_map<std::string, std::unordered_map<std::string,
    std::list<std::shared_ptr<helper_transform>>>>& helpers)
    : enabled_archetype_for_element_(enabled_archetype_for_element),
      element_properties_(element_properties), model_(fm),
      helpers_(helpers) { }

const std::unordered_set<text::entities::element_archetype>&
context::enabled_archetype_for_element() const {
    return enabled_archetype_for_element_;
}

const formattables::element_properties&
context::element_properties() const {
    return element_properties_;
}

const formattables::model& context::model() const {
    return model_;
}

const std::unordered_map<
    std::string,
    std::unordered_map<
        std::string, std::list<std::shared_ptr<helper_transform>>>>&
context::helpers() const {
    return helpers_;
}

}

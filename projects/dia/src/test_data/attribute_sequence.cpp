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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen/dia/test_data/color_sequence.hpp"
#include "dogen/dia/test_data/real_sequence.hpp"
#include "dogen/dia/test_data/boolean_sequence.hpp"
#include "dogen/dia/test_data/composite_sequence.hpp"
#include "dogen/dia/test_data/attribute_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {
namespace detail {

simple_attribute_generator::value_type
simple_attribute_generator::next_term(const unsigned int position) {
    if (position == 0) {
        color_sequence sequence;
        return dogen::dia::attribute("background", sequence());
    } else if (position == 1) {
        real_sequence sequence;
        return dogen::dia::attribute("pagebreak", sequence());
    }

    boolean_sequence sequence;
    return dogen::dia::attribute("is_portrait", sequence());
}

composite_attribute_generator::value_type
composite_attribute_generator::next_term(const unsigned int position) {
    std::vector<dogen::dia::composite> composites;
    std::string name;

    if (position == 0)
        name = "composite_0";
    else if (position == 1)
        name = "composite_1";
    else
        name = "composite_2";

    simple_composite_sequence sequence;
    composites.push_back(sequence());
    return dogen::dia::attribute(name, composites);
}

} } } }

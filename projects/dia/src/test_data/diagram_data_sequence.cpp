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
#include "dogen/dia/test_data/attribute_sequence.hpp"
#include "dogen/dia/test_data/diagram_data_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {
namespace detail {

diagram_data_generator::value_type
diagram_data_generator::next_term(const unsigned int position) {
    std::vector<dogen::dia::attribute> attributes;
    simple_attribute_sequence sequence;

    if (position == 0) {
        attributes.push_back(sequence());
        return dogen::dia::diagram_data(attributes);
    } else if (position == 1) {
        sequence();
        attributes.push_back(sequence());
        return dogen::dia::diagram_data(attributes);
    }
    sequence();
    sequence();
    attributes.push_back(sequence());
    return dogen::dia::diagram_data(attributes);
}

} } } }

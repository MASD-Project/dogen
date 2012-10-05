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
#include "dogen/dia/test_data/diagram_sequence.hpp"
#include "dogen/dia/test_data/diagram_data_sequence.hpp"
#include "dogen/dia/test_data/layer_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {
namespace detail {

diagram_generator::value_type
diagram_generator::next_term(const unsigned int position) {
    std::vector<dogen::dia::layer> layers;
    diagram_data_sequence sequence;
    layer_sequence sequence2;

    if (position == 0) {
        layers.push_back(sequence2());
        return dogen::dia::diagram(sequence(), layers);
    } else if (position == 1) {
        sequence();
        sequence2();
        layers.push_back(sequence2());
        return dogen::dia::diagram(sequence(), layers);
    }
    return dogen::dia::diagram(sequence(), layers);
}

} } } }

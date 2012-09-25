/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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

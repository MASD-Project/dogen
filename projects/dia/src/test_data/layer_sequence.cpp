/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/dia/test_data/layer_sequence.hpp"
#include "dogen/dia/test_data/object_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {
namespace detail {

layer_generator::value_type
layer_generator::next_term(const unsigned int position) {
    std::vector<dogen::dia::object> objects;
    object_sequence sequence;

    if (position == 0) {
        objects.push_back(sequence());
        return dogen::dia::layer("layer0", true, true, objects);
    } else if (position == 1) {
        objects.push_back(sequence());
        return dogen::dia::layer("layer1", true, false, objects);
    }
    objects.push_back(sequence());
    return dogen::dia::layer("layer2", false, false, objects);
}

} } } }

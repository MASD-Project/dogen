/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/dia/test_data/child_node_sequence.hpp"
#include "dogen/dia/test_data/attribute_sequence.hpp"
#include "dogen/dia/test_data/object_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {
namespace detail {

object_generator::value_type
object_generator::next_term(const unsigned int position) {
    std::vector<dogen::dia::attribute> attributes;
    simple_attribute_sequence sequence;
    child_node_sequence sequence2;

    if (position == 0) {
        attributes.push_back(sequence());
        return dogen::dia::object(
            "UML - LargePackage", position, "O0", attributes,
            boost::optional<dogen::dia::child_node>());
    } else if (position == 1) {
        sequence();
        attributes.push_back(sequence());
        return dogen::dia::object(
            "UML - Class", position, "O1", attributes,
            boost::optional<dogen::dia::child_node>(sequence2()));
    }

    sequence();
    sequence();
    attributes.push_back(sequence());
    return dogen::dia::object(
        "UML - LargePackage", position, "O2", attributes,
        boost::optional<dogen::dia::child_node>(sequence2()));
}

} } } }

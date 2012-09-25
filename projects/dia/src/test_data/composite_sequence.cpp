/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/dia/test_data/composite_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {
namespace detail {

simple_composite_generator::value_type
simple_composite_generator::next_term(const unsigned int position) {
    typedef boost::shared_ptr<dogen::dia::attribute> attribute_ptr;
    std::vector<attribute_ptr> attributes;
    simple_attribute_sequence sequence;
    boost::shared_ptr<composite> inner_composite(new composite());
    std::string type;

    if (position == 0) {
        type = "paper";
        inner_composite->type("position0");
        attributes.push_back(
            attribute_ptr(new dogen::dia::attribute(sequence())));
    } else if (position == 1) {
        type = "grid";
        inner_composite->type("position1");
        sequence();
        attributes.push_back(
            attribute_ptr(new dogen::dia::attribute(sequence())));
    } else {
        type = "dict";
        inner_composite->type("position2");
    }
    return dogen::dia::composite(type, attributes, inner_composite);
}

composite_composite_generator::value_type
composite_composite_generator::next_term(const unsigned int position) {
    typedef boost::shared_ptr<dogen::dia::attribute> attribute_ptr;
    std::vector<attribute_ptr> attributes;
    composite_attribute_sequence sequence;
    boost::shared_ptr<composite> inner_composite(new composite());
    std::string type;

    if (position == 0) {
        type = "paper";
        inner_composite->type("position0");
        attributes.push_back(
            attribute_ptr(new dogen::dia::attribute(sequence())));
    } else if (position == 1) {
        type = "grid";
        inner_composite->type("position1");
        sequence();
        attributes.push_back(
            attribute_ptr(new dogen::dia::attribute(sequence())));
    } else {
        type = "dict";
        inner_composite->type("position1");
    }
    return dogen::dia::composite(type, attributes, inner_composite);
}

} } } }

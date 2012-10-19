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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen/dia/test_data/composite_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {
namespace detail {

simple_composite_generator::result_type
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

composite_composite_generator::result_type
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

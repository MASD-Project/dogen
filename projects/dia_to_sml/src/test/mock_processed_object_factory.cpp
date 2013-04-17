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
#include <string>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/test/mock_processed_object_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia.mock_processed_object_factory"));

const std::string empty;
const std::string object_prefix("O");
const std::string uml_large_package("UML - LargePackage");
const std::string uml_class("UML - Class");
const std::string uml_generalization("UML - Generalization");
const std::string uml_association("UML - Association");
const std::string uml_note("UML - Note");
const std::string uml_message("UML - Message");
const std::string uml_realization("UML - Realizes");
const std::string dia_stereotype("stereotype");
const std::string dia_name("name");
const std::string enumeration_stereotype("#enumeration#");
const std::string invalid_stereotype("Invalid stereotype: ");

using dogen::dia_to_sml::processed_object;
using dogen::dia_to_sml::test::mock_processed_object_factory;

processed_object
create_object(const dogen::dia_to_sml::object_types ot, const unsigned int n) {
    processed_object r;
    r.id(mock_processed_object_factory::to_oject_id(n));
    r.object_type(ot);
    return r;
}

void create_name(processed_object& o, const unsigned int n) {
    std::ostringstream s;
    s << "name_" << n;
    o.name(s.str());
}

processed_object create_named_object(const dogen::dia_to_sml::object_types ot,
    const unsigned int n) {
    processed_object r(create_object(ot, n));
    create_name(r, n);
    return r;
}

}

namespace dogen {
namespace dia_to_sml {
namespace test {

std::string mock_processed_object_factory::to_oject_id(const unsigned int n) {
    return object_prefix + boost::lexical_cast<std::string>(n);
}

processed_object mock_processed_object_factory::
build_uml_note(const unsigned int n) {
    processed_object r(create_object(object_types::uml_note, n));
    r.stereotype(stereotypes::no_stereotype);

    std::ostringstream s;
    s << "this is a comment";
    r.text(s.str());
    return r;
}

processed_object mock_processed_object_factory::
build_uml_note_with_marker(const unsigned int n) {
    processed_object r(create_object(object_types::uml_note, n));
    r.stereotype(stereotypes::no_stereotype);
    std::ostringstream s;
    s << "#DOGEN COMMENT=true" << std::endl << std::endl
      << "this is a doxygen brief";
    r.text(s.str());
    return r;
}

processed_object mock_processed_object_factory::
build_empty_uml_note(const unsigned int n) {
    processed_object r(create_object(object_types::uml_note, n));
    r.stereotype(stereotypes::no_stereotype);
    return r;
}

processed_object mock_processed_object_factory::
build_class(const unsigned int n) {
    processed_object r(create_named_object(object_types::uml_class, n));
    r.stereotype(stereotypes::no_stereotype);
    return r;
}

processed_object mock_processed_object_factory::
build_empty_named_class(const unsigned int n) {
    processed_object r(create_object(object_types::uml_class, n));
    r.stereotype(stereotypes::no_stereotype);
    return r;
}

processed_object mock_processed_object_factory::
build_large_package(const unsigned int n) {
    return create_named_object(object_types::uml_large_package, n);
}

std::array<processed_object, 2> mock_processed_object_factory::
build_class_inside_large_package(unsigned int n)  {
    std::array<processed_object, 2> r = {{
            build_large_package(n),
            build_class(++n),
        }};

    r[1].child_node_id(r[0].id());
    return r;
}

std::array<processed_object, 3> mock_processed_object_factory::
build_class_inside_two_large_packages(unsigned int n)  {
    std::array<processed_object, 3> r = {{
            build_large_package(n),
            build_large_package(++n),
            build_class(++n),
        }};

    r[1].child_node_id(r[0].id());
    r[2].child_node_id(r[1].id());
    return r;
}

processed_object mock_processed_object_factory::build_stereotyped_class(
    const stereotypes st, const unsigned int n) {
    processed_object r(create_named_object(object_types::uml_class, n));
    r.stereotype(st);
    return r;
}

std::array<processed_object, 3>
mock_processed_object_factory::build_generalization(unsigned int n) {
    std::array<processed_object, 3> r = {{
            create_object(object_types::uml_generalization, n),
            build_class(++n),
            build_class(++n),
        }};
    r[2].connection(std::make_pair(r[0].id(), r[1].id()));
    return r;
}

std::array<processed_object, 3>
mock_processed_object_factory::build_association(unsigned int n) {
    std::array<processed_object, 3> r = {{
            build_class(n),
            build_class(++n),
            create_object(object_types::uml_association, ++n)
        }};

    r[2].connection(std::make_pair(r[0].id(), r[1].id()));
    return r;
}

std::array<processed_object, 4> mock_processed_object_factory::
build_generalization_inside_large_package(unsigned int n)  {
    std::array<processed_object, 4> r = {{
            build_large_package(n),
            build_class(++n),
            build_class(++n),
            create_object(object_types::uml_generalization, ++n)
        }};

    r[3].connection(std::make_pair(r[1].id(), r[2].id()));

    r[1].child_node_id(r[0].id());
    r[2].child_node_id(r[0].id());
    r[3].child_node_id(r[0].id());
    return r;
}

std::array<processed_object, 4> mock_processed_object_factory::
build_first_degree_cycle(unsigned int n) {
    std::array<processed_object, 4> r = {{
            build_class(n),
            build_class(++n),
            create_object(object_types::uml_generalization, ++n),
            create_object(object_types::uml_generalization, ++n)
        }};

    r[2].connection(std::make_pair(r[0].id(), r[1].id()));
    r[3].connection(std::make_pair(r[1].id(), r[0].id()));
    return r;
}


} } }

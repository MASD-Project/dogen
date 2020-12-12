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
#include <string>
#include <boost/lexical_cast.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.dia/types/entities/attribute_fwd.hpp"
#include "dogen.dia/types/entities/connection.hpp"
#include "dogen.dia/types/entities/child_node.hpp"
#include "dogen.dia/test/mock_object_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia.test.mock_object_factory"));

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
const std::string dia_text("text");
const std::string dia_comment("comment");
const std::string dia_comment_value("this is a comment");
const std::string dia_string("string");
const std::string enumeration_stereotype("#enumeration#");
const std::string invalid_stereotype("Invalid stereotype: ");

dogen::dia::entities::attribute
create_string_attribute(const std::string& name, const std::string& value) {
    dogen::dia::entities::attribute r;
    r.name(name);

    std::ostringstream s;
    s << "#" << value << "#";

    dogen::dia::entities::string v;
    v.value(s.str());
    r.values().push_back(v);

    return r;
}

dogen::dia::entities::object
create_object(const std::string& type, const unsigned int number) {
    dogen::dia::entities::object r;
    r.id(dogen::dia::test::mock_object_factory::to_oject_id(number));
    r.type(type);
    return r;
}

void create_name_attribute(dogen::dia::entities::object& o,
    const std::string& value) {
    o.attributes().push_back(create_string_attribute(dia_name, value));
}

void create_name_attribute(dogen::dia::entities::object& o, const unsigned int number) {
    std::ostringstream s;
    s << "name_" << number;
    create_name_attribute(o, s.str());
}

void create_comment_attribute(dogen::dia::entities::object& o) {
    const auto sa(create_string_attribute(dia_comment, dia_comment_value));
    o.attributes().push_back(sa);
}

void create_stereotype_attribute(dogen::dia::entities::object& o,
    const std::string st) {
    o.attributes().push_back(create_string_attribute(dia_stereotype, st));
}

dogen::dia::entities::object
create_named_object(const std::string& type, const unsigned int number) {
    dogen::dia::entities::object r(create_object(type, number));
    create_name_attribute(r, number);
    return r;
}

dogen::dia::entities::connection create_connection(const std::string& id) {
    dogen::dia::entities::connection r;
    r.to(id);
    return r;
}

}

namespace dogen::dia::test {

using dogen::dia::entities::object;
using dogen::dia::entities::connection;
using dogen::dia::entities::child_node;
using dogen::dia::entities::attribute;
using dogen::dia::entities::composite;

std::string mock_object_factory::to_oject_id(const unsigned int number) {
    return object_prefix + boost::lexical_cast<std::string>(number);
}

object mock_object_factory::make_uml_note(const unsigned int number) {
    std::ostringstream ss;
    ss << "#DOGEN masd.codec.dia.comment=true" << std::endl << std::endl
       << "this is a comment." << std::endl;

    dogen::dia::entities::string s(ss.str());
    boost::shared_ptr<attribute> ap(new attribute);
    ap->values().push_back(s);
    ap->name(dia_string);

    composite c;
    c.type(dia_text);
    c.value().push_back(ap);

    attribute a;
    a.name(dia_text);
    a.values().push_back(c);

    object r(create_object(uml_note, number));
    r.attributes().push_back(a);
    create_stereotype_attribute(r, empty);
    return r;
}

object mock_object_factory::make_class(const unsigned int number) {
    object r(create_named_object(uml_class, number));
    create_comment_attribute(r);
    create_stereotype_attribute(r, empty);
    return r;
}

object mock_object_factory::make_no_name_class(const unsigned int number) {
    object r(create_object(uml_class, number));
    create_stereotype_attribute(r, empty);
    return r;
}

object mock_object_factory::make_blank_name_class(const unsigned int number) {
    object r(create_object(uml_class, number));
    create_stereotype_attribute(r, empty);
    create_name_attribute(r, empty);
    return r;
}

object mock_object_factory::make_large_package(const unsigned int number) {
    return create_named_object(uml_large_package, number);
}

std::array<object, 2> mock_object_factory::
make_class_inside_large_package(unsigned int number)  {
    std::array<object, 2> r = {{
            make_large_package(number),
            make_class(++number),
        }};

    const child_node cn(r[0].id());
    r[1].child_node(cn);
    return r;
}

std::array<object, 3> mock_object_factory::
make_class_inside_two_large_packages(unsigned int number)  {
    std::array<object, 3> r = {{
            make_large_package(number),
            make_large_package(++number),
            make_class(++number),
        }};

    const child_node cn(r[0].id());
    r[1].child_node(cn);

    const child_node cn2(r[1].id());
    r[2].child_node(cn2);

    return r;
}

object mock_object_factory::make_stereotyped_class(
    const std::string& st, const unsigned int number) {
    object r(create_named_object(uml_class, number));
    create_comment_attribute(r);
    create_stereotype_attribute(r, st);
    return r;
}

std::array<object, 3>
mock_object_factory::make_generalization(unsigned int number) {
    std::array<object, 3> r = {{
            create_object(uml_generalization, number),
            make_class(++number),
            make_class(++number),
        }};

    r[0].connections(
        std::vector<connection> {
            create_connection(r[1].id()), create_connection(r[2].id())});

    return r;
}

std::array<object, 3>
mock_object_factory::make_association(unsigned int number) {
    std::array<object, 3> r = {{
            make_class(number),
            make_class(++number),
            create_object(uml_association, ++number)
        }};

    r[2].connections(
        std::vector<connection> {
            create_connection(r[0].id()), create_connection(r[1].id())});

    return r;
}

std::array<object, 4> mock_object_factory::
make_generalization_inside_large_package(unsigned int number)  {
    std::array<object, 4> r = {{
            make_large_package(number),
            make_class(++number),
            make_class(++number),
            create_object(uml_generalization, ++number)
        }};

    r[3].connections(
        std::vector<connection> {
            create_connection(r[1].id()), create_connection(r[2].id())});

    const child_node cn(r[0].id());
    r[1].child_node(cn);
    r[2].child_node(cn);
    r[3].child_node(cn);

    return r;
}

std::array<object, 4> mock_object_factory::
make_first_degree_cycle(unsigned int number) {
    std::array<object, 4> r = {{
            make_class(number),
            make_class(++number),
            create_object(uml_generalization, ++number),
            create_object(uml_generalization, ++number)
        }};

    r[2].connections(
        std::vector<connection> {
            create_connection(r[0].id()), create_connection(r[1].id())});

    r[3].connections(
        std::vector<connection> {
            create_connection(r[1].id()), create_connection(r[0].id())});

    return r;
}

}

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
#include "dogen.codec/test/mock_object_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia.mock_object_factory"));

const std::string empty;
const std::string object_prefix("O");
const std::string doxygen_comment("this is a doxygen brief");
const std::string note_text("this is a comment");
const std::string instruction_key("masd.codec.dia.comment");
const std::string instruction_value("true");
const std::string uml_large_package("UML - LargePackage");
const std::string uml_class("UML - Class");
const std::string uml_generalization("UML - Generalization");
const std::string uml_association("UML - Association");
const std::string uml_note("UML - Note");
const std::string uml_message("UML - Message");
const std::string uml_realization("UML - Realizes");
const std::string unsigned_int("unsigned int");

using dogen::codec::entities::object;
using dogen::codec::entities::attribute;
using dogen::codec::test::mock_object_factory;

object create_object(const std::string ot,
    const unsigned int n) {
    object r;
    r.id(mock_object_factory::to_oject_id(n));
    r.object_type(ot);
    return r;
}

std::string name(const unsigned int n) {
    std::ostringstream s;
    s << "name_" << n;
    return s.str();
}

object create_named_object(const std::string& ot, const unsigned int n) {
    object r(create_object(ot, n));
    r.name(name(n));
    return r;
}

attribute create_processed_attribute(const unsigned int n) {
    attribute r;
    r.name().simple(name(n));
    r.type(unsigned_int);
    r.comment().documentation(doxygen_comment);
    r.comment().original_content(doxygen_comment);
    return r;
}

}

namespace dogen::codec::test {

std::string mock_object_factory::to_oject_id(const unsigned int n) {
    return object_prefix + boost::lexical_cast<std::string>(n);
}

std::string
mock_object_factory::to_object_name(const unsigned int n) {
    return ::name(n);
}

object mock_object_factory::
make_uml_message(const unsigned int n) {
    object r(create_object(uml_message, n));
    return r;
}

object mock_object_factory::
make_uml_note(const unsigned int n) {
    object r(create_object(uml_note, n));
    r.comment().documentation(note_text);
    r.comment().original_content(note_text);
    return r;
}

object mock_object_factory::
make_uml_note_with_marker(const unsigned int n) {
    object r(create_object(uml_note, n));
    std::ostringstream s;
    s << "#DOGEN masd.codec.dia.comment=true" << std::endl << std::endl
      << doxygen_comment;
    r.comment().documentation(doxygen_comment);
    r.comment().original_content(s.str());
    r.comment().applies_to_container(true);
    identification::entities::tagged_value tv;
    tv.tag(instruction_key);
    tv.value(instruction_value);
    r.comment().tagged_values().push_back(tv);
    return r;
}

object mock_object_factory::
make_empty_uml_note(const unsigned int n) {
    object r(create_object(uml_note, n));
    return r;
}

std::array<object, 2> mock_object_factory::
make_uml_note_inside_large_package(unsigned int n) {
    std::array<object, 2> r = {{
            make_large_package(n),
            make_uml_note(++n),
        }};

    r[1].container_id(r[0].id());
    return r;
}

std::array<object, 2> mock_object_factory::
make_empty_uml_note_inside_large_package(unsigned int n) {
    std::array<object, 2> r = {{
            make_large_package(n),
            make_empty_uml_note(++n)
        }};

    r[1].container_id(r[0].id());
    return r;
}

std::array<object, 2> mock_object_factory::
make_uml_note_with_marker_inside_large_package(unsigned int n) {
    std::array<object, 2> r = {{
            make_large_package(n),
            make_uml_note_with_marker(++n)
        }};

    r[1].container_id(r[0].id());
    return r;
}

object mock_object_factory::
make_class(const unsigned int n, const std::string& st) {
    auto r(create_named_object(uml_class, n));
    r.stereotypes(st);
    r.comment().documentation(doxygen_comment);
    r.comment().original_content(doxygen_comment);
    return r;
}

object mock_object_factory::
make_class_with_attribute(const unsigned int n, const std::string& st) {
    auto r(make_class(n, st));
    r.attributes().push_back(create_processed_attribute(n));
    return r;
}

object mock_object_factory::
make_empty_named_class(const unsigned int n) {
    object r(create_object(uml_class, n));
    return r;
}

object mock_object_factory::
make_large_package(const unsigned int n) {
    auto r(create_named_object(uml_large_package, n));
    r.comment().documentation(doxygen_comment);
    return r;
}

std::array<object, 2> mock_object_factory::
make_class_inside_large_package(unsigned int n, const std::string& st) {
    std::array<object, 2> r = {{
            make_large_package(n),
            make_class(++n, st),
        }};

    r[1].container_id(r[0].id());
    return r;
}

std::array<object, 3> mock_object_factory::
make_class_inside_two_large_packages(unsigned int n, const std::string& st)  {
    std::array<object, 3> r = {{
            make_large_package(n),
            make_large_package(++n),
            make_class(++n, st),
        }};

    r[1].container_id(r[0].id());
    r[2].container_id(r[1].id());
    return r;
}

std::array<object, 3>
mock_object_factory::
make_realization(unsigned int n, const std::string& st) {
    std::array<object, 3> r = {{
            create_object(uml_realization, n),
            make_class(++n, st),
            make_class(++n, st),
        }};
    r[0].connection(std::make_pair(r[1].id(), r[2].id()));
    return r;
}

std::array<object, 3>
mock_object_factory::
make_generalization(unsigned int n, const std::string& st) {
    std::array<object, 3> r = {{
            create_object(uml_generalization, n),
            make_class(++n, st),
            make_class(++n, st),
        }};
    r[0].connection(std::make_pair(r[1].id(), r[2].id()));
    return r;
}

std::array<object, 3>
mock_object_factory::
make_association(unsigned int n, const std::string& st) {
    std::array<object, 3> r = {{
            make_class(n),
            make_class(++n, st),
            create_object(uml_association, ++n)
        }};

    r[2].connection(std::make_pair(r[0].id(), r[1].id()));
    return r;
}

std::array<object, 4> mock_object_factory::
make_generalization_inside_large_package(
    unsigned int n, const std::string& st)  {
    std::array<object, 4> r = {{
            make_large_package(n),
            make_class(++n, st),
            make_class(++n, st),
            create_object(uml_generalization, ++n)
        }};

    r[3].connection(std::make_pair(r[1].id(), r[2].id()));

    r[1].container_id(r[0].id());
    r[2].container_id(r[0].id());
    r[3].container_id(r[0].id());
    return r;
}

std::array<object, 4> mock_object_factory::
make_first_degree_cycle(unsigned int n) {
    std::array<object, 4> r = {{
            make_class(n),
            make_class(++n),
            create_object(uml_generalization, ++n),
            create_object(uml_generalization, ++n)
        }};

    r[2].connection(std::make_pair(r[0].id(), r[1].id()));
    r[3].connection(std::make_pair(r[1].id(), r[0].id()));
    return r;
}

}

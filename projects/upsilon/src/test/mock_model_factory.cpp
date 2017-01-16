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
#include "dogen/utility/log/logger.hpp"
#include "dogen/upsilon/test/mock_model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("upsilon.mock_model_factory"));

/*
 * Match yarn mock names.
 */
const std::string model_name_prefix("some_model_");
const std::string type_name_prefix("some_type_");
const std::string field_name_prefix("some_attribute_");
const std::string documentation("Some documentation");
const std::string unsigned_int("unsigned int");

std::string type_name(const unsigned int i) {
    std::ostringstream stream;
    stream << type_name_prefix << i;
    return stream.str();
}

std::string field_name(const unsigned int i) {
    std::ostringstream stream;
    stream << field_name_prefix << i;
    return stream.str();
}

std::string schema_name(const unsigned int i) {
    std::ostringstream stream;
    stream << model_name_prefix << i;
    return stream.str();
}

}

namespace dogen {
namespace upsilon {
namespace test {

name mock_model_factory::make_name(const unsigned int n) {
    name r;
    r.value(::type_name(n));
    r.schema_name(::schema_name(0));
    return r;
}

primitive mock_model_factory::make_primitive(const unsigned int n) {
    primitive r;
    r.name(make_name(n));
    r.comment(documentation);
    return r;
}

compound mock_model_factory::make_compound(const unsigned int n) {
    compound r;
    r.name(make_name(n));
    r.comment(documentation);
    return r;
}

compound mock_model_factory::make_compound_with_field(const unsigned int n) {
    compound r;
    r.name(make_name(n));
    r.comment(documentation);

    field f;
    f.name(field_name(n));
    f.comment(documentation);

    name tn;
    tn.value(unsigned_int);
    f.type_name(tn);

    r.fields().push_back(f);

    return r;
}

} } }

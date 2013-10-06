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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/test/building_error.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.mock_model_factory"));

const std::string model_name_prefix("some_model_");
const std::string simple_name_prefix("some_type_");
const std::string property_name_prefix("some_property_");
const std::string module_name_prefix("some_module_");

const std::string boolean("bool");
const std::string unsigned_int("unsigned int");

const std::string documentation("Some documentation");

const std::string invalid_property_type("Unknown property type.");
const std::string invalid_object_type("Invalid or unsupported object type.");

std::string simple_name(unsigned int i) {
    std::ostringstream stream;
    stream << simple_name_prefix << i;
    return stream.str();
}

std::string model_name(unsigned int i) {
    std::ostringstream stream;
    stream << model_name_prefix << i;
    return stream.str();
}

std::string property_name(unsigned int i) {
    std::ostringstream stream;
    stream << property_name_prefix << i;
    return stream.str();
}

std::string module_name(unsigned int i) {
    std::ostringstream stream;
    stream << module_name_prefix << i;
    return stream.str();
}

dogen::sml::nested_qname mock_qname(const dogen::sml::abstract_object& o) {
    dogen::sml::qname qn;
    qn.simple_name(o.name().simple_name());
    qn.model_name(o.name().model_name());

    dogen::sml::nested_qname r;
    r.type(qn);
    return r;
}

dogen::sml::qname mock_model_qname(unsigned int i) {
    dogen::sml::qname r;
    r.model_name(model_name(i));
    return r;
}

dogen::sml::nested_qname
mock_qname_shared_ptr(const dogen::sml::type& o) {
    dogen::sml::qname e;
    e.simple_name("shared_ptr");
    e.model_name("boost");

    dogen::sml::nested_qname r;
    r.type(e);

    dogen::sml::nested_qname c;
    c.type(o.name());

    r.children(std::list<dogen::sml::nested_qname> { c });

    return r;
}

dogen::sml::nested_qname mock_nested_qname(
    dogen::sml::test::mock_model_factory::property_types pt) {
    using namespace dogen::sml;

    qname qn;
    nested_qname r;

    typedef test::mock_model_factory::property_types property_types;
    switch(pt) {
    case property_types::unsigned_int:
        qn.simple_name(unsigned_int);
        r.type(qn);
        break;
    case property_types::boolean:
        qn.simple_name(boolean);
        r.type(qn);
        break;
    case property_types::boost_variant: {
        qname e;
        e.simple_name("variant");
        e.model_name("boost");
        r.type(e);

        qname f;
        f.simple_name(boolean);
        nested_qname c;
        c.type(f);

        qname g;
        g.simple_name(unsigned_int);
        nested_qname d;
        d.type(g);
        r.children(std::list<nested_qname> { c, d });
        break;
    }
    case property_types::std_string:
        qn.simple_name("string");
        qn.model_name("std");
        r.type(qn);
        break;
    case property_types::std_pair: {
        qname e;
        e.simple_name("pair");
        e.model_name("std");
        r.type(e);

        qname f;
        f.simple_name(boolean);
        nested_qname c;
        c.type(f);

        qname g;
        g.simple_name(boolean);
        nested_qname d;
        d.type(g);
        r.children(std::list<nested_qname> { c, d });
        break;
    }
    default:
        BOOST_LOG_SEV(lg, error) << invalid_property_type;
        BOOST_THROW_EXCEPTION(test::building_error(invalid_property_type));
    }
    return r;
}

void populate_object(dogen::sml::abstract_object& o, const unsigned int i,
    const dogen::sml::qname& model_qname, const unsigned int module_n) {

    dogen::sml::qname qn;
    qn.model_name(model_qname.model_name());
    qn.simple_name(simple_name(i));

    for (unsigned int i(0); i < module_n; ++i)
        qn.module_path().push_back(module_name(i));

    o.name(qn);
    o.generation_type(dogen::sml::generation_types::full_generation);
    o.documentation(documentation);
    o.origin_type(dogen::sml::origin_types::user);
}

void populate_simple_model_properties(dogen::sml::model& m, const unsigned int n) {
    m.name(mock_model_qname(n));
    m.documentation(documentation);
    m.origin_type(dogen::sml::origin_types::user);
    m.generation_type(dogen::sml::generation_types::full_generation);
}

boost::shared_ptr<dogen::sml::abstract_object>
mock_value_object(const unsigned int i, const dogen::sml::qname& model_qname,
    const unsigned int module_n = 0) {

    using dogen::sml::value_object;
    auto r(boost::make_shared<value_object>());
    populate_object(*r, i, model_qname, module_n);
    r->type(dogen::sml::value_object_types::plain);
    return r;
}

boost::shared_ptr<dogen::sml::abstract_object>
mock_entity(const dogen::sml::property& prop, const bool keyed,
    const unsigned int i, const dogen::sml::qname& model_qname,
    const unsigned int module_n = 0) {

    using namespace dogen::sml;
    boost::shared_ptr<abstract_entity> r;
    if (keyed)
        r = boost::shared_ptr<abstract_entity>(new keyed_entity());
    else
        r = boost::shared_ptr<abstract_entity>(new entity());

    populate_object(*r, i, model_qname, module_n);
    r->identity().push_back(prop);
    return r;
}

boost::shared_ptr<dogen::sml::abstract_object>
mock_value_object(unsigned int i, const unsigned int module_n = 0) {
    return mock_value_object(i, mock_model_qname(i), module_n);
}

dogen::sml::enumeration
mock_enumeration(const unsigned int i, const dogen::sml::qname& model_qname,
    const unsigned int module_n = 0) {
    dogen::sml::qname qn;
    qn.model_name(model_qname.model_name());
    qn.simple_name(simple_name(i));

    for (unsigned int i(0); i < module_n; ++i)
        qn.module_path().push_back(module_name(i));

    dogen::sml::enumeration r;
    r.name(qn);
    r.generation_type(dogen::sml::generation_types::full_generation);
    r.documentation(documentation);

    dogen::sml::qname uqn;
    uqn.simple_name(unsigned_int);
    r.underlying_type(uqn);

    const auto lambda([](const unsigned int n) -> dogen::sml::enumerator {
            dogen::sml::enumerator r;
            r.name(simple_name(n));
            r.value(boost::lexical_cast<std::string>(n));
            return r;
        });

    r.enumerators().push_back(lambda(0));
    r.enumerators().push_back(lambda(1));
    return r;
}

boost::shared_ptr<dogen::sml::abstract_object>
mock_exception(const unsigned int i, const dogen::sml::qname& model_qname,
    const unsigned int module_n = 0) {
    dogen::sml::qname qn;
    qn.model_name(model_qname.model_name());
    qn.simple_name(simple_name(i));

    for (unsigned int i(0); i < module_n; ++i)
        qn.module_path().push_back(module_name(i));

    using dogen::sml::value_object;
    boost::shared_ptr<value_object> r(new value_object());
    r->name(qn);
    r->generation_type(dogen::sml::generation_types::full_generation);
    r->documentation(documentation);
    r->type(dogen::sml::value_object_types::exception);
    return r;
}

}

namespace dogen {
namespace sml {
namespace test {

std::string mock_model_factory::model_name(const unsigned int n) {
    return ::model_name(n);
}

std::string mock_model_factory::simple_name(const unsigned int n) {
    return ::simple_name(n);
}

std::string mock_model_factory::module_name(const unsigned int n) {
    return ::module_name(n);
}

qname mock_model_factory::build_qname(const unsigned int model_n,
    const unsigned int simple_n) {

    dogen::sml::qname r;
    r.model_name(model_name(model_n));
    r.simple_name(simple_name(simple_n));
    return r;
}

model mock_model_factory::build_empty_model(const unsigned int n) {
    model r;
    populate_simple_model_properties(r, n);
    return r;
}

model mock_model_factory::
build_single_type_model(const unsigned int n, const object_types ot) {
    return build_multi_type_model(n, 1, ot);
}

model mock_model_factory::
build_single_type_model_in_module(const unsigned int n, const object_types ot,
    const unsigned int mod_n) {
    return build_multi_type_model(n, 1, ot, mod_n);
}

model mock_model_factory::
build_multi_type_model(const unsigned int n, const unsigned int type_n,
    const object_types ot, const unsigned int mod_n) {

    model r(build_empty_model(n));

    std::list<std::string> pp;
    for (unsigned int i(0); i < mod_n; ++i) {
        qname qn;
        qn.model_name(r.name().model_name());
        qn.simple_name(module_name(i));
        qn.module_path(pp);

        module p;
        p.name(qn);
        p.documentation(documentation);
        r.modules().insert(std::make_pair(p.name(), p));

        pp.push_back(module_name(i));
    }

    switch (ot) {
    case object_types::value_object:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto o(mock_value_object(i, r.name(), mod_n));
            r.objects().insert(std::make_pair(o->name(), o));
        }
        break;
    case object_types::enumeration:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(mock_enumeration(i, r.name(), mod_n));
            r.enumerations().insert(std::make_pair(e.name(), e));
        }
        break;
    case object_types::exception:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(mock_exception(i, r.name(), mod_n));
            r.objects().insert(std::make_pair(e->name(), e));
        }
        break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(building_error(invalid_object_type));
    }

    return r;
}

model mock_model_factory::
object_with_property(const object_types ot, const property_types pt) {
    using namespace dogen::sml;

    const auto mn(mock_model_qname(0));
    auto o1(mock_value_object(1, mn));

    property p;
    p.name(property_name(0));

    if (pt == property_types::value_object)
        p.type(mock_qname(*o1));
    else if (pt == property_types::boost_shared_ptr)
        p.type(mock_qname_shared_ptr(*o1));
    else
        p.type(mock_nested_qname(pt));

    boost::shared_ptr<abstract_object> o0;
    if (ot == object_types::value_object)
        o0 = mock_value_object(0, mn);
    else if (ot == object_types::keyed_entity || ot == object_types::entity)
        o0 = mock_entity(p, ot == object_types::keyed_entity, 0, mn);
    else {
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(building_error(invalid_object_type));
    }
    o0->properties().push_back(p);

    model r(build_empty_model(0));

    r.objects().insert(std::make_pair(o0->name(), o0));
    if (pt == property_types::value_object ||
        pt == property_types::boost_shared_ptr)
        r.objects().insert(std::make_pair(o1->name(), o1));

    if (pt == property_types::unsigned_int ||
        pt == property_types::boolean) {
        sml::primitive ui;
        ui.name(p.type().type());
        r.primitives().insert(std::make_pair(ui.name(), ui));
    } else if (pt == property_types::boost_shared_ptr) {
        dogen::sml::qname qn;
        qn.simple_name("shared_ptr");
        qn.model_name("boost");

        boost::shared_ptr<value_object> o2(new value_object());
        o2->name(qn);
        o2->type(dogen::sml::value_object_types::smart_pointer);
        r.objects().insert(std::make_pair(o2->name(), o2));
    } else if (pt == property_types::std_pair) {

        sml::primitive b;
        b.name().simple_name(boolean);
        r.primitives().insert(std::make_pair(b.name(), b));

        dogen::sml::qname qn;
        qn.simple_name("pair");
        qn.model_name("std");

        boost::shared_ptr<value_object> o2(new value_object());
        o2->name(qn);
        o2->type(sml::value_object_types::plain);
        r.objects().insert(std::make_pair(o2->name(), o2));
    } else if (pt == property_types::boost_variant) {
        sml::primitive b;
        b.name().simple_name(boolean);
        r.primitives().insert(std::make_pair(b.name(), b));

        sml::primitive ui;
        ui.name().simple_name(unsigned_int);
        r.primitives().insert(std::make_pair(ui.name(), ui));

        dogen::sml::qname qn;
        qn.simple_name("variant");
        qn.model_name("boost");

        boost::shared_ptr<value_object> o2(new value_object());
        o2->name(qn);
        o2->type(sml::value_object_types::plain);
        r.objects().insert(std::make_pair(o2->name(), o2));
    } else if (pt == property_types::std_string) {
        dogen::sml::qname qn;
        qn.simple_name("string");
        qn.model_name("std");

        boost::shared_ptr<value_object> o2(new value_object());
        o2->name(qn);
        o2->type(sml::value_object_types::plain);
        r.objects().insert(std::make_pair(o2->name(), o2));
    }

    return r;
}

std::array<model, 2>
mock_model_factory::object_with_property_type_in_different_model() {
    auto o0(mock_value_object(0));
    auto o1(mock_value_object(1));

    property p;
    p.name(property_name(0));
    p.type(mock_qname(*o1));
    o0->properties().push_back(p);

    qname m0_qn;
    m0_qn.model_name(model_name(0));

    model m0;
    m0.name(m0_qn);
    m0.objects().insert(std::make_pair(o0->name(), o0));

    qname m1_qn;
    m1_qn.model_name(model_name(1));

    model m1;
    m1.name(m1_qn);
    m1.objects().insert(std::make_pair(o1->name(), o1));

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::object_with_missing_property_type() {
    auto o0(mock_value_object(0));
    auto o1(mock_value_object(1));

    property p;
    p.name(property_name(0));
    p.type(mock_qname(*o1));
    o0->properties().push_back(p);

    qname mn_qn;
    mn_qn.model_name(model_name(0));

    model r(build_empty_model(0));
    r.objects().insert(std::make_pair(o0->name(), o0));

    return r;
}

model mock_model_factory::
object_with_parent_in_the_same_model(bool add_property) {
    const auto mn(mock_model_qname(0));

    model r(build_empty_model(0));
    auto o0(mock_value_object(0, mn));
    if (add_property) {
        property p;
        p.name(property_name(0));
        p.type(mock_nested_qname(property_types::unsigned_int));
        o0->properties().push_back(p);

        sml::primitive ui;
        ui.name(p.type().type());
        r.primitives().insert(std::make_pair(ui.name(), ui));
    }

    auto o1(mock_value_object(1, mn));
    if (add_property) {
        property p;
        p.name(property_name(1));
        p.type(mock_nested_qname(property_types::unsigned_int));
        o1->properties().push_back(p);
    }

    o0->parent_name(o1->name());
    o0->original_parent_name(o1->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    r.objects().insert(std::make_pair(o0->name(), o0));
    r.objects().insert(std::make_pair(o1->name(), o1));

    return r;
}

model mock_model_factory::object_with_missing_child_in_the_same_model() {
    const auto mn(mock_model_qname(0));
    auto o0(mock_value_object(0, mn));
    auto o1(mock_value_object(1, mn));
    o0->parent_name(o1->name());
    o0->original_parent_name(o1->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    model r(build_empty_model(0));
    r.objects().insert(std::make_pair(o1->name(), o1));

    return r;
}

std::array<model, 2> mock_model_factory::
object_with_parent_in_different_models() {
    auto o0(mock_value_object(0));
    auto o1(mock_value_object(1));
    o0->original_parent_name(o1->name());
    o0->parent_name(o1->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    model m0(build_empty_model(0));
    m0.objects().insert(std::make_pair(o0->name(), o0));

    model m1(build_empty_model(1));
    m1.objects().insert(std::make_pair(o1->name(), o1));
    m1.name(mock_model_qname(1));
    m1.origin_type(origin_types::user);

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::object_with_three_children_in_same_model() {
    const auto mn(mock_model_qname(0));
    auto o0(mock_value_object(0, mn));
    auto o1(mock_value_object(1, mn));
    auto o2(mock_value_object(2, mn));
    auto o3(mock_value_object(3, mn));

    o0->parent_name(o3->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o3->name());
    o1->original_parent_name(o3->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());

    o3->is_parent(true);
    o3->leaves().push_back(o0->name());
    o3->leaves().push_back(o1->name());
    o3->leaves().push_back(o2->name());

    model r(build_empty_model(0));
    r.objects().insert(std::make_pair(o0->name(), o0));
    r.objects().insert(std::make_pair(o1->name(), o1));
    r.objects().insert(std::make_pair(o2->name(), o2));
    r.objects().insert(std::make_pair(o3->name(), o3));
    r.name(mn);
    return r;

}

model mock_model_factory::
object_with_third_degree_parent_in_same_model(bool add_property) {
    const auto mn(mock_model_qname(0));

    model r(build_empty_model(0));

    auto o0(mock_value_object(0, mn));
    if (add_property) {
        property p;
        p.name(property_name(0));
        p.type(mock_nested_qname(property_types::unsigned_int));
        o0->properties().push_back(p);

        sml::primitive ui;
        ui.name(p.type().type());
        r.primitives().insert(std::make_pair(ui.name(), ui));
    }

    auto o1(mock_value_object(1, mn));
    if (add_property) {
        property p;
        p.name(property_name(1));
        p.type(mock_nested_qname(property_types::unsigned_int));
        o1->properties().push_back(p);
    }

    auto o2(mock_value_object(2, mn));
    if (add_property) {
        property p;
        p.name(property_name(2));
        p.type(mock_nested_qname(property_types::unsigned_int));
        o2->properties().push_back(p);
    }

    auto o3(mock_value_object(3, mn));
    if (add_property) {
        property p;
        p.name(property_name(3));
        p.type(mock_nested_qname(property_types::unsigned_int));
        o3->properties().push_back(p);
    }

    o0->parent_name(o1->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o2->name());
    o1->original_parent_name(o3->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());
    o2->is_parent(true);
    o2->leaves().push_back(o0->name());

    o3->leaves().push_back(o0->name());
    o3->is_parent(true);

    r.objects().insert(std::make_pair(o0->name(), o0));
    r.objects().insert(std::make_pair(o1->name(), o1));
    r.objects().insert(std::make_pair(o2->name(), o2));
    r.objects().insert(std::make_pair(o3->name(), o3));

    return r;
}

model mock_model_factory::object_with_third_degree_parent_missing() {
    const auto mn(mock_model_qname(0));
    auto o0(mock_value_object(0, mn));
    auto o1(mock_value_object(1, mn));
    auto o2(mock_value_object(2, mn));
    auto o3(mock_value_object(3, mn));

    o0->parent_name(o1->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o2->name());
    o1->original_parent_name(o3->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());
    o2->is_parent(true);
    o2->leaves().push_back(o0->name());

    o3->is_parent(true);
    o3->leaves().push_back(o0->name());

    model r(build_empty_model(0));
    r.objects().insert(std::make_pair(o0->name(), o0));
    r.objects().insert(std::make_pair(o1->name(), o1));
    r.objects().insert(std::make_pair(o2->name(), o2));
    r.name(mn);
    return r;
}

std::array<model, 4>
mock_model_factory::object_with_third_degree_parent_in_different_models() {
    auto o0(mock_value_object(0));
    auto o1(mock_value_object(1));
    auto o2(mock_value_object(2));
    auto o3(mock_value_object(3));

    o0->parent_name(o1->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o2->name());
    o1->original_parent_name(o3->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());
    o2->is_parent(true);
    o2->leaves().push_back(o0->name());

    o3->is_parent(true);
    o3->leaves().push_back(o0->name());

    model m0(build_empty_model(0));
    m0.objects().insert(std::make_pair(o0->name(), o0));

    model m1(build_empty_model(1));
    m1.objects().insert(std::make_pair(o1->name(), o1));

    model m2(build_empty_model(2));
    m2.objects().insert(std::make_pair(o2->name(), o2));

    model m3(build_empty_model(3));
    m3.objects().insert(std::make_pair(o3->name(), o3));

    return std::array<model, 4>{{ m0, m1, m2, m3 }};
}

std::array<model, 4> mock_model_factory::
object_with_missing_third_degree_parent_in_different_models() {
    auto o0(mock_value_object(0));
    auto o1(mock_value_object(1));
    auto o2(mock_value_object(2));
    auto o3(mock_value_object(3));

    o0->parent_name(o1->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o2->name());
    o1->original_parent_name(o3->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());
    o2->is_parent(true);
    o2->leaves().push_back(o0->name());

    o3->is_parent(true);
    o3->leaves().push_back(o0->name());

    model m0(build_empty_model(0));
    m0.objects().insert(std::make_pair(o0->name(), o0));

    model m1(build_empty_model(1));
    m1.objects().insert(std::make_pair(o1->name(), o1));

    model m2(build_empty_model(2));
    m2.objects().insert(std::make_pair(o2->name(), o2));

    return std::array<model, 4>{{ m0, m1, m2 }};
}

} } }

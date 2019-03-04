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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/unordered_set_io.hpp"
#include "masd.dogen.annotations/types/entry_selector.hpp"
#include "masd.dogen.annotations/types/type_repository_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/io/meta_model/languages_io.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/helpers/name_builder.hpp"
#include "masd.dogen.coding/types/helpers/name_factory.hpp"
#include "masd.dogen.coding/types/helpers/legacy_name_tree_parser.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/parsing_transform.hpp"

typedef boost::error_info<struct owner, std::string>
errmsg_parsing_owner;

namespace {

const std::string transform_id("coding.transforms.parsing_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string csharp_value("Value");
const std::string cpp_value("value");
const std::string documentation("Obtain the underlying value.");

const std::string empty_type("Attribute type is empty: ");
const std::string parent_name_conflict(
    "Parent name is defined in both meta-data and structure of model: ");
const std::string missing_underlier(
    "Primitive does not have an underlying element name: ");
const std::string unsupported_language("Invalid or unsupported language: ");
const std::string underlying_element_conflict(
    "Underlying element name is already defined: ");

}

namespace masd::dogen::coding::transforms {

parsing_transform::type_group parsing_transform::make_type_group(
    const annotations::type_repository& atrp) {
    type_group r;
    const annotations::type_repository_selector s(atrp);
    const auto gp(traits::generalization::parent());
    r.parent = s.select_type_by_name(gp);

    const auto eue(traits::enumeration::underlying_element());
    r.enumeration_underlying_element = s.select_type_by_name(eue);

    const auto pue(traits::primitive::underlying_element());
    r.primitive_underlying_element = s.select_type_by_name(pue);

    return r;
}

std::string parsing_transform::
make_parent(const type_group& tg, const annotations::annotation& a) {
    const annotations::entry_selector s(a);
    if (s.has_entry(tg.parent))
        return s.get_text_content(tg.parent);

    return std::string();
}

std::string parsing_transform::make_enumeration_underlying_element(
    const type_group& tg, const annotations::annotation& a) {
    const annotations::entry_selector s(a);
    if (s.has_entry(tg.enumeration_underlying_element))
        return s.get_text_content(tg.enumeration_underlying_element);

    return std::string();
}

std::string parsing_transform::make_primitive_underlying_element(
    const type_group& tg, const annotations::annotation& a) {
    const annotations::entry_selector s(a);
    if (s.has_entry(tg.primitive_underlying_element))
        return s.get_text_content(tg.primitive_underlying_element);

    return std::string();
}

std::string parsing_transform::
obtain_value_attribute_simple_name(const meta_model::languages l) {
    using meta_model::languages;
    switch(l) {
    case languages::csharp: return csharp_value;
    case languages::cpp: return cpp_value;
    default: {
        const auto s(boost::lexical_cast<std::string>(l));
        BOOST_LOG_SEV(lg, error) << unsupported_language << s;
        BOOST_THROW_EXCEPTION(transformation_error(unsupported_language + s));
    } }
}

void parsing_transform::parse_attributes(const meta_model::languages language,
    std::list<meta_model::attribute>& attrs) {
    const helpers::legacy_name_tree_parser ntp(language);
    for (auto& attr : attrs) {
        const auto ut(boost::algorithm::trim_copy(attr.unparsed_type()));

        /*
         * Attribute must always supply the unparsed type.
         */
        if (ut.empty()) {
            const auto sn(attr.name().simple());
            BOOST_LOG_SEV(lg, error) << empty_type << sn;
            BOOST_THROW_EXCEPTION(transformation_error(empty_type + sn));
        }

        auto nt(ntp.parse(ut));
        attr.parsed_type(nt);
    }
}

void parsing_transform::
parse_parent(const type_group& tg, meta_model::object& o) {
    /*
     * Obtain the parent name from the meta-data. If there is no
     * parent name there is nothing to do.
     */
    const auto parent(make_parent(tg, o.annotation()));
    if (parent.empty())
        return;

    /*
     * If we've already have a parent name, this means there are now
     * two conflicting sources of parenting information so bomb out.
     */
    if (!o.parents().empty()) {
        const auto& id(o.name().id());
        BOOST_LOG_SEV(lg, error) << parent_name_conflict << id;
        BOOST_THROW_EXCEPTION(transformation_error(parent_name_conflict + id));
    }

    /*
     * Convert the string obtained via meta-data into a coding name and
     * set it as our parent name.
     */
    const auto pn(helpers::name_builder::build(parent));
    o.parents().push_back(pn);
}

void parsing_transform::
parse_underlying_element(const type_group& tg, meta_model::enumeration& e) {

    /*
     * Obtain the underlying element name from the meta-data. If there
     * is none, there is nothing to do.
     */
    const auto s(make_enumeration_underlying_element(tg, e.annotation()));
    if (s.empty())
        return;

    /*
     * If we've already have an underlying element name, this means
     * there are now two conflicting sources of information.
     */
    if (!e.underlying_element().simple().empty()) {
        const auto& id(e.name().id());
        BOOST_LOG_SEV(lg, error) << underlying_element_conflict << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(underlying_element_conflict + id));
    }

    /*
     * Convert the string obtained via meta-data into a coding name and
     * set it as our underlying element name.
     */
    const auto ue(helpers::name_builder::build(s));
    e.underlying_element(ue);
}

void parsing_transform::parse_underlying_element(const type_group& tg,
    const meta_model::languages l, meta_model::primitive& p) {

    const auto id(p.name().id());

    /*
     * Obtain the underlying element name from the meta-data. If there
     * isn't one, bomb out as primitives require it.
     */
    auto ut(make_primitive_underlying_element(tg, p.annotation()));
    boost::algorithm::trim(ut);
    if (ut.empty()) {
        BOOST_LOG_SEV(lg, error) << missing_underlier << id;
        BOOST_THROW_EXCEPTION(transformation_error(missing_underlier + id));
    }

    /*
     * Create the value attribute.
     */
    helpers::name_factory nf;
    const auto& n(p.name());
    const auto sn(obtain_value_attribute_simple_name(l));

    meta_model::attribute attr;
    attr.name(nf.build_attribute_name(n, sn));
    attr.unparsed_type(ut);
    attr.documentation(documentation);

    const helpers::legacy_name_tree_parser ntp(l);
    auto nt(ntp.parse(ut));
    attr.parsed_type(nt);

    p.value_attribute(attr);
}

void parsing_transform::
transform(const context& ctx, meta_model::model& em) {
    tracing::scoped_transform_tracer stp(lg, "parsing transform",
        transform_id, em.name().id(), *ctx.tracer(), em);

    const auto tg(make_type_group(*ctx.type_repository()));
    const auto l(em.input_language());

    for (auto& pair : em.objects()) {
        auto& o(*pair.second);
        const auto id(o.name().id());

        try {
            parse_attributes(l, o.local_attributes());
            parse_parent(tg, o);
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    for (auto& pair : em.object_templates()) {
        auto& c(*pair.second);
        const auto id(c.name().id());

        try {
            parse_attributes(l, c.local_attributes());
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    for (auto& pair : em.enumerations()) {
        auto& e(*pair.second);
        const auto id(e.name().id());

        try {
            parse_underlying_element(tg, e);
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    for (auto& pair : em.primitives()) {
        auto& p(*pair.second);
        const auto id(p.name().id());

        try {
            parse_underlying_element(tg, l, p);
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    stp.end_transform(em);
}

}

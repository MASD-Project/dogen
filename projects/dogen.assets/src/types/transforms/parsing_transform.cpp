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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/types/traits.hpp"
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.assets/types/meta_model/structural/module.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/structural/builtin.hpp"
#include "dogen.assets/types/meta_model/structural/visitor.hpp"
#include "dogen.assets/types/meta_model/structural/exception.hpp"
#include "dogen.assets/types/meta_model/structural/primitive.hpp"
#include "dogen.assets/types/meta_model/structural/enumeration.hpp"
#include "dogen.assets/types/meta_model/structural/object_template.hpp"
#include "dogen.assets/types/meta_model/variability//feature_bundle.hpp"
#include "dogen.assets/io/meta_model/technical_space_io.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/helpers/name_builder.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.assets/types/helpers/legacy_name_tree_parser.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/parsing_transform.hpp"

typedef boost::error_info<struct owner, std::string>
errmsg_parsing_owner;

namespace {

const std::string transform_id("assets.transforms.parsing_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string csharp_value("Value");
const std::string cpp_value("value");
const std::string documentation("Obtain the underlying value.");

const std::string empty_type("Attribute type is empty: ");
const std::string missing_underlier(
    "Primitive does not have an underlying element name: ");
const std::string unsupported_technical_space(
    "Invalid or unsupported technical space: ");
const std::string underlying_element_conflict(
    "Underlying element name is already defined: ");

}

namespace dogen::assets::transforms {

parsing_transform::feature_group parsing_transform::make_feature_group(
    const variability::meta_model::feature_model& fm) {
    feature_group r;
    const variability::helpers::feature_selector s(fm);

    const auto eue(traits::enumeration::underlying_element());
    r.enumeration_underlying_element = s.get_by_name(eue);

    const auto pue(traits::primitive::underlying_element());
    r.primitive_underlying_element = s.get_by_name(pue);

    return r;
}

std::string parsing_transform::
make_enumeration_underlying_element(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.enumeration_underlying_element))
        return s.get_text_content(fg.enumeration_underlying_element);

    return std::string();
}

std::string
parsing_transform::make_primitive_underlying_element(const feature_group& tg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(tg.primitive_underlying_element))
        return s.get_text_content(tg.primitive_underlying_element);

    return std::string();
}

std::string parsing_transform::
obtain_value_attribute_simple_name(const meta_model::technical_space ts) {
    using meta_model::technical_space;
    switch(ts) {
    case technical_space::csharp: return csharp_value;
    case technical_space::cpp: return cpp_value;
    default: {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(
            transformation_error(unsupported_technical_space + s));
    } }
}

void parsing_transform::parse_attributes(const meta_model::technical_space ts,
    std::list<meta_model::attribute>& attrs) {
    const helpers::legacy_name_tree_parser ntp(ts);
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

void parsing_transform::parse_underlying_element(const feature_group& fg,
    meta_model::structural::enumeration& e) {
    /*
     * Obtain the underlying element name from the meta-data. If there
     * is none, there is nothing to do.
     */
    const auto s(make_enumeration_underlying_element(fg, *e.configuration()));
    if (s.empty())
        return;

    /*
     * If we've already have an underlying element name, this means
     * there are now two conflicting sources of information.
     */
    if (!e.underlying_element().simple().empty()) {
        const auto& id(e.name().qualified().dot());
        BOOST_LOG_SEV(lg, error) << underlying_element_conflict << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(underlying_element_conflict + id));
    }

    /*
     * Convert the string obtained via meta-data into a assets name and
     * set it as our underlying element name.
     */
    const auto ue(helpers::name_builder::build(s));
    e.underlying_element(ue);
}

void parsing_transform::parse_underlying_element(const feature_group& /*fg*/,
    const meta_model::technical_space ts,
    meta_model::structural::primitive& p) {

    // const auto id(p.name().qualified().dot());

    // /*
    //  * Obtain the underlying element name from the meta-data. If there
    //  * isn't one, bomb out as primitives require it.
    //  */
    // auto ut(make_primitive_underlying_element(fg, *p.configuration()));
    // boost::algorithm::trim(ut);
    // if (ut.empty()) {
    //     BOOST_LOG_SEV(lg, error) << missing_underlier << id;
    //     BOOST_THROW_EXCEPTION(transformation_error(missing_underlier + id));
    // }

    // /*
    //  * Create the value attribute.
    //  */
    // helpers::name_factory nf;
    // const auto& n(p.name());
    // const auto sn(obtain_value_attribute_simple_name(ts));

    // meta_model::attribute attr;
    // attr.name(nf.build_attribute_name(n, sn));
    // attr.unparsed_type(ut);
    // attr.documentation(documentation);

    const helpers::legacy_name_tree_parser ntp(ts);
    const auto nt(ntp.parse(p.value_attribute().unparsed_type()));
    p.value_attribute().parsed_type(nt);
}

void parsing_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "parsing transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto fg(make_feature_group(*ctx.feature_model()));
    const auto ts(m.input_technical_space());
    for (auto& pair : m.structural_elements().objects()) {
        auto& o(*pair.second);
        const auto id(o.name().qualified().dot());

        try {
            parse_attributes(ts, o.local_attributes());
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    for (auto& pair : m.structural_elements().object_templates()) {
        auto& c(*pair.second);
        const auto id(c.name().qualified().dot());

        try {
            parse_attributes(ts, c.local_attributes());
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    /*
    for (auto& pair : m.structural_elements().enumerations()) {
        auto& e(*pair.second);
        const auto id(e.name().qualified().dot());

        try {
            parse_underlying_element(fg, e);
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
        }*/

    for (auto& pair : m.structural_elements().primitives()) {
        auto& p(*pair.second);
        const auto id(p.name().qualified().dot());

        try {
            parse_underlying_element(fg,ts, p);
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    for (auto& pair : m.variability_elements().feature_bundles()) {
        auto& fb(*pair.second);
        const auto id(fb.name().qualified().dot());

        try {
            const helpers::legacy_name_tree_parser ntp(ts);

            for(auto& ft : fb.feature_templates()) {
                const auto ut(boost::algorithm::trim_copy(ft.mapped_type()));

                if (ut.empty()) {
                    BOOST_LOG_SEV(lg, error) << empty_type << id;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(empty_type + id));
                }
                auto nt(ntp.parse(ut));
                ft.parsed_type(nt);
            }
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    stp.end_transform(m);
}

}

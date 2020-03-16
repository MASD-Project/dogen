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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/variability/feature_bundle.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/helpers/legacy_name_tree_parser.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/parsing_transform.hpp"

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

}

namespace dogen::logical::transforms {

void parsing_transform::parse_attributes(const entities::technical_space ts,
    std::list<entities::attribute>& attrs) {
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

void parsing_transform::
parse_underlying_element(const entities::technical_space ts,
    entities::structural::primitive& p) {
    const helpers::legacy_name_tree_parser ntp(ts);
    const auto nt(ntp.parse(p.value_attribute().unparsed_type()));
    p.value_attribute().parsed_type(nt);
}

void parsing_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "parsing transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

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

    for (auto& pair : m.structural_elements().primitives()) {
        auto& p(*pair.second);
        const auto id(p.name().qualified().dot());

        try {
            parse_underlying_element(ts, p);
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    for (auto& pair : m.variability_elements().feature_template_bundles()) {
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

    for (auto& pair : m.variability_elements().feature_bundles()) {
        auto& fb(*pair.second);
        const auto id(fb.name().qualified().dot());

        try {
            const helpers::legacy_name_tree_parser ntp(ts);

            for(auto& f : fb.features()) {
                const auto ut(boost::algorithm::trim_copy(f.mapped_type()));

                if (ut.empty()) {
                    BOOST_LOG_SEV(lg, error) << empty_type << id;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(empty_type + id));
                }
                auto nt(ntp.parse(ut));
                f.parsed_type(nt);
            }
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    stp.end_transform(m);
}

}

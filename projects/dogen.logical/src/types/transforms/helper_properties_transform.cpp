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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/types/entities/logical_name_tree.hpp"
#include "dogen.identification/types/helpers/logical_name_flattener.hpp"
#include "dogen.logical/types/features/helpers.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/helper_descriptor.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.logical/types/entities/helper_properties.hpp"
#include "dogen.logical/io/entities/streaming_properties_io.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/io/entities/helper_properties_io.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/helper_properties_transform.hpp"

namespace {

const std::string
transform_id("logical.transforms.helper_properties_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_id("Duplicate ID:");
const std::string descriptor_expected(
    "Child name tree has no associated helper descriptor");
const std::string missing_helper_family("Helper family not found for: ");
const std::string empty_identifiable(
    "Identifiable was not generated correctly and is empty.");

}

namespace dogen::logical::transforms {

// using logical::entities::helper_properties;
// using logical::entities::helper_descriptor;

namespace {

class configuration_generator {
public:
    explicit configuration_generator(
        const features::helpers::feature_group& fg);

public:
    void operator()(entities::element& e);

public:
    const std::unordered_map<identification::entities::logical_id, std::string>&
    result() { return result_; }

private:
    const features::helpers::feature_group& feature_group_;
    std::unordered_map<identification::entities::logical_id, std::string>
    result_;
};

configuration_generator::
configuration_generator(const features::helpers::feature_group& fg)
    : feature_group_(fg) {}

void configuration_generator::operator()(entities::element& e) {
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id.value();

    const auto& cfg(*e.configuration());
    using features::helpers;
    const auto scfg(helpers::make_static_configuration(feature_group_, cfg));
    const auto pair(std::make_pair(id, scfg.family));
    const auto result(result_.insert(pair).second);
    if (!result) {
        BOOST_LOG_SEV(lg, error) << duplicate_id << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(duplicate_id + id.value()));
    }
}

}


std::unordered_map<identification::entities::logical_id, std::string>
helper_properties_transform::
make_configuration(const variability::entities::feature_model& fm,
    const entities::model& m) {

    BOOST_LOG_SEV(lg, debug) << "Started making the configuration.";

    using logical::features::helpers;
    const auto fg(helpers::make_feature_group(fm));
    configuration_generator cg(fg);
    elements_traversal(m, cg);

    const auto& r(cg.result());
    BOOST_LOG_SEV(lg, debug) << "Finished making the configuration. Result:"
                             << r;
    return r;
}


void helper_properties_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "decoration",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto cfg(make_configuration(fm, m));


    stp.end_transform(m);
}

}

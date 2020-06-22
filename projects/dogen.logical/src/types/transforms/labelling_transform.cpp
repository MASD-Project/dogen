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
#include <unordered_set>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/features/labelling.hpp"
#include "dogen.logical/types/entities/label.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/labelling_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.labelling_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_key_found("Duplicate key: ");

}

namespace dogen::logical::transforms {

namespace {

/**
 * @brief Updates the labels for any elements that have them.
 */
class labels_updater {
public:
    labels_updater(const features::labelling::feature_group& fg)
        : feature_group_(fg) {}

public:
    void operator()(entities::element& e);

private:
    const features::labelling::feature_group& feature_group_;
};

void labels_updater::operator()(entities::element& e) {
    using features::labelling;
    const auto scfg(labelling::make_static_configuration(feature_group_, e));

    std::unordered_set<std::string> keys;
    for (const auto& kvp : scfg.label) {
        const auto& k(kvp.first);
        const auto& v(kvp.second);
        const auto inserted(keys.insert(k).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_key_found << k;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_key_found + k));
        }
        e.labels().push_back(entities::label(k, v));
    }
}

}

void labelling_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "labelling transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto fg(features::labelling::make_feature_group(fm));
    labels_updater u(fg);
    entities::elements_traversal(m, u);

    stp.end_transform(m);
}

}

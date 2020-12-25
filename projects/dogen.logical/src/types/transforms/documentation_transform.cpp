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
#include <boost/algorithm/string/trim.hpp>
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/documentation_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.documentation_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

namespace {

/**
 * @brief Updates the documentation on all model elements.
 */
class trimmer {
private:
    void trim(logical::entities::element& e) {
        const auto trimmed(boost::algorithm::trim_copy(e.documentation()));
        e.documentation(trimmed);
    }

    void trim(logical::entities::attribute& attr) {
        const auto trimmed(boost::algorithm::trim_copy(attr.documentation()));
        attr.documentation(trimmed);
    }

public:
    void operator()(logical::entities::element& v) { trim(v); }
    void operator()(logical::entities::structural::object_template &v) {
        trim(v);
        for (auto& attr : v.local_attributes())
            trim(attr);
    }

    void operator()(logical::entities::structural::object& v) {
        trim(v);
        for (auto& attr : v.local_attributes())
            trim(attr);
    }
};

}

void documentation_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "documentation transform",
        transform_id, m.name().id().value(), *ctx.tracer(), m);

    trimmer t;
    using logical::entities::elements_traversal;
    elements_traversal(m, t);
    stp.end_transform(m);
}

}

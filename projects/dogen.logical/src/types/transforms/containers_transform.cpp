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
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/containers_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.containers_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_id("Duplicate ID for element: ");

}

namespace dogen::logical::transforms {

/**
 * @brief Gathers element ids for containers.
 */
class container_id_gatherer {
public:
    const std::unordered_set<std::string>& result() { return result_; }

private:
    template<typename Nameable>
    void insert(const Nameable& n) {
        const auto id(n.name().qualified().dot());
        const auto inserted(result_.insert(id).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_id << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_id + id));
        }
    }

public:
    void operator()(entities::element&) { /*ignored by design.*/ }
    void operator()(entities::structural::module& v) { insert(v); }
    void operator()(entities::decoration::modeline_group& v) { insert(v); }
    void operator()(logical::entities::physical::backend& v) { insert(v); }
    void operator()(logical::entities::physical::facet& v) { insert(v); }

private:
    std::unordered_set<std::string> result_;
};

void containers_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "containers transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    container_id_gatherer g;
    entities::elements_traversal(m, g);
    m.container_ids(g.result());

    stp.end_transform(m);
}

}

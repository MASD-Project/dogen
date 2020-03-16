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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/io/meta_model/model_set_io.hpp"
#include "dogen.logical/types/meta_model/elements_traversal.hpp"
#include "dogen.logical/types/transforms/dynamic_stereotypes_transform.hpp"

namespace {

const std::string transform_id(
    "assets.transforms.dynamic_stereotypes_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

namespace {

class updater {
private:
    template<typename Configurable>
    std::list<std::string> extract(Configurable& c) {
        const auto& n(c.configuration()->name());
        const auto& qn(n.qualified());
        BOOST_LOG_SEV(lg, trace) << "Extracting: " << n.simple()
                                 << " (" << qn << ") ";

        std::list<std::string> r;
        const auto& pbs(c.configuration()->profile_bindings());
        for (const auto& pb : pbs) {
            if (!pb.realized())
                r.push_back(pb.name());
        }
        return r;
    }

    void update(logical::meta_model::element& e) {
        e.dynamic_stereotypes(extract(e));
    }

public:
    void operator()(logical::meta_model::element& e) { update(e); }
    void operator()(logical::meta_model::structural::object_template &ot) {
        update(ot);
        for (auto& attr : ot.local_attributes())
            attr.dynamic_stereotypes(extract(attr));
    }
    void operator()(logical::meta_model::structural::enumeration& e) {
        update(e);
        for (auto& enm : e.enumerators())
            enm.dynamic_stereotypes(extract(enm));
    }
    void operator()(logical::meta_model::structural::object& o) {
        update(o);
        for (auto& attr : o.local_attributes())
            attr.dynamic_stereotypes(extract(attr));
    }
};

}

void
dynamic_stereotypes_transform::apply(const logical::transforms::context& ctx,
    logical::meta_model::model_set& ms) {
    tracing::scoped_transform_tracer stp(lg, "dynamic stereotypes transform",
        transform_id, *ctx.tracer(), ms);

    updater u;
    using logical::meta_model::elements_traversal;
    elements_traversal(ms.target(), u);
    for (auto& m : ms.references())
        elements_traversal(m, u);

    stp.end_transform(ms);
}

}

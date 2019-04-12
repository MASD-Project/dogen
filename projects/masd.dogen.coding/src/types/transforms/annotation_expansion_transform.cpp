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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/annotation_expander.hpp"
#include "masd.dogen.coding/io/meta_model/model_set_io.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.coding/types/transforms/annotation_expansion_transform.hpp"

namespace {

const std::string transform_id(
    "coding.transforms.annotation_expansion_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

namespace {

class updater {
public:
    explicit updater(const variability::annotation_expander& e)
        : annotation_expander_(e) {}

private:
    void update(meta_model::element& e) {
        const auto& ds(e.dynamic_stereotypes());
        e.annotation(annotation_expander_.expand(ds, e.annotation()));
    }

public:
    void operator()(meta_model::element&) { }
    void operator()(meta_model::module& m) { update(m); }
    void operator()(meta_model::object_template& ot) {
        update(ot);
        for (auto& attr : ot.local_attributes())
            attr.annotation(annotation_expander_.expand(attr.annotation()));
    }
    void operator()(meta_model::builtin& b) { update(b); }
    void operator()(meta_model::enumeration& e) {
        update(e);
        for (auto& enm : e.enumerators())
            enm.annotation(annotation_expander_.expand(enm.annotation()));
    }
    void operator()(meta_model::primitive& p) { update(p); }
    void operator()(meta_model::object& o) {
        update(o);
        for (auto& attr : o.local_attributes())
            attr.annotation(annotation_expander_.expand(attr.annotation()));
    }
    void operator()(meta_model::exception& e) { update(e); }
    void operator()(meta_model::visitor& v) { update(v); }
    void operator()(meta_model::licence& l) { update(l); }
    void operator()(meta_model::modeline& ml) { update(ml); }
    void operator()(meta_model::modeline_group& mg) { update(mg); }
    void operator()(meta_model::generation_marker& gm) { update(gm); }
    void operator()(meta_model::configuration& c) {
        update(c);
        for (auto& e : c.entries())
            e.annotation(annotation_expander_.expand(e.annotation()));
    }

private:
    const variability::annotation_expander annotation_expander_;
};

}

void annotation_expansion_transform::
apply(const context& ctx, meta_model::model_set& ms) {
    tracing::scoped_transform_tracer stp(lg, "annotation expansion transform",
        transform_id, ms.target().name().qualified().dot(), *ctx.tracer(), ms);

    updater u(*ctx.annotation_expander());
    meta_model::elements_traversal(ms.target(), u);

    for (auto& m : ms.references())
        meta_model::elements_traversal(m, u);

    stp.end_transform(ms);
}


}

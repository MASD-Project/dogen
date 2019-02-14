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
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.coding/types/meta_model/endomodel.hpp"
#include "masd.dogen.coding/io/meta_model/endomodel_io.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/meta_naming_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.meta_naming_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

using helpers::meta_name_factory;

class updater {
public:
    void operator()(meta_model::element&) {
        /*
         * Element ignored on purpose; we cannot update non-coding
         * meta-model elements.
         */
    }

    void operator()(meta_model::module& m) {
        static const auto n(meta_name_factory::make_module_name());
        m.meta_name(n);
    }

    void operator()(meta_model::object_template& ot) {
        static const auto n(meta_name_factory::make_object_template_name());
        ot.meta_name(n);
    }

    void operator()(meta_model::builtin& b) {
        static const auto n(meta_name_factory::make_builtin_name());
        b.meta_name(n);
    }

    void operator()(meta_model::enumeration& e) {
        static const auto n(meta_name_factory::make_enumeration_name());
        e.meta_name(n);
    }

    void operator()(meta_model::primitive& p) {
        static const auto n(meta_name_factory::make_primitive_name());
        p.meta_name(n);
    }

    void operator()(meta_model::object& o) {
        static const auto n(meta_name_factory::make_object_name());
        o.meta_name(n);
    }

    void operator()(meta_model::exception& e) {
        static const auto n(meta_name_factory::make_exception_name());
        e.meta_name(n);
    }

    void operator()(meta_model::visitor& v) {
        static const auto n(meta_name_factory::make_visitor_name());
        v.meta_name(n);
    }
};

void meta_naming_transform::
transform(const context& ctx, meta_model::endomodel& em) {
    tracing::scoped_transform_tracer stp(lg, "meta-naming transform",
        transform_id, em.name().id(), ctx.tracer(), em);

    em.meta_name(meta_name_factory::make_endomodel_name());

    updater u;
    meta_model::elements_traversal(em, u);

    stp.end_transform(em);
}

}

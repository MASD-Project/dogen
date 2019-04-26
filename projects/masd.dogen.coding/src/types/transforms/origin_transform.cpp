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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
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
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/origin_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.origin_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string target_cannot_be_proxy(
    "Model has origin set to target but is also a proxy: ");

}

namespace masd::dogen::coding::transforms {

namespace {

class updater {
public:
    explicit updater(const meta_model::origin_types ot) : origin_types_(ot) {}

public:
    template<typename DeterminableOrigin>
    void update(DeterminableOrigin& d) { d.origin_type(origin_types_); }

public:
    void operator()(meta_model::element&) { }
    void operator()(meta_model::module& m) { update(m); }
    void operator()(meta_model::object_template& ot) { update(ot); }
    void operator()(meta_model::builtin& b) { update(b); }
    void operator()(meta_model::enumeration& e) { update(e); }
    void operator()(meta_model::primitive& p) { update(p); }
    void operator()(meta_model::object& o) { update(o); }
    void operator()(meta_model::exception& e) { update(e); }
    void operator()(meta_model::visitor& v) { update(v); }

private:
    const meta_model::origin_types origin_types_;
};

}

origin_transform::type_group origin_transform::
make_type_group(const variability::type_repository& atrp) {

    type_group r;
    const variability::type_repository_selector s(atrp);
    r.is_proxy_model = s.select_type_by_name(traits::is_proxy_model());
    return r;
}

bool origin_transform::
is_proxy_model(const type_group& tg, const meta_model::model& m) {
    const auto& o(m.root_module()->annotation());
    const variability::entry_selector s(o);
    const bool r(s.get_boolean_content_or_default(tg.is_proxy_model));
    BOOST_LOG_SEV(lg, debug) << "Read is proxy model: " << r
                             << " for model: " << m.name().qualified().dot();
    return r;
}

origin_transform::feature_group origin_transform::
make_feature_group(const variability::meta_model::feature_model& fm) {
    feature_group r;
    const variability::helpers::feature_selector s(fm);
    r.is_proxy_model = s.get_by_name(traits::is_proxy_model());
    return r;
}

bool origin_transform::
is_proxy_model(const feature_group& fg, const meta_model::model& m) {
    const auto& cfg(*m.root_module()->configuration());
    const variability::helpers::configuration_selector s(cfg);
    const bool r(s.get_boolean_content_or_default(fg.is_proxy_model));
    BOOST_LOG_SEV(lg, debug) << "Read is proxy model: " << r
                             << " for model: " << m.name().qualified().dot();
    return r;
}

meta_model::origin_types origin_transform::
compute_origin_types(const meta_model::model& m, const bool is_proxy_model) {
    using meta_model::origin_types;
    if (is_proxy_model && m.origin_type() == origin_types::target) {
        const auto& id(m.name().qualified().dot());
        BOOST_LOG_SEV(lg, error) << target_cannot_be_proxy << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(target_cannot_be_proxy + id));
    }

    if (m.origin_type() == origin_types::target)
        return origin_types::target;
    else if (is_proxy_model)
        return origin_types::proxy_reference;

    return origin_types::non_proxy_reference;
}

void origin_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "origin transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);


    bool ipm(false);
    if (ctx.use_configuration()) {
        const auto fg(make_feature_group(*ctx.feature_model()));
        ipm = is_proxy_model(fg, m);
    } else {
        const auto tg(make_type_group(*ctx.type_repository()));
        ipm = is_proxy_model(tg, m);
    }
    const auto ot(compute_origin_types(m, ipm));
    m.origin_type(ot);

    updater g(ot);
    meta_model::elements_traversal(m, g);

    stp.end_transform(m);
}

}

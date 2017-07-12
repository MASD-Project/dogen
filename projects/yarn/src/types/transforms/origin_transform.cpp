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
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/meta_model/elements_traversal.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/origin_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.origin_transform"));

const std::string target_cannot_be_proxy(
    "Model has origin set to target but is also a proxy: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

namespace {

class updater {
public:
    explicit updater(const meta_model::origin_types ot) : origin_types_(ot) {}

public:
    template<typename DeterminableOrigin>
    void update(DeterminableOrigin& d) { d.origin_type(origin_types_); }

public:
    bool include_injected_elements() { return false; }
    void operator()(meta_model::element&) { }
    void operator()(meta_model::module& m) { update(m); }
    void operator()(meta_model::concept& c) { update(c); }
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
make_type_group(const annotations::type_repository& atrp) {

    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.is_proxy_model = s.select_type_by_name(traits::is_proxy_model());
    return r;
}

bool origin_transform::
is_proxy_model(const type_group& tg, const meta_model::intermediate_model& im) {
    const auto& o(im.root_module().annotation());
    const annotations::entry_selector s(o);
    const bool r(s.get_boolean_content_or_default(tg.is_proxy_model));
    BOOST_LOG_SEV(lg, debug) << "Read is proxy model: " << r
                             << " for model: " << im.name().id();
    return r;
}

meta_model::origin_types
origin_transform::compute_origin_types(const meta_model::intermediate_model& im,
    const bool is_proxy_model) {
    using meta_model::origin_types;
    if (is_proxy_model && im.origin_type() == origin_types::target) {
        const auto& id(im.name().id());
        BOOST_LOG_SEV(lg, error) << target_cannot_be_proxy << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(target_cannot_be_proxy + id));
    }

    if (im.origin_type() == origin_types::target)
        return origin_types::target;
    else if (is_proxy_model)
        return origin_types::proxy_reference;

    return origin_types::non_proxy_reference;
}

void origin_transform::
transform(const context& ctx, meta_model::intermediate_model& im) {
    const auto tg(make_type_group(ctx.type_repository()));
    const auto ipm(is_proxy_model(tg, im));
    const auto ot(compute_origin_types(im, ipm));
    im.origin_type(ot);

    updater g(ot);
    meta_model::elements_traversal(im, g);
}

} } }

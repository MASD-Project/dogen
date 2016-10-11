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
#include "dogen/annotations/types/repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/origin_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.origin_expander"));

const std::string target_cannot_be_proxy(
    "Model has origin set to target but is also a proxy: ");

}

namespace dogen {
namespace yarn {

namespace {

class updater {
public:
    explicit updater(const origin_types ot) : origin_types_(ot) {}

public:
    template<typename DeterminableOrigin>
    void update(DeterminableOrigin& d) { d.origin_type(origin_types_); }

public:
    void operator()(yarn::module& m) { update(m); }
    void operator()(yarn::concept& c) { update(c); }
    void operator()(yarn::primitive& p) { update(p); }
    void operator()(yarn::enumeration& e) { update(e); }
    void operator()(yarn::object& o) { update(o); }
    void operator()(yarn::exception& e) { update(e); }
    void operator()(yarn::visitor& v) { update(v); }

private:
    const origin_types origin_types_;
};

}

origin_expander::type_group origin_expander::
make_type_group(const annotations::type_repository& atrp) const {

    type_group r;
    const annotations::repository_selector rs(atrp);
    r.is_proxy_model = rs.select_field_by_name(traits::is_proxy_model());
    return r;
}

bool origin_expander::
is_proxy_model(const type_group& tg, const intermediate_model& im) const {
    const auto& o(im.root_module().annotation());
    const annotations::field_selector fs(o);
    const bool r(fs.get_boolean_content_or_default(tg.is_proxy_model));
    BOOST_LOG_SEV(lg, debug) << "Read is proxy model: " << r
                             << " for model: " << im.name().id();
    return r;
}

origin_types origin_expander::compute_origin_types(const intermediate_model& im,
    const bool is_proxy_model) const {
    if (is_proxy_model && im.origin_type() == origin_types::target) {
        const auto& id(im.name().id());
        BOOST_LOG_SEV(lg, error) << target_cannot_be_proxy << id;
        BOOST_THROW_EXCEPTION(expansion_error(target_cannot_be_proxy + id));
    }

    if (im.origin_type() == origin_types::target)
        return origin_types::target;
    else if (is_proxy_model)
        return origin_types::proxy_reference;

    return origin_types::non_proxy_reference;
}

void origin_expander::
expand(const annotations::type_repository& atrp, intermediate_model& im) const {
    const auto tg(make_type_group(atrp));
    const auto ipm(is_proxy_model(tg, im));
    const auto ot(compute_origin_types(im, ipm));
    im.origin_type(ot);

    updater g(ot);
    yarn::elements_traversal(im, g);
}

} }

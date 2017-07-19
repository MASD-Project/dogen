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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/meta_model/elements_traversal.hpp"
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/meta_name_transform.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.meta_name_transform"));

}

namespace dogen {
namespace yarn {
namespace transforms {

class updater {
private:
    meta_model::location create_location() const {
        meta_model::location r;
        r.external_modules().push_back("dogen");
        r.model_modules().push_back("yarn");
        r.internal_modules().push_back("meta_model");
        return r;
    }

    meta_model::name create_name(const std::string& sn) const {
        static const auto l(create_location());
        helpers::name_builder b;
        b.location(l);
        b.simple_name(sn);
        return b.build();
    }

private:
    void update(const meta_model::name& mn, meta_model::element& e) const {
        e.meta_name(mn);
    }

public:
    void operator()(meta_model::element&) { }
    void operator()(meta_model::module& m) {
        static const auto n(create_name("module"));
        update(n, m);
    }
    void operator()(meta_model::concept& c) {
        static const auto n(create_name("concept"));
        update(n, c);
    }
    void operator()(meta_model::builtin& b) {
        static const auto n(create_name("builtin"));
        update(n, b);
    }
    void operator()(meta_model::enumeration& e) {
        static const auto n(create_name("enumeration"));
        update(n, e);
    }
    void operator()(meta_model::primitive& p) {
        static const auto n(create_name("primitive"));
        update(n, p);
    }
    void operator()(meta_model::object& o) {
        static const auto n(create_name("object"));
        update(n, o);
    }
    void operator()(meta_model::exception& e) {
        static const auto n(create_name("exception"));
        update(n, e);
    }
    void operator()(meta_model::visitor& v) {
        static const auto n(create_name("visitor"));
        update(n, v);
    }
};

void meta_name_transform::transform(meta_model::intermediate_model& im) {
    updater u;
    meta_model::elements_traversal(im, u);
}

} } }

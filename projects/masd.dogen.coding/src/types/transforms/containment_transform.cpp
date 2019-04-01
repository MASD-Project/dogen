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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.coding/types/helpers/name_factory.hpp"
#include "masd.dogen.coding/types/helpers/name_builder.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/containment_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.containment_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string separator(".");
const std::string missing_module("Could not find module: ");

}

namespace masd::dogen::coding::transforms {

namespace {

class updater {
public:
    updater(meta_model::model& m) : model_(m) { }

private:
    boost::optional<meta_model::name>
    containing_module(const meta_model::name& n);
    void update(meta_model::element& e);

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

public:
    meta_model::model& model_;
};

boost::optional<meta_model::name>
updater::containing_module(const meta_model::name& n) {
    BOOST_LOG_SEV(lg, debug) << "Finding containing module for: "
                             << n.qualified().dot();

    const bool in_global_namespace(n.location().model_modules().empty());
    if (in_global_namespace) {
        BOOST_LOG_SEV(lg, debug) << "Type is in global module so, it has"
                                 << " no containing module yet. Type: "
                                 << n.qualified().dot();
        return boost::optional<meta_model::name>();
    }

    const bool at_model_level(n.location().internal_modules().empty());
    const auto mn(n.location().model_modules().back());
    if (at_model_level && n.simple() == mn) {
        BOOST_LOG_SEV(lg, debug) << "Type is a model module, so containing "
                                 << "module will be handled later. Type: "
                                 << n.qualified().dot();
        return boost::optional<meta_model::name>();
    }

    helpers::name_builder b;

    /* we can always take the external modules regardless because these
     * do not contribute to the modules in the model.
     */
     b.external_modules(n.location().external_modules());

    auto imp(n.location().internal_modules());
    if (imp.empty()) {
        /* if there are no internal modules, we must be at the
         * top-level, so take the model name.
         */
        b.simple_name(mn);

        /* the model name may be composite. If so, we need to make
         * sure we add the remaining components.
         */
        if (!n.location().model_modules().empty()) {
            auto remaining_model_modules(n.location().model_modules());
            remaining_model_modules.pop_back();
            b.model_modules(remaining_model_modules);
        }
    } else {
        /* if we are an internal module, we can take the module name
         * and use that as our simple name. We need to add the
         * remaining internal module names to our location.
         */
        b.model_modules(n.location().model_modules());
        b.simple_name(imp.back());
        imp.pop_back();
        b.internal_modules(imp);
    }

    const auto module_n(b.build());
    const auto i(model_.modules().find(module_n.qualified().dot()));
    if (i != model_.modules().end()) {
        BOOST_LOG_SEV(lg, debug) << "Adding type to module. Type: '"
                                 << n.qualified().dot()
                                 << "' Module: '" << module_n.qualified().dot();
        auto& o(*i->second);
        o.members().push_back(n.qualified().dot());
        return module_n;
    }

    BOOST_LOG_SEV(lg, warn) << "Could not find containing module: "
                            << module_n.qualified().dot();
    return boost::optional<meta_model::name>();
}

void updater::update(meta_model::element& e) {
    e.contained_by(containing_module(e.name()));

    if (!e.contained_by())
        return;

    auto i(model_.modules().find(e.contained_by()->qualified().dot()));
    if (i == model_.modules().end()) {
        const auto sn(e.contained_by()->simple());
        BOOST_LOG_SEV(lg, error) << missing_module << sn;
        BOOST_THROW_EXCEPTION(transformation_error(missing_module + sn));
    }
}

}

void containment_transform::
apply(const context& /*ctx*/, meta_model::model& m) {
    updater u(m);
    meta_model::elements_traversal(m, u);
}

}

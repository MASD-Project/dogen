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
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/endomodel_io.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.coding/types/helpers/name_factory.hpp"
#include "masd.dogen.coding/types/helpers/name_builder.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/modules_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.modules_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string separator(".");
const std::string missing_module("Could not find module: ");

}

namespace masd::dogen::coding::transforms {

namespace {

class internal_modules_builder {
private:
    void process(const meta_model::name& n);

public:
    void operator()(meta_model::element&) { }
    void operator()(meta_model::module& m) { process(m.name()); }
    void operator()(meta_model::object_template& ot) { process(ot.name()); }
    void operator()(meta_model::builtin& b) { process(b.name()); }
    void operator()(meta_model::enumeration& e) { process(e.name()); }
    void operator()(meta_model::primitive& p) { process(p.name()); }
    void operator()(meta_model::object& o) { process(o.name()); }
    void operator()(meta_model::exception& e) { process(e.name()); }
    void operator()(meta_model::visitor& v) { process(v.name()); }

public:
    const std::unordered_map<std::string, std::list<std::string>>&
    result();

private:
    std::unordered_map<std::string, std::list<std::string>>
        distinct_internal_moduless_;
};

void internal_modules_builder::process(const meta_model::name& n) {
    auto imp(n.location().internal_modules());
    while (!imp.empty()) {
        const std::string key(boost::join(imp, separator));
        distinct_internal_moduless_.insert(std::make_pair(key, imp));
        imp.pop_back();
    }
}

const std::unordered_map<std::string, std::list<std::string>>&
    internal_modules_builder::result() {
    return distinct_internal_moduless_;
}

class updater {
public:
    updater(meta_model::endomodel& im) : model_(im) { }

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
    meta_model::endomodel& model_;
};

boost::optional<meta_model::name>
updater::containing_module(const meta_model::name& n) {
    BOOST_LOG_SEV(lg, debug) << "Finding containing module for: "
                             << n.id();

    const bool in_global_namespace(n.location().model_modules().empty());
    if (in_global_namespace) {
        BOOST_LOG_SEV(lg, debug) << "Type is in global module so, it has"
                                 << " no containing module yet. Type: "
                                 << n.id();
        return boost::optional<meta_model::name>();
    }

    const bool at_model_level(n.location().internal_modules().empty());
    const auto mn(n.location().model_modules().back());
    if (at_model_level && n.simple() == mn) {
        BOOST_LOG_SEV(lg, debug) << "Type is a model module, so containing "
                                 << "module will be handled later. Type: "
                                 << n.id();
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
    const auto i(model_.modules().find(module_n.id()));
    if (i != model_.modules().end()) {
        BOOST_LOG_SEV(lg, debug) << "Adding type to module. Type: '"
                                 << n.id()
                                 << "' Module: '" << module_n.id();
        auto& o(*i->second);
        o.members().push_back(n.id());
        return module_n;
    }

    BOOST_LOG_SEV(lg, warn) << "Could not find containing module: "
                            << module_n.id();
    return boost::optional<meta_model::name>();
}

void updater::update(meta_model::element& e) {
    e.contained_by(containing_module(e.name()));

    if (!e.contained_by())
        return;

    auto i(model_.modules().find(e.contained_by()->id()));
    if (i == model_.modules().end()) {
        const auto sn(e.contained_by()->simple());
        BOOST_LOG_SEV(lg, error) << missing_module << sn;
        BOOST_THROW_EXCEPTION(transformation_error(missing_module + sn));
    }
}

}

void modules_transform::
create_missing_modules(meta_model::endomodel& im) {
    internal_modules_builder b;
    meta_model::elements_traversal(im, b);

    for (const auto& pair : b.result()) {
        helpers::name_factory f;
        const auto& ipp(pair.second);
        const auto n(f.build_module_name(im.name(), ipp));
        const auto i(im.modules().find(n.id()));
        if (i == im.modules().end()) {
            auto m(boost::make_shared<meta_model::module>());
            m->name(n);
            m->origin_type(im.origin_type());
            im.modules().insert(std::make_pair(n.id(), m));
        }
    }
}

void modules_transform::
expand_containing_module(meta_model::endomodel& im) {
    updater u(im);
    meta_model::elements_traversal(im, u);
}

void modules_transform::
transform(const context& ctx, meta_model::endomodel& em) {
    tracing::scoped_transform_tracer stp(lg, "modules transform",
        transform_id, em.name().id(), ctx.tracer(), em);

    create_missing_modules(em);
    expand_containing_module(em);

    stp.end_transform(em);
    BOOST_LOG_SEV(lg, debug) << "Finished modules transform.";
}

}

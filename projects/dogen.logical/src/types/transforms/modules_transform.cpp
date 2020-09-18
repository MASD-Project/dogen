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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.identification/types/helpers/logical_name_factory.hpp"
#include "dogen.identification/types/helpers/logical_name_builder.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/modules_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.modules_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string separator(".");
const std::string too_many_containers(
    "Found more than one container for ID: ");

}

namespace dogen::logical::transforms {

using identification::entities::logical_id;
using identification::entities::logical_name;
using namespace entities::structural;

namespace {

class internal_modules_gatherer {
private:
    void process(const logical_name& n);

public:
    void operator()(entities::element&) { }
    void operator()(module& m) { process(m.name()); }
    void operator()(object_template& ot) { process(ot.name()); }
    void operator()(builtin& b) { process(b.name()); }
    void operator()(enumeration& e) { process(e.name()); }
    void operator()(primitive& p) { process(p.name()); }
    void operator()(object& o) { process(o.name()); }
    void operator()(exception& e) { process(e.name()); }
    void operator()(visitor& v) { process(v.name()); }

public:
    const std::unordered_map<std::string, std::list<std::string>>&
    result();

private:
    std::unordered_map<std::string, std::list<std::string>>
    distinct_internal_moduless_;
};

void internal_modules_gatherer::process(const logical_name& n) {
    auto im(n.location().internal_modules());
    while (!im.empty()) {
        const std::string key(boost::join(im, separator));
        distinct_internal_moduless_.insert(std::make_pair(key, im));
        im.pop_back();
    }
}

const std::unordered_map<std::string, std::list<std::string>>&
    internal_modules_gatherer::result() {
    return distinct_internal_moduless_;
}

}

std::unordered_map<std::string, std::list<std::string>>
modules_transform::gather_internal_modules(entities::model& m) {
    internal_modules_gatherer img;
    entities::elements_traversal(m, img);
    return img.result();
}

bool modules_transform::
containing_element_exists(const logical_id& id, const entities::model& m) {
    const auto lambda([&](const auto& container) -> bool {
            const auto i(container.find(id));
            return i != container.end();
        });

    /*
     * Check across all of the containers for this ID.
     */
    const bool mod(lambda(m.structural_elements().modules()));
    const bool mg(lambda(m.decoration_elements().modeline_groups()));
    const bool b(lambda(m.physical_elements().backends()));
    const bool f(lambda(m.physical_elements().facets()));

    /*
     * Count the numbers of matches and ensure we have at most one.
     */
    int found(0);
    if (mod) ++found;
    if (mg) ++found;
    if (b) ++found;
    if (f) ++found;

    if (found > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_containers << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(too_many_containers + id.value()));
    }

    return found == 1;
}

void modules_transform::create_modules(const std::unordered_map<std::string,
    std::list<std::string>>& internal_modules, entities::model& m) {

    identification::helpers::logical_name_factory f;
    for (const auto& pair : internal_modules) {
        /*
         * For each of the internal module paths, create the
         * corresponding element name .
         */
        const auto& im(pair.second);
        const auto n(f.build_module_name(m.name(), im));
        const auto id(n.id());

        /*
         * Check to see if the element name matches any of the
         * possible containing elements in the model. If so, nothing
         * for us to do.
         */
        if (containing_element_exists(id, m))
            continue;

        /*
         * There are no matches. Create a module for it.
         */
        using entities::structural::module;
        auto mod(boost::make_shared<module>());
        mod->name(n);
        mod->provenance().model_type(m.provenance().model_type());

        using variability::entities::configuration;
        mod->configuration(boost::make_shared<configuration>());
        mod->configuration()->name().simple(n.simple());
        mod->configuration()->name().qualified(n.qualified().dot());
        m.structural_elements().modules().insert(std::make_pair(id, mod));
    }
}

void modules_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "modules",
        transform_id, m.name().id().value(), *ctx.tracer(), m);

    const auto im(gather_internal_modules(m));
    create_modules(im, m);

    stp.end_transform(m);
}

}

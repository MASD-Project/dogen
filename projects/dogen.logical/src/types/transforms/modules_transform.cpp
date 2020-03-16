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
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.logical/io/meta_model/model_io.hpp"
#include "dogen.logical/types/meta_model/structural/module.hpp"
#include "dogen.logical/types/meta_model/structural/object.hpp"
#include "dogen.logical/types/meta_model/elements_traversal.hpp"
#include "dogen.logical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/helpers/name_builder.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/modules_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.modules_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string separator(".");
const std::string missing_module("Could not find module: ");

}

namespace dogen::logical::transforms {

namespace {

class internal_modules_gatherer {
private:
    void process(const meta_model::name& n);

public:
    void operator()(meta_model::element&) { }
    void operator()(meta_model::structural::module& m) {
        process(m.name());
    }
    void operator()(meta_model::structural::object_template& ot) {
        process(ot.name());
    }
    void operator()(meta_model::structural::builtin& b) {
        process(b.name());
    }
    void operator()(meta_model::structural::enumeration& e) {
        process(e.name());
    }
    void operator()(meta_model::structural::primitive& p) {
        process(p.name());
    }
    void operator()(meta_model::structural::object& o) {
        process(o.name());
    }
    void operator()(meta_model::structural::exception& e) {
        process(e.name());
    }
    void operator()(meta_model::structural::visitor& v) {
        process(v.name());
    }

public:
    const std::unordered_map<std::string, std::list<std::string>>&
    result();

private:
    std::unordered_map<
        std::string, std::list<std::string>
    > distinct_internal_moduless_;
};

void internal_modules_gatherer::process(const meta_model::name& n) {
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

std::unordered_map<std::string, std::list<std::string>>  modules_transform::
gather_internal_modules(meta_model::model& m) {
    internal_modules_gatherer img;
    meta_model::elements_traversal(m, img);
    return img.result();
}

void modules_transform::create_modules(const std::unordered_map<std::string,
    std::list<std::string>>& internal_modules, meta_model::model& m) {

    helpers::name_factory f;
    for (const auto& pair : internal_modules) {
        const auto& ipp(pair.second);
        const auto n(f.build_module_name(m.name(), ipp));
        const auto i(m.structural_elements().modules().find(
                n.qualified().dot()));
        if (i == m.structural_elements().modules().end()) {
            auto mod(boost::make_shared<meta_model::structural::module>());
            mod->name(n);
            mod->origin_type(m.origin_type());
            mod->configuration(
                boost::make_shared<variability::meta_model::configuration>());
            mod->configuration()->name().simple(n.simple());
            mod->configuration()->name().qualified(n.qualified().dot());
            m.structural_elements().modules().insert(
                std::make_pair(n.qualified().dot(), mod));
        }
    }
}

void modules_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "modules transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto im(gather_internal_modules(m));
    create_modules(im, m);

    stp.end_transform(m);
}

}

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
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn.dia/types/building_error.hpp"
#include "dogen/yarn.dia/types/repository_selector.hpp"
#include "dogen/yarn.dia/types/builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.builder"));

const std::string empty_package_id("Supplied package id is empty");
const std::string missing_module_for_name("Missing module for name: ");
const std::string missing_name_for_id("Missing name for dia object ID: ");

}

namespace dogen {
namespace yarn {
namespace dia {

builder::builder(const std::string& model_name,
    const std::string& external_modules, bool is_target,
    const dynamic::workflow& w,
    const std::unordered_map<std::string, std::list<std::string> >&
    child_id_to_parent_ids) :
    dynamic_workflow_(w) {

    repository_.model(setup_model(model_name, external_modules, is_target));
    repository_.child_id_to_parent_ids(child_id_to_parent_ids);
}

yarn::module builder::create_module_for_model(const yarn::name& n,
    const yarn::origin_types ot) const {

    yarn::module r;
    r.name(n);
    r.origin_type(ot);
    r.generation_type(ot == yarn::origin_types::target ?
        yarn::generation_types::full_generation :
        yarn::generation_types::no_generation);

    return r;
}

yarn::intermediate_model builder::setup_model(const std::string& model_name,
    const std::string& external_modules, bool is_target) const {

    yarn::intermediate_model r;
    yarn::name_factory nf;
    r.name(nf.build_model_name(model_name, external_modules));
    BOOST_LOG_SEV(lg, debug) << "Model: " << r.name().id();

    /*
     * If we are not a target model, nothing else can be said about it
     * at this point in time.
     */
    const auto tg(origin_types::target);
    const auto nyd(origin_types::not_yet_determined);
    const auto ot(is_target ? tg : nyd);

    r.origin_type(ot);
    const auto mm(create_module_for_model(r.name(), ot));
    r.modules().insert(std::make_pair(mm.name().id(), mm));

    return r;
}

void builder::update_documentation(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is a note: " << o.id()
                             << ". Note text: '"
                             << o.comment().original_content() << "'";

    if (o.comment().original_content().empty() ||
        !o.comment().applicable_to_parent_object())
        return;

    const auto& documentation(o.comment().documentation());
    const auto& kvps(o.comment().key_value_pairs());

    using dynamic::scope_types;
    repository_selector rs(repository_);
    if (o.child_node_id().empty()) {
        auto& module(rs.module_for_name(repository_.model().name()));
        module.documentation(documentation);

        const auto scope(scope_types::root_module);
        module.extensions(dynamic_workflow_.execute(scope, kvps));
        return;
    }

    yarn::module& module(rs.module_for_id(o.child_node_id()));
    module.documentation(documentation);

    const auto scope(scope_types::any_module);
    module.extensions(dynamic_workflow_.execute(scope, kvps));
}

void builder::add(const profiled_object& po) {
    const auto& p(po.profile());
    const auto& o(po.object());

    auto& im(repository_.model());
    transformer t(dynamic_workflow_, repository_);

    if (p.is_uml_note())
        update_documentation(o);
    else if (p.is_uml_large_package())
        add(im.modules(), t.to_module(o, p), o.id());
    else if (p.is_enumeration())
        add(im.enumerations(), t.to_enumeration(o, p), o.id());
    else if (p.is_concept())
        add(im.concepts(), t.to_concept(o, p), o.id());
    else if (p.is_exception()) {
        add(im.exceptions(), t.to_exception(o, p), o.id());
    } else {
        const auto ot(p.is_service() ?
            yarn::object_types::user_defined_service :
            yarn::object_types::user_defined_value_object);
        add(im.objects(), t.to_object(o, p, ot), o.id());
    }
}

yarn::intermediate_model builder::build() {
    return repository_.model();
}

} } }

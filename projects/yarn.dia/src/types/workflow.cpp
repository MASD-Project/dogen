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
#include <boost/graph/depth_first_search.hpp>
#include "dogen/dia/types/diagram.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn.dia/types/grapher.hpp"
#include "dogen/yarn.dia/types/context.hpp"
#include "dogen/yarn.dia/types/visitor.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"
#include "dogen/yarn.dia/types/object_processor.hpp"
#include "dogen/yarn.dia/types/reducer.hpp"
#include "dogen/yarn.dia/types/validator.hpp"
#include "dogen/yarn.dia/types/profiled_object_factory.hpp"
#include "dogen/yarn.dia/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.workflow"));

}

namespace dogen {
namespace yarn {
namespace dia {

workflow::workflow(const dynamic::workflow& w) : dynamic_workflow_(w) { }

std::list<profiled_object> workflow::
create_profiled_objects(const dogen::dia::diagram& d) const {
    profiled_object_factory f;
    return f.make(d);
}

std::list<profiled_object> workflow::
reduce_profiled_objects(const std::list<profiled_object>& pos) const {
    reducer rd;
    return rd.reduce(pos);
}

void workflow::
validate_profiled_objects(const std::list<profiled_object>& pos) const {
    validator vd;
    vd.validate(pos);
}

yarn::module workflow::create_module_for_model(const yarn::name& n,
    const yarn::origin_types ot) const {

    yarn::module r;
    r.name(n);
    r.origin_type(ot);
    r.generation_type(ot == yarn::origin_types::target ?
        yarn::generation_types::full_generation :
        yarn::generation_types::no_generation);
    return r;
}

void workflow::initialise_context_activity(const std::string& model_name,
    const std::string& external_modules, bool is_target) {

    /*
     * Reset the context in case we've been called several times.
     */
    context_ = context();

    auto& m(context_.model());
    yarn::name_factory nf;
    m.name(nf.build_model_name(model_name, external_modules));
    BOOST_LOG_SEV(lg, debug) << "Model: " << m.name().id();

    /*
     * If we are not a target model, nothing else can be said about it
     * at this point in time.
     */
    const auto tg(origin_types::target);
    const auto nyd(origin_types::not_yet_determined);
    const auto ot(is_target ? tg : nyd);

    m.origin_type(ot);
    const auto mm(create_module_for_model(m.name(), ot));
    m.modules().insert(std::make_pair(mm.name().id(), mm));
}

graph_type workflow::
generate_graph_activity(const std::list<profiled_object>& pos) {
    grapher g;
    object_processor op;
    g.add(pos);
    g.generate();
    context_.child_id_to_parent_ids(g.child_id_to_parent_ids());
    return g.graph();
}

void workflow::graph_to_context_activity(const graph_type& g) {
    transformer_ = std::unique_ptr<transformer>(
        new transformer(dynamic_workflow_, context_));
    auto lambda([&](const profiled_object& o) {
            transformer_->transform(o.object(), o.profile());
        });
    visitor v(lambda);
    boost::depth_first_search(g, boost::visitor(v));
}

yarn::intermediate_model workflow::execute(const dogen::dia::diagram& d,
    const std::string& model_name, const std::string& external_modules,
    bool is_target) {

    const auto original(create_profiled_objects(d));
    const auto reduced(reduce_profiled_objects(original));
    validate_profiled_objects(reduced);

    initialise_context_activity(model_name, external_modules, is_target);
    graph_to_context_activity(generate_graph_activity(reduced));

    BOOST_LOG_SEV(lg, debug) << "Final model: " << context_.model();
    return context_.model();
}

} } }

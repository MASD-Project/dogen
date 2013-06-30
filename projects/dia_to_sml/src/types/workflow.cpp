/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/grapher.hpp"
#include "dogen/dia_to_sml/types/context.hpp"
#include "dogen/dia_to_sml/types/visitor.hpp"
#include "dogen/dia_to_sml/types/transformer.hpp"
#include "dogen/dia_to_sml/types/identifier_parser.hpp"
#include "dogen/dia_to_sml/types/processor.hpp"
#include "dogen/dia_to_sml/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.workflow"));

}

namespace dogen {
namespace dia_to_sml {

workflow::workflow() { }

workflow::~workflow() noexcept { }

void workflow::initialise_context_activity(const std::string& model_name,
    const std::string& external_module_path, bool is_target) {

    context_ = context();

    const auto epp(identifier_parser::parse_scoped_name(external_module_path));
    context_.model().name().external_module_path(epp);
    context_.model().name().model_name(model_name);
    context_.is_target(is_target);
    context_.model().is_system(false);
}

graph_type workflow::build_graph_activity(const dia::diagram& diagram) {
    grapher g;
    processor p;
    for (const auto& l : diagram.layers()) {
        for (const auto& o : l.objects()) {
            const auto po(p.process(o));

            if (!g.is_relevant(po))
                continue;

            g.add(po);
        }
    }

    g.build();
    context_.child_id_to_parent_ids(g.child_id_to_parent_ids());
    context_.parent_ids(g.parent_ids());
    context_.top_level_module_names(g.top_level_module_names());
    return g.graph();
}

void workflow::transformation_activity(const processed_object& o) {
    const auto p(profiler_.generate(o));
    validator_.validate(p);
    transformer_->transform(o, p);
}

void workflow::graph_to_context_activity(const graph_type& g) {
    transformer_ = std::unique_ptr<transformer>(new transformer(context_));

    using namespace std::placeholders;
    const auto f(std::bind(&workflow::transformation_activity, this, _1));
    visitor v(f);
    boost::depth_first_search(g, boost::visitor(v));
}

void workflow::post_process_model_activity() {
    for (auto& pair : context_.model().objects()) {
        auto i(context_.leaves().find(pair.first));
        if (i == context_.leaves().end())
            continue;

        // for every base (abstract) type which has concrete
        // implementations (leafs), find them and add them to the type
        // itself; then add each leaf type to the model's leaf
        // container.
        pair.second->leaves(i->second);
        for (const auto& j : i->second)
            context_.model().leaves().insert(j);
    }
}

sml::model workflow::execute(const dia::diagram& diagram,
    const std::string& model_name, const std::string& external_module_path,
    bool is_target) {

    initialise_context_activity(model_name, external_module_path, is_target);
    graph_to_context_activity(build_graph_activity(diagram));
    post_process_model_activity();

    BOOST_LOG_SEV(lg, debug) << "Final model: " << context_.model();
    return context_.model();
}

} }

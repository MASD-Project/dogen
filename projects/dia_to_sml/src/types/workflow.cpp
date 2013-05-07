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
#include "dogen/dia_to_sml/types/graph_builder.hpp"
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

void workflow::initialise_context(const std::string& model_name,
    const std::string& external_package_path, bool is_target) {

    context_ = context();

    const auto epp(identifier_parser::parse_scoped_name(external_package_path));
    context_.model().external_package_path(epp);
    context_.model().name(model_name);
    context_.is_target(is_target);
}

graph_type workflow::build_graph(const dia::diagram& diagram) {
    graph_builder b;
    processor p;
    for (const auto& l : diagram.layers()) {
        for (const auto& o : l.objects()) {
            const auto po(p.process(o));
            b.add(po);
        }
    }

    b.build();
    context_.child_to_parent(b.child_to_parent());
    context_.parent_ids(b.parent_ids());
    context_.top_level_package_names(b.top_level_package_names());
    return b.graph();
}

void workflow::transformation_sub_workflow(const processed_object& o) {
    const auto op(profiler_.profile(o));
    validator_.validate(op);
    return transformer_->transform(o, op);
}

void workflow::graph_to_context(const graph_type& g) {
    transformer_ = std::unique_ptr<transformer>(new transformer(context_));

    using namespace std::placeholders;
    const auto f(std::bind(&workflow::transformation_sub_workflow, this, _1));
    visitor v(f);
    boost::depth_first_search(g, boost::visitor(v));
}

void workflow::post_process_model() {
    context_.model().is_system(false);
    for (auto& pair : context_.model().pods()) {
        auto j(context_.leaves().find(pair.first));
        if (j != context_.leaves().end()) {
            pair.second.leaves(j->second);
            for (const auto k : j->second)
                context_.model().leaves().insert(k);
        }
    }
}

sml::model workflow::execute(const dia::diagram& diagram,
    const std::string& model_name, const std::string& external_package_path,
    bool is_target) {

    initialise_context(model_name, external_package_path, is_target);
    graph_to_context(build_graph(diagram));
    post_process_model();

    BOOST_LOG_SEV(lg, debug) << "Final workflow model: " << context_.model();
    return context_.model();
}

} }

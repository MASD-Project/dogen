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
#include "dogen/utility/string/splitter.hpp"
#include "dogen/dia/types/diagram.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/grapher.hpp"
#include "dogen/dia_to_sml/types/context.hpp"
#include "dogen/dia_to_sml/types/visitor.hpp"
#include "dogen/dia_to_sml/types/transformer.hpp"
#include "dogen/dia_to_sml/types/object_processor.hpp"
#include "dogen/dia_to_sml/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.workflow"));

}

namespace dogen {
namespace dia_to_sml {

workflow::workflow(const dynamic::workflow& w) : dynamic_workflow_(w) { }

sml::qname
workflow::create_qualified_name_for_model(const std::string& model_name,
    const std::string& external_module_path) const {

    sml::qname r;
    using utility::string::splitter;
    const auto epp(splitter::split_scoped(external_module_path));
    r.external_module_path(epp);
    r.model_name(model_name);
    r.simple_name(model_name);

    return r;
}

sml::module workflow::create_module_for_model(const sml::qname& qn,
    const bool is_target) const {

    sml::module r;
    r.name(qn);
    r.origin_type(sml::origin_types::user);
    r.type(is_target ?
        sml::module_types::root_model :
        sml::module_types::model);
    r.generation_type(is_target ?
        sml::generation_types::full_generation :
        sml::generation_types::no_generation);
    return r;
}

void workflow::initialise_context_activity(const std::string& model_name,
    const std::string& external_module_path, bool is_target) {

    context_ = context();
    sml::model& m(context_.model());

    const auto& epp(external_module_path);
    m.name(create_qualified_name_for_model(model_name, epp));
    BOOST_LOG_SEV(lg, debug) << "Target model name: "
                             << sml::string_converter::convert(m.name());

    m.origin_type(sml::origin_types::user);
    m.is_target(is_target);

    const auto mm(create_module_for_model(m.name(), is_target));
    m.modules().insert(std::make_pair(mm.name(), mm));
}

graph_type workflow::generate_graph_activity(const dia::diagram& diagram) {
    grapher g;
    object_processor op;
    for (const auto& l : diagram.layers()) {
        for (const auto& o : l.objects()) {
            const auto po(op.process(o));
            if (g.is_relevant(po))
                g.add(po);
        }
    }

    g.generate();
    context_.child_id_to_parent_ids(g.child_id_to_parent_ids());
    context_.parent_ids(g.parent_ids());
    context_.top_level_module_names(g.top_level_module_names());
    return g.graph();
}

void workflow::transformation_activity(const processed_object& o) {
    auto p(profiler_.generate(o));

    // default to value object if nothing else is set
    if (p.is_uml_class() && (
            !p.is_enumeration() && !p.is_exception() && !p.is_entity() &&
            !p.is_keyed_entity() && !p.is_value_object() && !p.is_service() &&
            !p.is_factory() && !p.is_repository() && !p.is_concept()))
        p.is_value_object(true);

    validator_.validate(p);
    transformer_->transform(o, p);
}

void workflow::graph_to_context_activity(const graph_type& g) {
    transformer_ = std::unique_ptr<transformer>(
        new transformer(dynamic_workflow_, context_));
    const auto f(std::bind(&workflow::transformation_activity, this,
            std::placeholders::_1));
    visitor v(f);
    boost::depth_first_search(g, boost::visitor(v));
}

sml::model workflow::execute(const dia::diagram& diagram,
    const std::string& model_name, const std::string& external_module_path,
    bool is_target) {

    initialise_context_activity(model_name, external_module_path, is_target);
    graph_to_context_activity(generate_graph_activity(diagram));

    BOOST_LOG_SEV(lg, debug) << "Final model: " << context_.model();
    return context_.model();
}

} }

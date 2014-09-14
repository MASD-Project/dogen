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
#include <boost/throw_exception.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/graph_visitor.hpp"
#include "dogen/sml/types/meta_data/enricher_grapher.hpp"
#include "dogen/sml/types/workflow_error.hpp"
#include "dogen/sml/types/meta_data/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.meta_data.workflow"));

const std::string null_registrar("Registrar is null");

}

namespace dogen {
namespace sml {
namespace meta_data {

std::shared_ptr<registrar> workflow::registrar_;

workflow::workflow() {
    if (!registrar_) {
        BOOST_LOG_SEV(lg, error) << null_registrar;
        BOOST_THROW_EXCEPTION(workflow_error(null_registrar));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar was initialised as expected.";
    registrar_->validate();
    BOOST_LOG_SEV(lg, debug) << "Registrar is valid.";
}

sml::meta_data::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<sml::meta_data::registrar>();

    return *registrar_;
}

enricher_graph workflow::build_enricher_graph_activity() {
    BOOST_LOG_SEV(lg, debug) << "Creating enricher's graph.";

    enricher_grapher g;
    g.add_root_enricher(registrar_->root_enricher());
    g.add_ordinary_enrichers(registrar_->ordinary_enrichers());
    g.build();
    return g.graph();
}

void workflow::first_stage_enrichment_activity(const qname& qn) {
    enrichment_sub_workflow_->execute(qn, enrichment_types::first_stage);
}

void workflow::second_stage_enrichment_activity(const qname& qn) {
    enrichment_sub_workflow_->execute(qn, enrichment_types::second_stage);
}

void workflow::
register_root_enricher(std::shared_ptr<enricher_interface> e) {
    registrar().register_root_enricher(e);
}

void workflow::
register_ordinary_enricher(std::shared_ptr<enricher_interface> e) {
    registrar().register_ordinary_enricher(e);
}

void workflow::
execute(const module_containment_graph& g, model& m) {
    BOOST_LOG_SEV(lg, debug) << "Starting meta-data workflow.";

   auto enricher_graph(build_enricher_graph_activity());
    enrichment_sub_workflow_ =
        std::make_shared<enrichment_sub_workflow>(m, enricher_graph);

    const auto first_function(
        std::bind(&workflow::first_stage_enrichment_activity, this,
            std::placeholders::_1));
    graph_visitor<qname> first_visitor(first_function);
    boost::depth_first_search(g, boost::visitor(first_visitor));

    const auto second_function(
        std::bind(&workflow::second_stage_enrichment_activity, this,
            std::placeholders::_1));
    graph_visitor<qname> second_visitor(second_function);
    boost::depth_first_search(g, boost::visitor(second_visitor));

    BOOST_LOG_SEV(lg, debug) << "Finished meta-data workflow.";
}

} } }

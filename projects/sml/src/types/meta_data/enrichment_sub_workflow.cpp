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
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/meta_data/enrichment_types_io.hpp"
#include "dogen/sml/types/graph_visitor.hpp"
#include "dogen/sml/types/meta_data/enrichment_sub_workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.meta_data.enrichment_sub_workflow"));

}

namespace dogen {
namespace sml {
namespace meta_data {


enrichment_sub_workflow::context::context(
    const sml::qname& qname, const enrichment_types enrichment_type)
    : qname_(qname), enrichment_type_(enrichment_type) { }

sml::qname enrichment_sub_workflow::context::qname() const {
    return qname_;
}

enrichment_types enrichment_sub_workflow::context::enrichment_type() const {
    return enrichment_type_;
}

enrichment_sub_workflow::
enrichment_sub_workflow(model& m, enricher_graph& g) : model_(m), graph_(g) { }

void enrichment_sub_workflow::
apply_enricher_activity(std::shared_ptr<enricher_interface> e) {
    apply_enrichment(context_->qname(), context_->enrichment_type(),
        model_.modules(), *e);
    apply_enrichment(context_->qname(), context_->enrichment_type(),
        model_.concepts(), *e);
    apply_enrichment(context_->qname(), context_->enrichment_type(),
        model_.primitives(), *e);
    apply_enrichment(context_->qname(), context_->enrichment_type(),
        model_.enumerations(), *e);
    apply_enrichment(context_->qname(), context_->enrichment_type(),
        model_.objects(), *e);
}

void enrichment_sub_workflow::
execute(const qname& qn, const enrichment_types enrichment_type) {
    BOOST_LOG_SEV(lg, debug) << "Starting enrichment sub workflow for: " << qn
                             << "type: " << enrichment_type;
    context_ = std::make_shared<context>(qn, enrichment_type);

    const auto f(std::bind(&enrichment_sub_workflow::apply_enricher_activity,
            this, std::placeholders::_1));
    graph_visitor<std::shared_ptr<enricher_interface>> v(f);
    boost::depth_first_search(graph_, boost::visitor(v));

    BOOST_LOG_SEV(lg, debug) << "Finsihed enrichment sub workflow for: " << qn
                             << "type: " << enrichment_type;
}

} } }

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
#include <boost/filesystem/path.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/injector.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/json_hydrator.hpp"
#include "dogen/sml/types/merger.hpp"
#include "dogen/sml/types/resolver.hpp"
#include "dogen/sml/types/meta_data/workflow.hpp"
#include "dogen/sml/types/concept_indexer.hpp"
#include "dogen/sml/types/property_indexer.hpp"
#include "dogen/sml/types/association_indexer.hpp"
#include "dogen/sml/types/module_containment_graph.hpp"
#include "dogen/sml/types/module_containment_grapher.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/sml/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.workflow"));

}


namespace dogen {
namespace sml {

class graph_populator {
public:
    graph_populator(module_containment_grapher& grapher) : grapher_(grapher) { }

public:
    void operator()(dogen::sml::type& t) const {
        grapher_.add(t.name(), t.containing_module());
    }

    void operator()(dogen::sml::module& m) const {
        grapher_.add(m.name(), m.containing_module());
    }

    void operator()(dogen::sml::concept& c) const {
        grapher_.add(c.name(), c.containing_module());
    }

private:
    module_containment_grapher& grapher_;
};


workflow::workflow(const config::knitting_settings& s) : settings_(s) { }

bool workflow::is_generatable(const type& t) const {
    const auto gt(t.generation_type());
    return
        gt == sml::generation_types::full_generation ||
        gt == sml::generation_types::partial_generation;
}

bool workflow::has_generatable_types(const sml::model& m) const {
    for (const auto pair : m.objects()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : m.enumerations()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : m.enumerations()) {
        if (is_generatable(pair.second))
            return true;
    }

    return false;
}

void workflow::inject_system_types_activity(std::list<model>& models) const {
    injector i;
    for (auto& m : models)
        i.inject(m);
}

model workflow::
create_merged_model_activity(const std::list<model>& models) const {
    merger mg;
    for (const auto& m : models)
        mg.add(m);

    return mg.merge();
}

void workflow::process_meta_data_activity(model& merged_model) const {
    module_containment_grapher g;
    graph_populator populator(g);
    all_model_items_traversal(merged_model, populator);

    meta_data::workflow w;
    w.execute(g.graph(), merged_model);
}

void workflow::resolve_types_activity(model& merged_model) const {
    resolver res(merged_model);
    res.resolve();
}

void workflow::index_concepts_activity(model& merged_model) const {
    concept_indexer indexer;
    indexer.index(merged_model);
}

void workflow::index_properties_activity(model& merged_model) const {
    property_indexer indexer;
    indexer.index(merged_model);
}

void workflow::index_associations_activity(model& merged_model) const {
    association_indexer indexer;
    indexer.index(merged_model);
}

std::pair<bool, model> workflow::
execute(std::list<model> models) const {
    BOOST_LOG_SEV(lg, debug) << "Starting SML workflow.";

    inject_system_types_activity(models);
    auto r(create_merged_model_activity(models));
    resolve_types_activity(r);
    index_concepts_activity(r);
    index_properties_activity(r);
    index_associations_activity(r);
    process_meta_data_activity(r);

    BOOST_LOG_SEV(lg, debug) << "Finished SML workflow.";

    return std::pair<bool, model> { has_generatable_types(r), r };
}

} }

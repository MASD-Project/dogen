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
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia/types/diagram.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn.dia/types/grapher.hpp"
#include "dogen/yarn.dia/types/visitor.hpp"
#include "dogen/yarn.dia/types/reducer.hpp"
#include "dogen/yarn.dia/types/validator.hpp"
#include "dogen/yarn.dia/types/processed_object_factory.hpp"
#include "dogen/yarn.dia/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.workflow"));

}

namespace dogen {
namespace yarn {
namespace dia {

std::list<processed_object> workflow::
create_processed_objects(const dogen::dia::diagram& d) const {
    processed_object_factory f;
    return f.make(d);
}

std::list<processed_object> workflow::
reduce_processed_objects(const std::list<processed_object>& pos) const {
    reducer rd;
    return rd.reduce(pos);
}

void workflow::
validate_processed_objects(const std::list<processed_object>& pos) const {
    validator vd;
    vd.validate(pos);
}

std::string workflow::
obtain_external_modules(const std::list<processed_object>& pos) const {
    std::string r;
    for (const auto& po : pos) {
        if (po.child_node_id().empty() &&
            po.dia_object_type() == dia_object_types::uml_note &&
            po.comment().applicable_to_parent_object()) {
            return po.comment().external_modules();
        }
    }
    return r;
}

std::pair<graph_type,
          const std::unordered_map<std::string, std::list<std::string>>
          >
workflow::generate_graph(const std::list<processed_object>& pos) {
    grapher g;
    g.add(pos);
    g.generate();
    const auto r(std::make_pair(g.graph(), g.child_id_to_parent_ids()));
    return r;
}

builder workflow::create_builder(const std::string& model_name,
    const std::string& external_modules, const bool is_target,
    const std::unordered_map<std::string, std::list<std::string>>&
    child_id_to_parent_ids) const {

    builder b(model_name, external_modules, is_target, child_id_to_parent_ids);
    return b;
}

yarn::intermediate_model
workflow::generate_model(builder& b, const graph_type& g) {
    visitor v(b);
    boost::depth_first_search(g, boost::visitor(v));
    return b.build();
}

yarn::intermediate_model workflow::execute(const dogen::dia::diagram& d,
    const std::string& model_name, bool is_target) {

    /*
     * Convert the original dia diagram into a list of dia objects
     * reading for processing.
     */
    const auto original(create_processed_objects(d));
    const auto reduced(reduce_processed_objects(original));
    validate_processed_objects(reduced);
    const auto external_modules(obtain_external_modules(reduced));

    /*
     * Create a dependency graph of the objects, and a map of children
     * to their respective parents.
     */
    const auto pair(generate_graph(reduced));
    const auto& g(pair.first);
    const auto& ctp(pair.second);

    /*
     * Go through the dependency graph and build a yarn model from
     * it.
     */
    auto b(create_builder(model_name, external_modules, is_target, ctp));
    const auto r(generate_model(b, g));

    BOOST_LOG_SEV(lg, debug) << "Final model: " << r;
    return r;
}

} } }

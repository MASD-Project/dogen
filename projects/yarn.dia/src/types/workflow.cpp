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
#include <algorithm>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/dia/types/diagram.hpp"
#include "dogen/yarn/io/meta_model/intermediate_model_io.hpp"
#include "dogen/yarn.dia/io/processed_object_io.hpp"
#include "dogen/yarn.dia/types/grapher.hpp"
#include "dogen/yarn.dia/types/visitor.hpp"
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

inline bool is_not_relevant(const processed_object& po) {
    const auto ot(po.dia_object_type());
    const bool is_relevant(
        ot == dia_object_types::uml_large_package ||
        ot == dia_object_types::uml_generalization ||
        ot == dia_object_types::uml_class ||
        ot == dia_object_types::uml_note);

    return !is_relevant;
}

std::list<processed_object> workflow::
create_processed_objects(const dogen::dia::diagram& d) const {
    processed_object_factory f;
    return f.make(d);
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
    const std::string& external_modules,
    const std::unordered_map<std::string, std::list<std::string>>&
    child_id_to_parent_ids) const {

    builder b(model_name, external_modules, child_id_to_parent_ids);
    return b;
}

meta_model::intermediate_model
workflow::generate_model(builder& b, const graph_type& g) {
    visitor v(b);
    boost::depth_first_search(g, boost::visitor(v));
    return b.build();
}

meta_model::intermediate_model
workflow::execute(const dogen::dia::diagram& d, const std::string& model_name) {
    /*
     * Convert the original dia diagram into a list of dia objects
     * reading for processing.
     */
    auto pos(create_processed_objects(d));

    /*
     * Remove all the non-relevant process objects.
     */
    boost::range::remove_erase_if(pos, is_not_relevant);

    validate_processed_objects(pos);
    const auto external_modules(obtain_external_modules(pos));

    /*
     * Create a dependency graph of the objects, and a map of children
     * to their respective parents.
     */
    const auto pair(generate_graph(pos));
    const auto& g(pair.first);
    const auto& ctp(pair.second);

    /*
     * Go through the dependency graph and build a yarn model from
     * it.
     */
    auto b(create_builder(model_name, external_modules, ctp));
    const auto r(generate_model(b, g));

    BOOST_LOG_SEV(lg, debug) << "Final model: " << r;
    return r;
}

} } }

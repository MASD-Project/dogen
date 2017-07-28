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

std::string
workflow::obtain_external_modules(const std::list<processed_object>& pos) {
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

meta_model::intermediate_model
workflow::generate_model(const std::list<processed_object>& pos,
    const std::string& model_name, const std::string& external_modules) {

    /*
     * Create a dependency graph of the objects, and a map of children
     * to their respective parents.
     */
    grapher g;
    g.generate(pos);

    /*
     * Go through the dependency graph and build a yarn model from
     * it.
     */
    builder b(model_name, external_modules, g.child_id_to_parent_ids());
    visitor v(b);
    boost::depth_first_search(g.graph(), boost::visitor(v));
    return b.build();
}

meta_model::intermediate_model
workflow::execute(const dogen::dia::diagram& d, const std::string& model_name) {
    /*
     * Convert the original dia diagram into a list of dia objects
     * reading for processing.
     */
    auto pos(processed_object_factory::make(d));

    /*
     * Remove all the non-relevant process objects.
     */
    boost::range::remove_erase_if(pos, is_not_relevant);

    /*
     * Sanity check the processed objects to make sure they are valid.
     */
    validator::validate(pos);

    /*
     * Now obtain the external module path.
     */
    const auto external_modules(obtain_external_modules(pos));

    /*
     * Finally generate the model.
     */
    const auto r(generate_model(pos, model_name, external_modules));
    BOOST_LOG_SEV(lg, debug) << "Final model: " << r;

    return r;
}

} } }

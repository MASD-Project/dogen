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
#include <set>
#include <list>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/indexing_error.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/relationship_types_io.hpp"
#include "dogen/sml/types/generalization_indexer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("sml.generalization_indexer"));

const std::string child_with_no_parents(
    "Object is child but has no parents. Child: ");
const std::string parent_not_found("Could not find parent: ");

}

namespace dogen {
namespace sml {

void generalization_indexer::
add_leaf(const model& m, const sml::qname& leaf, const sml::object& o,
    std::unordered_map<qname, std::list<qname> >& leaves) const {

    if (!o.is_child())
        return;

    const auto i(o.relationships().find(relationship_types::parents));
    if (i == o.relationships().end() || i->second.empty()) {
        const auto n(string_converter::convert(o.name()));
        BOOST_LOG_SEV(lg, error) << child_with_no_parents << n;
        BOOST_THROW_EXCEPTION(indexing_error(child_with_no_parents + n));
    }

    for (const auto& parent : i->second) {
        auto j(m.objects().find(parent));
        if (j == m.objects().end()) {
            const auto n(string_converter::convert(parent));
            BOOST_LOG_SEV(lg, error) << parent_not_found << n;
            BOOST_THROW_EXCEPTION(indexing_error(parent_not_found + n));
        }

        add_leaf(m, leaf, j->second, leaves);
        leaves[parent].push_back(leaf);
        BOOST_LOG_SEV(lg, debug) << "Type is a leaf of: "
                                 << string_converter::convert(parent);
    }
}

std::unordered_map<qname, std::list<qname> > generalization_indexer::
obtain_leaves(const model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining leaves.";
    std::unordered_map<qname, std::list<qname> > r;
    for (auto& pair : m.objects()) {
        auto& o(pair.second);
        BOOST_LOG_SEV(lg, debug) << "Processing type: "
                                 << string_converter::convert(o.name());

        // FIXME: massive hack. must not add leafs for services.
        const auto uds(object_types::user_defined_service);
        const bool is_service(o.object_type() == uds);
        if (o.is_parent() || !o.is_child() || is_service) {
            BOOST_LOG_SEV(lg, debug) << "Type is not a leaf."
                                     << " is parent: " << o.is_parent()
                                     << " is child: " << o.is_child()
                                     << " is service: " << is_service;
            continue;
        }

        add_leaf(m, o.name(), o, r);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished obtaining leaves: " << r;
    return r;
}

void generalization_indexer::
populate_leaves(const std::unordered_map<qname, std::list<qname> >& leaves,
    model& m) const {

    for (const auto& pair : leaves) {
        const auto& parent(pair.first);
        auto i(m.objects().find(parent));
        if (i == m.objects().end()) {
            const auto n(string_converter::convert(parent));
            BOOST_LOG_SEV(lg, error) << parent_not_found << n;
            BOOST_THROW_EXCEPTION(indexing_error(parent_not_found + n));
        }

        i->second.relationships()[relationship_types::leaves] = pair.second;
        for (const auto& l : pair.second) {
            if (l.model_name() == m.name().model_name())
                m.leaves().insert(l);
        }
    }
}

void generalization_indexer::index(model& m) const {
    const auto l(obtain_leaves(m));
    populate_leaves(l, m);
}

} }

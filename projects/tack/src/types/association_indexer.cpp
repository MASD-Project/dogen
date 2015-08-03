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
#include "dogen/utility/log/logger.hpp"
#include "dogen/tack/types/string_converter.hpp"
#include "dogen/tack/types/indexing_error.hpp"
#include "dogen/tack/io/qname_io.hpp"
#include "dogen/tack/io/relationship_types_io.hpp"
#include "dogen/tack/types/association_indexer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tack.association_indexer"));

const std::string object_not_found("Object not found in object container: ");

}

namespace dogen {
namespace tack {

void association_indexer::remove_duplicates(std::list<qname>& names,
    std::unordered_set<qname> processed) const {
    BOOST_LOG_SEV(lg, debug) << "Removing duplicates from list. Original size: "
                             << names.size() << ". Processed starts with size: "
                             << processed.size();

    auto i(names.begin());
    while (i != names.end()) {
        const auto qn(*i);
        if (processed.find(qn) != processed.end()) {
            const auto j(i++);
            names.erase(j);
            continue;
        }
        ++i;
        processed.insert(qn);
    }

    BOOST_LOG_SEV(lg, debug) << "Removed duplicates from list. final size: "
                             << names.size();
}

void association_indexer::recurse_nested_qnames(const model& m,
    object& o, const nested_qname& nqn, bool& is_pointer) const {
    const auto qn(nqn.type());
    auto& rels(o.relationships());
    if (is_pointer)
        rels[relationship_types::weak_associations].push_back(qn);
    else
        rels[relationship_types::regular_associations].push_back(qn);

    const auto i(m.primitives().find(qn));
    if (i != m.primitives().end()) {
        is_pointer = false;
        return;
    }

    const auto j(m.enumerations().find(qn));
    if (j != m.enumerations().end()) {
        is_pointer = false;
        return;
    }

    const auto k(m.objects().find(qn));
    if (k == m.objects().end()) {
        const auto n(string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << object_not_found << n;
        BOOST_THROW_EXCEPTION(indexing_error(object_not_found + n));
    }

    const auto sp(object_types::smart_pointer);
    is_pointer = k->second.object_type() == sp;

    bool is_first(true);
    for (const auto c : nqn.children()) {
        const auto hc(object_types::hash_container);
        if (is_first && k->second.object_type() == hc)
            rels[relationship_types::hash_container_keys].push_back(c.type());

        recurse_nested_qnames(m, o, c, is_pointer);
        is_first = false;
    }
}

void association_indexer::index_object(const model& m, object& o) const {
    BOOST_LOG_SEV(lg, debug) << "Indexing object: "
                             << string_converter::convert(o.name());

    for (const auto& p : o.local_properties()) {
        const auto nqn(p.type());
        bool is_pointer(nqn.is_pointer());
        recurse_nested_qnames(m, o, nqn, is_pointer);
    }

    auto i(o.relationships().find(relationship_types::regular_associations));
    std::unordered_set<qname> regular_associations;
    if (i != o.relationships().end()) {
        remove_duplicates(i->second);
        for (const auto qn : i->second)
            regular_associations.insert(qn);
    }

    i = o.relationships().find(relationship_types::weak_associations);
    if (i != o.relationships().end()) {
        // ensure we remove any items which are simultaneously regular and
        // weak associations.
        remove_duplicates(i->second, regular_associations);
    }

    const auto hck(relationship_types::hash_container_keys);
    i = o.relationships().find(hck);
    if (i != o.relationships().end())
        remove_duplicates(i->second);
}

void association_indexer::index(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Indexing objects. Total objects: "
                             << m.objects().size();

    for (auto& pair : m.objects()) {
        auto& o(pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        index_object(m, o);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished indexing objects.";
}

} }

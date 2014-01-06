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
#include <unordered_map>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/indexing_error.hpp"
#include "dogen/sml/io/relationship_types_io.hpp"
#include "dogen/sml/types/association_indexer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.association_indexer"));

const std::string object_not_found("Object not found in object container: ");

}

namespace dogen {
namespace sml {

class association_indexer::context {
public:
    context(sml::model& m) : model_(m) { }

public:
    sml::model& model() { return model_; }

private:
    sml::model& model_;
};

void association_indexer::remove_duplicates(std::list<qname>& names,
    std::unordered_set<sml::qname> processed) const {
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

void association_indexer::recurse_nested_qnames(object& o,
    const nested_qname& nqn, bool& is_pointer) const {
    const auto qn(nqn.type());
    auto& rels(o.relationships());
    if (is_pointer)
        rels[relationship_types::weak_associations].push_back(qn);
    else
        rels[relationship_types::regular_associations].push_back(qn);

    const auto i(context_->model().primitives().find(qn));
    if (i != context_->model().primitives().end()) {
        is_pointer = false;
        return;
    }

    const auto j(context_->model().enumerations().find(qn));
    if (j != context_->model().enumerations().end()) {
        is_pointer = false;
        return;
    }

    const auto k(context_->model().objects().find(qn));
    if (k == context_->model().objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << qn;
        BOOST_THROW_EXCEPTION(indexing_error(object_not_found +
                boost::lexical_cast<std::string>(qn)));
    }

    const auto sp(sml::object_types::smart_pointer);
    is_pointer = k->second.object_type() == sp;

    bool is_first(true);
    for (const auto c : nqn.children()) {
        const auto hc(sml::object_types::hash_container);
        if (is_first && k->second.object_type() == hc)
            rels[relationship_types::hash_container_keys].push_back(c.type());

        recurse_nested_qnames(o, c, is_pointer);
        is_first = false;
    }
}

void association_indexer::index_object(object& o) {
    BOOST_LOG_SEV(lg, debug) << "Indexing object: " << o.name().simple_name();

    for (const auto& p : o.local_properties()) {
        const auto nqn(p.type());
        bool is_pointer(nqn.is_pointer());
        recurse_nested_qnames(o, nqn, is_pointer);
    }

    for (const auto& op : o.operations()) {
        for (const auto& p : op.parameters()) {
            bool is_pointer(p.type().is_pointer());
            recurse_nested_qnames(o, p.type(), is_pointer);
        }

        if (!op.type())
            continue;

        const auto nqn(*op.type());
        bool is_pointer(nqn.is_pointer());
        recurse_nested_qnames(o, nqn, is_pointer);
    }

    auto i(o.relationships().find(relationship_types::regular_associations));
    std::unordered_set<sml::qname> regular_associations;
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
}

void association_indexer::index(model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing objects: " << m.objects().size();

    context_ = std::unique_ptr<context>(new context(m));
    for (auto& pair : m.objects()) {
        auto& o(pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        index_object(o);
    }
    context_ = std::unique_ptr<context>();
}

} }

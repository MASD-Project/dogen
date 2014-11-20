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
#include <limits>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/grapher.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/sml/types/graphing_error.hpp"
#include "dogen/sml/types/consumption_workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.consumption_workflow"));

const std::string could_not_find_qname("Could not find qname in model: ");

}

namespace dogen {
namespace sml {

/**
 * @brief Populates the graph with module containment and parenting
 * relationships.
 */
class graph_populator {
public:
    graph_populator(sml::grapher& grapher) : grapher_(grapher) { }

public:
    void operator()(const dogen::sml::object& o) const {
        grapher_.add(o.name(), o.containing_module());

        const auto i(o.relationships().find(relationship_types::parents));
        if (i == o.relationships().end())
            return;

        for (const auto p : i->second)
            grapher_.add(o.name(), p);
    }

    void operator()(const dogen::sml::enumeration& e) const {
        grapher_.add(e.name(), e.containing_module());
    }

    void operator()(const dogen::sml::primitive& p) const {
        grapher_.add(p.name(), p.containing_module());
    }

    void operator()(const dogen::sml::module& m) const {
        grapher_.add(m.name(), m.containing_module());
    }

    void operator()(const dogen::sml::concept& c) const {
        grapher_.add(c.name(), c.containing_module());
    }

private:
    sml::grapher& grapher_;
};

/**
 * @brief Wrapper on boost DFS visitor.
 *
 * @note This entire logic is obviously terrible and terribly
 * inefficient (map lookups for no reason, etc). The point is to get
 * the architecture to work end to end and then replace the
 * implementation hacks afterwards.
 */
class graph_visitor : public boost::default_dfs_visitor {
public:
    graph_visitor() = delete;
    graph_visitor& operator=(const graph_visitor&) = default;
    graph_visitor(const graph_visitor&) = default;
    graph_visitor(graph_visitor&&) = default;

public:
    typedef std::function<void(const qname&)> function_type;

public:
    graph_visitor(const model& m, const unsigned int pass,
        const std::list<std::shared_ptr<consumer_interface>>& c)
        : model_(m), pass_(pass), consumers_(c) { }

private:
    /**
     * @brief Tries to apply the enrichment to the qname.
     *
     * @return true if consumption was performed, false otherwise.
     */
    template<typename T>
    bool try_consuming(const qname& qn,
        const unsigned int pass,
        const std::unordered_map<qname, T>& map,
        const consumer_interface& c) {
        auto i(map.find(qn));
        if (i == map.end())
            return false;

        c.consume(model_, pass, i->second);
        return true;
    }

public:
    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& u, const Graph& g) {
        const auto qn(g[u]);
        for (const auto& c : consumers_) {
            const bool consumed(
                try_consuming(qn, pass_, model_.modules(), *c) ||
                try_consuming(qn, pass_, model_.concepts(), *c) ||
                try_consuming(qn, pass_, model_.primitives(), *c) ||
                try_consuming(qn, pass_, model_.enumerations(), *c) ||
                try_consuming(qn, pass_, model_.objects(), *c));

            if (consumed)
                return;

            const auto n(sml::string_converter::convert(qn));
            BOOST_LOG_SEV(lg, error) << could_not_find_qname << n;
            BOOST_THROW_EXCEPTION(graphing_error(could_not_find_qname + n));
        }
    }

private:
    const model& model_;
    const unsigned int pass_;
    const std::list<std::shared_ptr<consumer_interface>>& consumers_;
};

graph_type consumption_workflow::build_graph_activity(const model& m) const {
    grapher g;
    graph_populator p(g);
    all_model_items_traversal(m, p);
    return g.graph();
}

consumption_workflow::consumers_by_pass_type consumption_workflow::
obtain_consumers_by_pass_activity(const consumer_list_type& consumers) const {
    consumers_by_pass_type r;
    const auto last_pass(std::numeric_limits<unsigned int>::max());
    for (const auto& c : consumers) {
        if (c->consume_last()) {
            r[last_pass].push_back(c);
            continue;
        }

        for (unsigned int i(0); i < c->required_passes(); ++i)
            r[i].push_back(c);
    }
    return r;
}

void consumption_workflow::
consume_elements_activity(const model& model,
    const consumers_by_pass_type& consumers_by_pass,
    const graph_type& graph) const {

    for (const auto& pair : consumers_by_pass) {
        const auto& consumers(pair.second);
        const auto pass(pair.first);
        graph_visitor v(model, pass, consumers);
        boost::depth_first_search(graph, boost::visitor(v));
    }
}

void consumption_workflow::
execute(const model& m, const consumer_list_type& consumers) {
    BOOST_LOG_SEV(lg, debug) << "Starting consumption workflow.";
    const auto g(build_graph_activity(m));
    const auto c(obtain_consumers_by_pass_activity(consumers));
    consume_elements_activity(m, c, g);
    BOOST_LOG_SEV(lg, debug) << "Finished consumption workflow.";
}

} }

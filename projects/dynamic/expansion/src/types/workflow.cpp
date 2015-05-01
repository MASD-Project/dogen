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
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/module_types.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/dynamic/schema/io/scope_types_io.hpp"
#include "dogen/dynamic/schema/io/object_io.hpp"
#include "dogen/dynamic/expansion/types/workflow_error.hpp"
#include "dogen/dynamic/expansion/types/expander_interface.hpp"
#include "dogen/dynamic/expansion/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.expansion.workflow"));

}

namespace dogen {
namespace dynamic {
namespace expansion {

class dispatcher {
public:
    dispatcher(const expander_interface& e) : expander_(e) { }

private:
    template<typename IdentifiableAndExensible>
    void expand(schema::scope_types st, IdentifiableAndExensible& ie) {
        using sml::string_converter;
        BOOST_LOG_SEV(lg, debug) << "Performing expansion: '"
                                 << expander_.name() << "' to '"
                                 << string_converter::convert(ie.name())
                                 << " at scope: " << st;

        // FIXME: consider logging at fine debug
        BOOST_LOG_SEV(lg, debug) << "Before expansion: " << ie.extensions();
        expander_.expand(ie.name(), st, ie.extensions());
        BOOST_LOG_SEV(lg, debug) << "After expansion: " << ie.extensions();
    }

public:
    void operator()(dogen::sml::object& o) {
        expand(schema::scope_types::entity, o);
        // FIXME: expand every property and operation
    }

    void operator()(dogen::sml::enumeration& e) {
        expand(schema::scope_types::entity, e);
    }

    void operator()(dogen::sml::primitive& p) {
        expand(schema::scope_types::entity, p);
    }

    void operator()(dogen::sml::module& m) {
        const auto st(m.type() == sml::module_types::root_model ?
            schema::scope_types::root_module :
            schema::scope_types::any_module);
        expand(st, m);
    }

    void operator()(dogen::sml::concept& c) {
        expand(schema::scope_types::entity, c);
    }

private:
    const expander_interface& expander_;
};

class graph_visitor : public boost::default_dfs_visitor {
public:
    graph_visitor(expansion_context& ec) : context_(ec) { }

public:
    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& u, const Graph& g) {
        const auto expander(g[u]);
        expander->setup(context_);
        dispatcher d(*expander);
        sml::all_model_items_traversal(context_.model(), d);
    }

private:
    expansion_context& context_;
};

std::shared_ptr<expansion::registrar> workflow::registrar_;

expansion::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<expansion::registrar>();

    return *registrar_;
}

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating workflow.";
    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Finished validating workflow.";
}

graph_type workflow::
build_expander_graph_activity(const expansion_types et) const {
    grapher g(et);
    for (auto e : registrar().expanders(et))
        g.add(e);

    g.generate();
    return g.graph();
}

expansion_context workflow::create_expansion_context_activity(
    const config::cpp_options& options,
    const schema::repository& rp,
    const sml::model& m) const {
    return expansion_context(m, rp, options);
}

void workflow::
perform_expansion_activity(const graph_type& g, expansion_context& ec) const {
    graph_visitor v(ec);
    boost::depth_first_search(g, boost::visitor(v));
}

sml::model workflow::execute(
    const expansion_types et,
    const config::cpp_options& options,
    const schema::repository& rp,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Expanding model: "
                             << sml::string_converter::convert(m.name());

    validate();
    auto g(build_expander_graph_activity(et));
    auto ec(create_expansion_context_activity(options, rp, m));
    perform_expansion_activity(g, ec);

    BOOST_LOG_SEV(lg, debug) << "Finished expanding model.";

    return ec.model();
}

} } }

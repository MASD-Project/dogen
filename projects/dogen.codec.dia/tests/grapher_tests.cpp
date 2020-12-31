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
#include <list>
#include <memory>
#include <boost/test/unit_test.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.codec/io/entities/object_io.hpp"
#include "dogen.codec.dia/test/mock_processed_object_factory.hpp"
#include "dogen.codec.dia/types/graphing_error.hpp"
#include "dogen.codec.dia/types/grapher.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"

using namespace dogen::codec::dia;
using dogen::utility::test::contains_checker;
using factory = dogen::codec::dia::test::mock_processed_object_factory;

namespace  {

const std::string test_module("masd.codec.dia.tests");
const std::string test_suite("grapher_tests");
const std::string graph_generated("Graph has already been generated");
const std::string graph_not_generated("Graph has not yet been generated");
const std::string graph_has_cycle("Graph has a cycle");

bool is_root_id(const std::string id) {
    return id == dogen::codec::dia::grapher::root_id();
}

class visitor : public boost::default_dfs_visitor {
public:
    visitor() : objects_(
        new std::list<dogen::codec::entities::object>()) {}

public:
    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& u, const Graph& g) {
        objects_->push_back(g[u]);
    }

    const std::list<dogen::codec::entities::object>& result() {
        return *objects_;
    }

private:
    std::shared_ptr<std::list<dogen::codec::entities::object>>
    objects_;
};

}

using dogen::utility::test::contains_checker;
using dogen::codec::dia::graphing_error;

BOOST_AUTO_TEST_SUITE(grapher_tests)

BOOST_AUTO_TEST_CASE(not_adding_objects_to_graph_produces_only_root_object) {
    SETUP_TEST_LOG_SOURCE("not_adding_objects_to_graph_produces_only_root_object");

    visitor v;
    dogen::codec::dia::grapher g;
    g.generate();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << v.result();

    BOOST_REQUIRE(v.result().size() == 1);
    BOOST_CHECK(is_root_id(v.result().back().id()));
}

BOOST_AUTO_TEST_CASE(adding_unrelated_objects_produces_expected_order) {
    SETUP_TEST_LOG_SOURCE("adding_unrelated_objects_produces_expected_order");
    dogen::codec::dia::grapher g;
    g.add(factory::make_large_package(0));
    g.add(factory::make_class(1));
    g.add(factory::make_class(2));

    visitor v;
    g.generate();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << v.result();

    BOOST_REQUIRE(v.result().size() == 4);

    auto i(v.result().begin());
    BOOST_CHECK(i->id() == factory::to_oject_id(0));
    BOOST_CHECK((++i)->id() == factory::to_oject_id(1));
    BOOST_CHECK((++i)->id() == factory::to_oject_id(2));
    BOOST_CHECK(is_root_id((++i)->id()));
}

BOOST_AUTO_TEST_CASE(adding_generalization_produces_expected_order) {
    SETUP_TEST_LOG_SOURCE("adding_generalization_produces_expected_order");

    dogen::codec::dia::grapher g;
    g.add(factory::make_generalization(0));

    visitor v;
    g.generate();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << v.result();

    BOOST_REQUIRE(v.result().size() == 3);

    auto i(v.result().begin());
    BOOST_CHECK(i->id() == factory::to_oject_id(1));
    BOOST_CHECK((++i)->id() == factory::to_oject_id(2));
    BOOST_CHECK(is_root_id((++i)->id()));
}

BOOST_AUTO_TEST_CASE(adding_generalization_inside_package_produces_expected_order) {
    SETUP_TEST_LOG_SOURCE("adding_generalization_inside_package_produces_expected_order");

    dogen::codec::dia::grapher g;
    g.add(factory::make_generalization_inside_large_package(0));

    visitor v;
    g.generate();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << v.result();

    BOOST_REQUIRE(v.result().size() == 4);

    auto i(v.result().begin());
    BOOST_CHECK(i->id() == factory::to_oject_id(0));
    BOOST_CHECK((++i)->id() == factory::to_oject_id(1));
    BOOST_CHECK((++i)->id() == factory::to_oject_id(2));
    BOOST_CHECK(is_root_id((++i)->id()));
}

BOOST_AUTO_TEST_CASE(generating_after_graph_has_been_generated_throws) {
    SETUP_TEST_LOG("generating_after_graph_has_been_generated_throws");

    dogen::codec::dia::grapher g;
    g.generate();
    contains_checker<graphing_error> c(graph_generated);
    BOOST_CHECK_EXCEPTION(g.generate(), graphing_error, c);
}

BOOST_AUTO_TEST_CASE(adding_object_after_graph_has_been_generated_throws) {
    SETUP_TEST_LOG("adding_object_after_graph_has_been_generated_throws");

    dogen::codec::dia::grapher g1;
    g1.generate();
    const auto o(factory::make_class(0));
    contains_checker<graphing_error> c(graph_generated);
    BOOST_CHECK_EXCEPTION(g1.add(o), graphing_error, c);

    dogen::codec::dia::grapher g2;
    g2.add(o);
    g2.generate();
    BOOST_CHECK_EXCEPTION(g2.add(o), graphing_error, c);
}

BOOST_AUTO_TEST_CASE(querying_state_before_generating_throws) {
    SETUP_TEST_LOG("querying_state_before_generating_throws");

    dogen::codec::dia::grapher g;
    const auto o(factory::make_class(0));
    contains_checker<graphing_error> c(graph_not_generated);
    BOOST_CHECK_EXCEPTION(g.graph(), graphing_error, c);
    BOOST_CHECK_EXCEPTION(g.parent_id_to_child_ids(), graphing_error, c);
}

BOOST_AUTO_TEST_CASE(generating_graph_with_first_degree_cycle_throws) {
    SETUP_TEST_LOG("generating_graph_with_first_degree_cycle_throws");

    dogen::codec::dia::grapher g;
    g.add(factory::make_first_degree_cycle(0));
    contains_checker<graphing_error> c(graph_has_cycle);
    BOOST_CHECK_EXCEPTION(g.generate(), graphing_error, c);
}

BOOST_AUTO_TEST_SUITE_END()

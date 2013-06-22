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
#include <list>
#include <boost/test/unit_test.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia_to_sml/io/processed_object_io.hpp"
#include "dogen/dia_to_sml/test/mock_processed_object_factory.hpp"
#include "dogen/dia_to_sml/types/graphing_error.hpp"
#include "dogen/dia_to_sml/types/grapher.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;
using dogen::utility::test::contains_checker;
using dogen::dia_to_sml::test::mock_processed_object_factory;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("grapher_spec");
const std::string graph_built("Graph has already been built");
const std::string graph_not_built("Graph has not yet been built");
const std::string graph_has_cycle("Graph has a cycle");

bool is_root_id(const std::string id) {
    return id == dogen::dia_to_sml::grapher::root_id();
}

class visitor : public boost::default_dfs_visitor {
public:
    explicit visitor(std::list<dogen::dia_to_sml::processed_object>& o)
        : objects_(o) {}

public:
    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& u, const Graph& g) {
        objects_.push_back(g[u]);
    }

private:
    std::list<dogen::dia_to_sml::processed_object>& objects_;
};

}

using dogen::utility::test::contains_checker;
using dogen::dia_to_sml::graphing_error;

BOOST_AUTO_TEST_SUITE(grapher)

BOOST_AUTO_TEST_CASE(not_adding_objects_to_graph_produces_only_root_object) {
    SETUP_TEST_LOG_SOURCE("not_adding_objects_to_graph_produces_only_root_object");

    std::list<dogen::dia_to_sml::processed_object> o;
    visitor v(o);

    dogen::dia_to_sml::grapher g;
    g.build();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << o;

    BOOST_REQUIRE(o.size() == 1);
    BOOST_CHECK(is_root_id(o.back().id()));
}

BOOST_AUTO_TEST_CASE(adding_unrelated_objects_produces_expected_order) {
    SETUP_TEST_LOG_SOURCE("adding_unrelated_objects_produces_expected_order");
    dogen::dia_to_sml::grapher g;
    g.add(mock_processed_object_factory::build_large_package(0));
    g.add(mock_processed_object_factory::build_class(1));
    g.add(mock_processed_object_factory::build_class(2));

    std::list<dogen::dia_to_sml::processed_object> o;
    visitor v(o);
    g.build();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << o;

    BOOST_REQUIRE(o.size() == 4);

    auto i(o.begin());
    BOOST_CHECK(i->id() == mock_processed_object_factory::to_oject_id(0));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(1));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(2));
    BOOST_CHECK(is_root_id((++i)->id()));
}

BOOST_AUTO_TEST_CASE(adding_generalization_produces_expected_order) {
    SETUP_TEST_LOG_SOURCE("adding_generalization_produces_expected_order");

    dogen::dia_to_sml::grapher g;
    g.add(mock_processed_object_factory::build_generalization(0));

    std::list<dogen::dia_to_sml::processed_object> o;
    visitor v(o);
    g.build();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << o;

    BOOST_REQUIRE(o.size() == 3);

    auto i(o.begin());
    BOOST_CHECK(i->id() == mock_processed_object_factory::to_oject_id(1));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(2));
    BOOST_CHECK(is_root_id((++i)->id()));
}

BOOST_AUTO_TEST_CASE(adding_generalization_inside_package_produces_expected_order) {
    SETUP_TEST_LOG_SOURCE("adding_generalization_inside_package_produces_expected_order");

    dogen::dia_to_sml::grapher g;
    g.add(mock_processed_object_factory::
        build_generalization_inside_large_package(0));

    std::list<dogen::dia_to_sml::processed_object> o;
    visitor v(o);
    g.build();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << o;

    BOOST_REQUIRE(o.size() == 4);

    auto i(o.begin());
    BOOST_CHECK(i->id() == mock_processed_object_factory::to_oject_id(0));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(1));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(2));
    BOOST_CHECK(is_root_id((++i)->id()));
}

BOOST_AUTO_TEST_CASE(building_after_graph_has_been_built_throws) {
    SETUP_TEST_LOG("building_object_after_graph_has_been_built_throws");

    dogen::dia_to_sml::grapher g;
    g.build();
    const auto o(mock_processed_object_factory::build_class(0));
    contains_checker<graphing_error> c(graph_built);
    BOOST_CHECK_EXCEPTION(g.build(), graphing_error, c);
}

BOOST_AUTO_TEST_CASE(adding_object_after_graph_has_been_built_throws) {
    SETUP_TEST_LOG("adding_object_after_graph_has_been_built_throws");

    dogen::dia_to_sml::grapher g1;
    g1.build();
    const auto o(mock_processed_object_factory::build_class(0));
    contains_checker<graphing_error> c(graph_built);
    BOOST_CHECK_EXCEPTION(g1.add(o), graphing_error, c);

    dogen::dia_to_sml::grapher g2;
    g2.add(o);
    g2.build();
    BOOST_CHECK_EXCEPTION(g2.add(o), graphing_error, c);
}

BOOST_AUTO_TEST_CASE(querying_state_before_building_throws) {
    SETUP_TEST_LOG("querying_state_before_building_throws");

    dogen::dia_to_sml::grapher g;
    const auto o(mock_processed_object_factory::build_class(0));
    contains_checker<graphing_error> c(graph_not_built);
    BOOST_CHECK_EXCEPTION(g.graph(), graphing_error, c);
    BOOST_CHECK_EXCEPTION(g.child_to_parents(), graphing_error, c);
    BOOST_CHECK_EXCEPTION(g.parent_ids(), graphing_error, c);
    BOOST_CHECK_EXCEPTION(g.top_level_module_names(), graphing_error, c);
}

BOOST_AUTO_TEST_CASE(building_graph_with_first_degree_cycle_throws) {
    SETUP_TEST_LOG("building_graph_with_first_degree_cycle_throws");

    dogen::dia_to_sml::grapher g;
    g.add(mock_processed_object_factory::build_first_degree_cycle(0));
    contains_checker<graphing_error> c(graph_has_cycle);
    BOOST_CHECK_EXCEPTION(g.build(), graphing_error, c);
}

BOOST_AUTO_TEST_SUITE_END()

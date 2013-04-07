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
#include <boost/test/unit_test.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/io/object_io.hpp"
#include "dogen/dia/test/mock_object_factory.hpp"
#include "dogen/dia_to_sml/types/building_error.hpp"
#include "dogen/dia_to_sml/types/graph_builder.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;
using dogen::utility::test::contains_checker;
using dogen::dia::test::mock_object_factory;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("graph_builder_spec");
const std::string adding_after_build("Cannot add object after building");

class empty_graph_visitor : public boost::default_dfs_visitor {
public:
    empty_graph_visitor(bool& found_root, unsigned int& count)
        : found_root_(found_root), count_(count) {
        found_root_ = false;
        count_ = 0;
    }

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        BOOST_REQUIRE_MESSAGE(!found_root_, "Expected only one root");
        BOOST_REQUIRE_MESSAGE(++count_ == 1, "Expected only one node");

        const dogen::dia::object o(g[u]);
        found_root_ = o.id() == dogen::dia_to_sml::graph_builder::root_id();
        BOOST_REQUIRE_MESSAGE(found_root_, "Unexpected vertex");
    }

private:
    bool& found_root_;
    unsigned int& count_;
};

class n_objects_graph_visitor : public boost::default_dfs_visitor {
public:
    n_objects_graph_visitor(bool& found_root, unsigned int& count)
        : found_root_(found_root), count_(count) {
        found_root_ = false;
        count_ = 0;
    }

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        ++count_;
        const dogen::dia::object o(g[u]);
        if (!found_root_)
            found_root_ = o.id() == dogen::dia_to_sml::graph_builder::root_id();
    }

private:
    bool& found_root_;
    unsigned int& count_;
};

}

using dogen::utility::test::contains_checker;
using dogen::dia_to_sml::building_error;

BOOST_AUTO_TEST_SUITE(graph_builder)

BOOST_AUTO_TEST_CASE(building_a_graph_with_no_objects_results_in_just_root_visit) {
    SETUP_TEST_LOG("building_a_graph_with_no_objects_results_in_just_root_visit");

    bool found_root(false);
    unsigned int count(0);
    empty_graph_visitor v(found_root, count);

    dogen::dia_to_sml::graph_builder b;
    boost::depth_first_search(b.build(), boost::visitor(v));
    BOOST_CHECK(found_root);
    BOOST_CHECK(count == 1);
}

BOOST_AUTO_TEST_CASE(building_a_graph_with_n_relevant_objects_results_in_n_plus_one_visits) {
    SETUP_TEST_LOG("building_a_graph_with_n_relevant_objects_results_in_n_plus_one_visits");

    dogen::dia_to_sml::graph_builder b;
    unsigned int id(0);
    b.add(mock_object_factory::build_large_package(id++));
    b.add(mock_object_factory::build_generalization(id));

    bool found_root(false);
    unsigned int count(0);
    n_objects_graph_visitor v(found_root, count);
    boost::depth_first_search(b.build(), boost::visitor(v));

    BOOST_CHECK(found_root);
    BOOST_CHECK(count == 5);
}

BOOST_AUTO_TEST_CASE(adding_object_after_graph_has_been_built_throws) {
    SETUP_TEST_LOG("adding_object_after_graph_has_been_built_throws");

    dogen::dia_to_sml::graph_builder b1;
    b1.build();
    const dogen::dia::object o(mock_object_factory::build_class(0));
    contains_checker<building_error> c(adding_after_build);
    BOOST_CHECK_EXCEPTION(b1.add(o), building_error, c);

    dogen::dia_to_sml::graph_builder b2;
    b2.add(o);
    b2.build();
    BOOST_CHECK_EXCEPTION(b2.add(o), building_error, c);
}

BOOST_AUTO_TEST_SUITE_END()

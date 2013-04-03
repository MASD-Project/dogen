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
#include "dogen/dia_to_sml/types/transformation_error.hpp"
#include "dogen/dia_to_sml/types/graph_builder.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("graph_builder_spec");

class empty_graph_visitor : public boost::default_dfs_visitor {
public:
    empty_graph_visitor() : found_root_(false), count_(0) {}

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        using dogen::dia_to_sml::transformation_error;
        if (found_root_)
            throw transformation_error("Expected only one root");

        ++count_;
        if (count_ != 1)
            throw transformation_error("Expected only one node");

        const dogen::dia::object o(g[u]);
        found_root_ = o.id() == dogen::dia_to_sml::graph_builder::root_id();
        // std::cout << o.id() << std::endl << found_root_ << std::endl;

        if (!found_root_)
            throw transformation_error("Unexpected vertex");
    }

public:
    bool found_root() const { return found_root_; }
    unsigned int count() const { return count_; }

private:
    bool found_root_;
    unsigned int count_;
};

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(graph_builder)

BOOST_AUTO_TEST_CASE(building_a_graph_with_no_objects_results_in_no_visits) {
    SETUP_TEST_LOG("building_a_graph_with_no_objects_results_in_no_visits");

    dogen::dia_to_sml::graph_builder gb;
    empty_graph_visitor v;
    boost::depth_first_search(gb.graph(), boost::visitor(v));
    // BOOST_CHECK(v.found_root());
    // BOOST_CHECK(v.count() == 1);
}

BOOST_AUTO_TEST_SUITE_END()

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
#ifndef DOGEN_UTILITY_TEST_IO_TESTER_HPP
#define DOGEN_UTILITY_TEST_IO_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/stream_translator.hpp>
#include <boost/property_tree/exceptions.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace dogen {
namespace utility {
namespace test {

/**
 * @brief Ensures the inserter operator produces valid JSON.
 */
template<typename Entity>
class io_tester {
public:
    typedef Entity entity_type;

public:
    static void inserter_operator_produces_valid_json(const Entity& /*a*/) {
        // FIXME: this test is disabled until we move to latest boost
        // because it fails to compile with C++11 on.
        // https://svn.boost.org/trac/boost/ticket/6785
        // try {
        //     boost::property_tree::basic_ptree<std::string, std::string> pt;
        //     std::stringstream s;
        //     s << a;
        //     boost::property_tree::json_parser::read_json(s, pt);
        // } catch(boost::property_tree::json_parser::json_parser_error& e) {
        //     BOOST_FAIL("Failed to parse JSON: " << e.what());
        // }
    }
};

} } }

#endif

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
#include <array>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/io/object_io.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/test/mock_intermediate_model_factory.hpp"
#include "dogen/yarn/types/modules_expander.hpp"
#include "dogen/yarn/types/expander.hpp"

/*
using dogen::yarn::object_types;

namespace {

using dogen::yarn::test::mock_intermediate_model_factory;
const mock_intermediate_model_factory::flags flags;
const mock_intermediate_model_factory factory(flags);

const std::string test_module("yarn");
const std::string test_suite("injector_spec");

}

using dogen::utility::test::contains_checker;
using dogen::yarn::expansion_error;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(expander)

BOOST_AUTO_TEST_CASE(model_with_type_with_missing_modules_gets_correctly_expanded) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_missing_modules_gets_correctly_expanded");

    auto m(factory.make_single_type_model());
    BOOST_REQUIRE(m.objects().size() == 3);
    BOOST_REQUIRE(m.modules().empty());
    BOOST_REQUIRE(m.primitives().empty());
    BOOST_REQUIRE(m.enumerations().empty());
    BOOST_REQUIRE(m.concepts().empty());

    dogen::yarn::modules_expander me;
    me.expand(m);

    BOOST_CHECK(m.objects().size() == 3);
    BOOST_CHECK(m.modules().size() == 3);

    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto n(o.name());

        if (!n.location().internal_module_path().empty()) {
            bool module_found(false);
            for (const auto& pair : m.modules()) {
                const auto mod(pair.second);
                auto pp(mod.name().location().internal_module_path());
                pp.push_back(mod.name().simple());
                BOOST_LOG_SEV(lg, info) << "Converted path: " << pp;
                if (n.location().internal_module_path() == pp) {
                    module_found = true;
                    break;
                }
            }

            if (!module_found)
                BOOST_LOG_SEV(lg, error) << "Object has undefined module: "
                                         << n.qualified();
            BOOST_CHECK(module_found);
        }
    }

    BOOST_CHECK(m.primitives().empty());
    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.concepts().empty());
}

}
*/

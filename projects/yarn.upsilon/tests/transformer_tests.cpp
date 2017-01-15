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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/io/primitive_io.hpp"
#include "dogen/yarn/test/mock_intermediate_model_factory.hpp"
#include "dogen/upsilon/test/mock_model_factory.hpp"
#include "dogen/upsilon/types/primitive.hpp"
#include "dogen/upsilon/io/primitive_io.hpp"
#include "dogen/yarn.upsilon/types/transformer.hpp"

namespace {

const std::string empty;
const std::string test_module("yarn.upsilon");
const std::string test_suite("transformer_tests");

using dogen::yarn::test::mock_intermediate_model_factory;

/* @note tagging should make no difference to tests, and not having tags
 * makes the model dumps easier to understand.
 *
 * However, strictly speaking, tagging happens before expansion so it
 * would be more truthful to use a tagged model in the tests.
 */
const mock_intermediate_model_factory::flags flags(
    false/*tagged*/, false/*merged*/, false/*resolved*/,
    true/*concepts_indexed*/, true/*attributes_indexed*/,
    false/*associations_indexed*/);
const mock_intermediate_model_factory yarn_factory(flags);
const auto ot(dogen::yarn::origin_types::target);

}

using dogen::upsilon::test::mock_model_factory;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(transformer_tests)

BOOST_AUTO_TEST_CASE(upsilon_primitive_transforms_into_expected_yarn_primitive) {
    SETUP_TEST_LOG_SOURCE("upsilon_primitive_transforms_into_expected_yarn_primitive");

    const auto model_name(yarn_factory.model_name(0));
    const auto i(mock_model_factory::make_primitive(0));
    BOOST_LOG_SEV(lg, debug) << "input: " << i;

    const auto e(yarn_factory.make_primitive(0, model_name, ot));
    const auto ot(e.origin_type());

    dogen::yarn::upsilon::transformer t;
    const auto a(t.to_primitive(ot, model_name, i));

    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_SUITE_END()

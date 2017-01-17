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
#include <set>
#include <array>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/intermediate_model_validator.hpp"
#include "dogen/yarn/types/validation_error.hpp"
#include "dogen/yarn/test/mock_intermediate_model_factory.hpp"

namespace {

const std::string test_module("yarn");
const std::string test_suite("validator_tests");

using dogen::yarn::test::mock_intermediate_model_factory;
const mock_intermediate_model_factory::flags flags;
const mock_intermediate_model_factory factory(flags);

const std::string invalid_id("INVALID");
const std::string invalid_model_name("INVALID");

const std::string incorrect_model("Type does not belong to this model");
const std::string inconsistent_kvp("Inconsistency between key and value");

}

using dogen::utility::test::contains_checker;
using dogen::yarn::validation_error;

BOOST_AUTO_TEST_SUITE(merger_tests)

BOOST_AUTO_TEST_CASE(type_with_incorrect_model_name_throws) {
    SETUP_TEST_LOG_SOURCE("type_with_incorrect_model_name_throws");
    const auto ot(dogen::yarn::origin_types::target);
    auto m(factory.make_single_type_model(ot));

    m.name().location().model_modules().clear();
    m.name().location().model_modules().push_back(invalid_model_name);
    m.language(dogen::yarn::languages::cpp);
    BOOST_LOG_SEV(lg, debug) << "Model: " << m;

    dogen::yarn::intermediate_model_validator v;
    contains_checker<validation_error> c(incorrect_model);
    BOOST_CHECK_EXCEPTION(v.validate(m), validation_error, c);
}

BOOST_AUTO_TEST_CASE(type_with_inconsistent_key_value_pair_throws) {
    SETUP_TEST_LOG_SOURCE("type_with_inconsistent_key_value_pair_throws");

    const auto ot(dogen::yarn::origin_types::target);
    auto m(factory.make_multi_type_model(0, 2, ot));
    m.objects().begin()->second.name().id(invalid_id);
    m.language(dogen::yarn::languages::cpp);
    BOOST_LOG_SEV(lg, debug) << "Model: " << m;

    dogen::yarn::intermediate_model_validator v;
    contains_checker<validation_error> c(inconsistent_kvp);
    BOOST_CHECK_EXCEPTION(v.validate(m), validation_error, c);
}

BOOST_AUTO_TEST_SUITE_END()

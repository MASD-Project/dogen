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
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/validation_error.hpp"
#include "dogen.logical/test/mock_model_factory.hpp"
#include "dogen.logical/types/helpers/pre_assembly_validator.hpp"

namespace {

const std::string test_module("dogen.logical.tests");
const std::string test_suite("pre_assembly_validator_tests");

using dogen::logical::test::mock_model_factory;
const mock_model_factory::flags flags;
const mock_model_factory factory(flags);

const std::string invalid_id("INVALID");
const std::string invalid_model_name("INVALID");

const std::string incorrect_model("Type does not belong to this model");
const std::string inconsistent_kvp("Inconsistency between key and value");

}

using dogen::utility::test::contains_checker;
using dogen::identification::entities::model_type;
using dogen::identification::entities::technical_space;
using dogen::logical::helpers::validation_error;
using dogen::logical::helpers::pre_assembly_validator;


BOOST_AUTO_TEST_SUITE(pre_assembly_validator_tests)

BOOST_AUTO_TEST_CASE(type_with_incorrect_model_name_throws) {
    SETUP_TEST_LOG_SOURCE("type_with_incorrect_model_name_throws");
    const auto mt(model_type::target);
    auto m(factory.make_single_type_model(mt));

    m.name().location().model_modules().clear();
    m.name().location().model_modules().push_back(invalid_model_name);
    m.input_technical_space(technical_space::cpp);
    BOOST_LOG_SEV(lg, debug) << "Model: " << m;

    contains_checker<validation_error> c(incorrect_model);
    BOOST_CHECK_EXCEPTION(
        pre_assembly_validator::validate(m), validation_error, c);
}

BOOST_AUTO_TEST_CASE(type_with_inconsistent_key_value_pair_throws) {
    SETUP_TEST_LOG_SOURCE("type_with_inconsistent_key_value_pair_throws");

    const auto mt(model_type::target);
    auto m(factory.make_multi_type_model(0, 2, mt));

    using dogen::identification::entities::logical_id;
    logical_id id(invalid_id);
    m.structural_elements().objects().begin()->second->name().id(id);
    m.input_technical_space(technical_space::cpp);
    BOOST_LOG_SEV(lg, debug) << "Model: " << m;

    contains_checker<validation_error> c(inconsistent_kvp);
    BOOST_CHECK_EXCEPTION(pre_assembly_validator::validate(m),
        validation_error, c);
}

BOOST_AUTO_TEST_SUITE_END()

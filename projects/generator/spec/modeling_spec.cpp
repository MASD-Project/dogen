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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/generator/modeling/validation_error.hpp"
#include "dogen/utility/test/xml_serialization_helper.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/test_data/codegen_tds.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/dia/xml/hydrator.hpp"
#include "dogen/generator/modeling/dia_to_sml.hpp"
#include "dogen/generator/modeling/sml_builder.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/sml/serialization/model_ser.hpp"

namespace  {

const std::string empty;
const bool verbose(true);
const std::string schema_name("some_schema");

const std::string test_module("generator");
const std::string test_suite("modeling_spec");
const std::string class_in_a_package_model_name("class_in_a_package");
const std::string type_name_prefix("some_type_");
const std::string model_name_prefix("some_model_");
const std::string property_name_prefix("some_property_");

const std::string incorrect_model("Pod does not belong to this model");
const std::string inconsistent_kvp("Inconsistency between key and value");
const std::string missing_target("No target model found");
const std::string too_many_targets("Only one target expected.");
const std::string undefined_type("Pod has property with undefined type");
const std::string missing_parent("Pod's parent could not be located");
const std::string incorrect_meta_type("Pod has incorrect meta_type");

std::string type_name(unsigned int i) {
    std::ostringstream stream;
    stream << type_name_prefix << i;
    return stream.str();
}

std::string model_name(unsigned int i) {
    std::ostringstream stream;
    stream << model_name_prefix << i;
    return stream.str();
}

std::string property_name(unsigned int i) {
    std::ostringstream stream;
    stream << property_name_prefix << i;
    return stream.str();
}

dogen::sml::pod mock_pod(unsigned int i, std::string model_name) {
    dogen::sml::qualified_name qn;
    qn.model_name(model_name);
    qn.type_name(type_name(i));
    qn.meta_type(dogen::sml::meta_types::pod);

    dogen::sml::pod r;
    r.name(qn);
    r.generate(true);
    return r;
}

dogen::sml::pod mock_pod(unsigned int i) {
    return mock_pod(i, model_name(i));
}

}

BOOST_AUTO_TEST_SUITE(modeling)

BOOST_AUTO_TEST_CASE(class_in_a_package_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG_SOURCE("class_in_a_package_dia_transforms_into_expected_sml");
    using dogen::utility::test_data::dia_sml;
    auto input_path(dia_sml::expected_class_in_a_package_dia_xml());

    using dogen::utility::test::xml_deserialize;
    const auto input(xml_deserialize<dogen::dia::diagram>(input_path));

    const std::string epp;
    const bool is_target(true);
    const bool verbose(true);

    using dogen::generator::modeling::dia_to_sml;
    dia_to_sml dia_to_sml(
        input, class_in_a_package_model_name, epp, is_target, verbose);
    dogen::sml::model actual(dia_to_sml.transform());

    auto actual_path(dia_sml::actual_class_in_a_package_sml_xml());
    auto expected_path(dia_sml::expected_class_in_a_package_sml_xml());
    BOOST_LOG_SEV(lg, debug) << "diff -u " << expected_path.string()
                             << " " << actual_path.string();

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_object(expected_path, actual_path, actual));
}

BOOST_AUTO_TEST_CASE(building_n_distinct_models_with_one_pod_each_results_in_n_pods_in_combined_model) {
    SETUP_TEST_LOG("building_n_distinct_models_with_one_pod_each_results_in_n_pods_in_combined_model");
    const unsigned int n(5);
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    std::list<dogen::sml::qualified_name> names;
    for (unsigned int i(0); i < n; ++i) {
        using namespace dogen::sml;
        pod p(mock_pod(i));
        names.push_back(p.name());

        std::unordered_map<qualified_name, pod> pods { { p.name(), p } };
        model m;
        m.name(model_name(i));
        m.pods(pods);
        i == 0 ? builder.add_target(m) : builder.add(m);
    }

    const auto combined(builder.build());
    BOOST_CHECK(combined.pods().size() == n);
    BOOST_CHECK(combined.primitives().empty());

    const auto pods(combined.pods());
    for (const auto qn : names) {
        BOOST_CHECK(pods.find(qn) != pods.end());
    }
}

BOOST_AUTO_TEST_CASE(building_empty_model_results_in_empty_combined_model) {
    SETUP_TEST_LOG("building_empty_model_results_in_empty_combined_model");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);
    dogen::sml::model m;
    builder.add_target(m);

    const auto combined(builder.build());
    BOOST_CHECK(combined.pods().empty());
    BOOST_CHECK(combined.primitives().empty());
}

BOOST_AUTO_TEST_CASE(type_with_incorrect_model_name_throws) {
    SETUP_TEST_LOG("type_with_incorrect_model_name_throws");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);
    using namespace dogen::sml;
    pod p(mock_pod(1));

    model m;
    m.name(model_name(0));
    std::unordered_map<qualified_name, pod> pods { { p.name(), p } };
    m.pods(pods);
    builder.add_target(m);

    using dogen::generator::modeling::validation_error;
    auto lambda([](const validation_error& e) {
            const std::string msg(e.what());
            return boost::contains(msg, incorrect_model);
        });
    BOOST_CHECK_EXCEPTION(builder.build(), validation_error, lambda);
}

BOOST_AUTO_TEST_CASE(type_with_inconsistent_key_value_pair_throws) {
    SETUP_TEST_LOG_SOURCE("type_with_inconsistent_key_value_pair_throws");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);
    using namespace dogen::sml;
    pod p(mock_pod(0));
    pod q(mock_pod(1));

    model m;
    m.name(model_name(0));
    std::unordered_map<qualified_name, pod> pods { { p.name(), q } };
    m.pods(pods);
    builder.add_target(m);

    using dogen::generator::modeling::validation_error;
    auto lambda([](const validation_error& e) {
            const std::string msg(e.what());
            return boost::contains(msg, inconsistent_kvp);
        });
    BOOST_CHECK_EXCEPTION(builder.build(), validation_error, lambda);
}

BOOST_AUTO_TEST_CASE(not_adding_a_target_throws) {
    SETUP_TEST_LOG_SOURCE("not_adding_a_target_throws");
    dogen::sml::model m;
    m.name(model_name(0));

    const bool verbose(true);
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);
    builder.add(m);

    using dogen::generator::modeling::validation_error;
    auto lambda([](const validation_error& e) {
            const std::string msg(e.what());
            return boost::contains(msg, missing_target);
        });
    BOOST_CHECK_EXCEPTION(builder.build(), validation_error, lambda);
}

BOOST_AUTO_TEST_CASE(adding_more_than_one_target_throws) {
    SETUP_TEST_LOG("adding_more_than_one_target_throws");
    dogen::sml::model m0;
    m0.name(model_name(0));

    dogen::sml::model m1;
    m1.name(model_name(1));

    dogen::generator::modeling::sml_builder builder(verbose, schema_name);
    builder.add_target(m0);

    using dogen::generator::modeling::validation_error;
    auto lambda([](const validation_error& e) {
            const std::string msg(e.what());
            return boost::contains(msg, too_many_targets);
        });
    BOOST_CHECK_EXCEPTION(builder.add_target(m1), validation_error, lambda);
}

BOOST_AUTO_TEST_CASE(pod_with_property_type_in_the_same_model_results_in_successful_build) {
    SETUP_TEST_LOG("pod_with_property_type_in_the_same_model_results_in_successful_build");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));

    auto props(pod0.properties());
    property p;
    p.name(property_name(0));

    dogen::sml::qualified_name qn;
    qn.type_name(pod1.name().type_name());
    qn.model_name(pod1.name().model_name());
    p.type_name(qn);
    props.push_back(p);
    pod0.properties(props);

    model m;
    m.pods(
        std::unordered_map<qualified_name, pod> {
            { pod0.name(), pod0 },
            { pod1.name(), pod1 }
        });
    m.name(mn);

    builder.add_target(m);

    const auto combined(builder.build());
    BOOST_CHECK(combined.pods().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    const auto pods(combined.pods());
    const auto i(pods.find(pod0.name()));
    BOOST_CHECK(i != pods.end());
    BOOST_CHECK(i->second.properties().size() == 1);
    const auto updated_pod0(i->second.properties()[0]);
    BOOST_CHECK(updated_pod0.type_name().type_name() == pod1.name().type_name());
    BOOST_CHECK(updated_pod0.type_name().meta_type() == meta_types::pod);
}

BOOST_AUTO_TEST_CASE(pod_with_property_type_in_different_model_results_in_successful_build) {
    SETUP_TEST_LOG("pod_with_property_type_in_different_model_results_in_successful_build");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));

    auto props(pod0.properties());
    property p;
    p.name(property_name(0));

    dogen::sml::qualified_name qn;
    qn.type_name(pod1.name().type_name());
    qn.model_name(pod1.name().model_name());
    p.type_name(qn);
    props.push_back(p);
    pod0.properties(props);

    model m0;
    m0.pods(
        std::unordered_map<qualified_name, pod> {
            { pod0.name(), pod0 }
        });
    m0.name(model_name(0));

    model m1;
    m1.pods(
        std::unordered_map<qualified_name, pod> {
            { pod1.name(), pod1 }
        });
    m1.name(model_name(1));

    builder.add_target(m0);
    builder.add(m1);

    const auto combined(builder.build());
    BOOST_CHECK(combined.pods().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    const auto pods(combined.pods());
    const auto i(pods.find(pod0.name()));
    BOOST_CHECK(i != pods.end());
    BOOST_CHECK(i->second.properties().size() == 1);
    const auto updated_pod0(i->second.properties()[0]);
    BOOST_CHECK(updated_pod0.type_name().type_name() == pod1.name().type_name());
    BOOST_CHECK(updated_pod0.type_name().meta_type() == meta_types::pod);
}

BOOST_AUTO_TEST_CASE(pod_with_missing_property_type_throws) {
    SETUP_TEST_LOG("pod_with_missing_property_type_throws");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));

    auto props(pod0.properties());
    property p;
    p.name(property_name(0));

    dogen::sml::qualified_name qn;
    qn.type_name(pod1.name().type_name());
    qn.model_name(pod1.name().model_name());
    p.type_name(qn);
    props.push_back(p);
    pod0.properties(props);

    model m0;
    m0.pods(
        std::unordered_map<qualified_name, pod> {
            { pod0.name(), pod0 }
        });
    m0.name(model_name(0));

    builder.add_target(m0);

    using dogen::generator::modeling::validation_error;
    auto lambda([](const validation_error& e) {
            const std::string msg(e.what());
            return boost::contains(msg, undefined_type);
        });
    BOOST_CHECK_EXCEPTION(builder.build(), validation_error, lambda);
}

BOOST_AUTO_TEST_CASE(pod_with_parent_in_the_same_model_builds_successfully) {
    SETUP_TEST_LOG("pod_with_parent_in_the_same_model_builds_successfully");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod0.parent_name(pod1.name());

    model m;
    m.pods(
        std::unordered_map<qualified_name, pod> {
            { pod0.name(), pod0 },
            { pod1.name(), pod1 }
        });
    m.name(mn);

    builder.add_target(m);

    const auto combined(builder.build());
    BOOST_CHECK(combined.pods().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    const auto pods(combined.pods());
    const auto i(pods.find(pod0.name()));
    BOOST_CHECK(i != pods.end());
    const auto pn(i->second.parent_name());
    BOOST_CHECK(pn);
    BOOST_CHECK(pn->type_name() == pod1.name().type_name());
    BOOST_CHECK(pn->meta_type() == meta_types::pod);
}

BOOST_AUTO_TEST_CASE(pod_with_parent_in_different_models_builds_successfully) {
    SETUP_TEST_LOG("pod_with_parent_in_different_models_builds_successfully");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));
    pod0.parent_name(pod1.name());

    model m0;
    m0.pods(
        std::unordered_map<qualified_name, pod> {
            { pod0.name(), pod0 }
        });
    m0.name(model_name(0));

    model m1;
    m1.pods(
        std::unordered_map<qualified_name, pod> {
            { pod1.name(), pod1 }
        });
    m1.name(model_name(1));

    builder.add_target(m0);
    builder.add(m1);

    const auto combined(builder.build());
    BOOST_CHECK(combined.pods().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    const auto pods(combined.pods());
    const auto i(pods.find(pod0.name()));
    BOOST_CHECK(i != pods.end());
    const auto pn(i->second.parent_name());
    BOOST_CHECK(pn);
    BOOST_CHECK(pn->type_name() == pod1.name().type_name());
    BOOST_CHECK(pn->meta_type() == meta_types::pod);
}

BOOST_AUTO_TEST_CASE(pod_with_third_degree_parent_in_same_model_builds_successfully) {
    SETUP_TEST_LOG("pod_with_third_degree_parent_in_same_model_builds_successfully");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod pod2(mock_pod(2, mn));
    pod pod3(mock_pod(3, mn));

    pod0.parent_name(pod1.name());
    pod1.parent_name(pod2.name());
    pod2.parent_name(pod3.name());

    model m;
    m.pods(
        std::unordered_map<qualified_name, pod> {
            { pod0.name(), pod0 },
            { pod1.name(), pod1 },
            { pod2.name(), pod2 },
            { pod3.name(), pod3 }
        });
    m.name(mn);

    builder.add_target(m);

    const auto combined(builder.build());
    BOOST_CHECK(combined.pods().size() == 4);
    BOOST_CHECK(combined.primitives().empty());

    const auto pods(combined.pods());
    const auto i(pods.find(pod0.name()));
    BOOST_CHECK(i != pods.end());
    const auto pn(i->second.parent_name());
    BOOST_CHECK(pn);
    BOOST_CHECK(pn->type_name() == pod1.name().type_name());
}

BOOST_AUTO_TEST_CASE(pod_with_third_degree_parent_missing_within_single_model_throws) {
    SETUP_TEST_LOG("pod_with_third_degree_parent_missing_within_single_model_throws");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod pod2(mock_pod(2, mn));
    pod pod3(mock_pod(3, mn));

    pod0.parent_name(pod1.name());
    pod1.parent_name(pod2.name());
    pod2.parent_name(pod3.name());

    model m;
    m.pods(
        std::unordered_map<qualified_name, pod> {
            { pod0.name(), pod0 },
            { pod1.name(), pod1 },
            { pod2.name(), pod2 }
        });
    m.name(mn);

    builder.add_target(m);
    using dogen::generator::modeling::validation_error;
    auto lambda([](const validation_error& e) {
            const std::string msg(e.what());
            return boost::contains(msg, missing_parent);
        });
    BOOST_CHECK_EXCEPTION(builder.build(), validation_error, lambda);
}

BOOST_AUTO_TEST_CASE(pod_with_third_degree_parent_in_different_models_builds_successfully) {
    SETUP_TEST_LOG("pod_with_third_degree_parent_in_different_models_builds_successfully");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));
    pod pod2(mock_pod(2));
    pod pod3(mock_pod(3));

    pod0.parent_name(pod1.name());
    pod1.parent_name(pod2.name());
    pod2.parent_name(pod3.name());

    model m0;
    m0.pods(
        std::unordered_map<qualified_name, pod> {
            { pod0.name(), pod0 }
        });
    m0.name(model_name(0));

    model m1;
    m1.pods(
        std::unordered_map<qualified_name, pod> {
            { pod1.name(), pod1 }
        });
    m1.name(model_name(1));

    model m2;
    m2.pods(
        std::unordered_map<qualified_name, pod> {
            { pod2.name(), pod2 }
        });
    m2.name(model_name(2));

    model m3;
    m3.pods(
        std::unordered_map<qualified_name, pod> {
            { pod3.name(), pod3 }
        });
    m3.name(model_name(3));

    builder.add_target(m0);
    builder.add(m1);
    builder.add(m2);
    builder.add(m3);

    const auto combined(builder.build());
    BOOST_CHECK(combined.pods().size() == 4);
    BOOST_CHECK(combined.primitives().empty());

    const auto pods(combined.pods());
    const auto i(pods.find(pod0.name()));
    BOOST_CHECK(i != pods.end());
    const auto pn(i->second.parent_name());
    BOOST_CHECK(pn);
    BOOST_CHECK(pn->type_name() == pod1.name().type_name());
}

BOOST_AUTO_TEST_CASE(pod_with_missing_third_degree_parent_in_different_models_throws) {
    SETUP_TEST_LOG("pod_with_missing_third_degree_parent_in_different_models_throws");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));
    pod pod2(mock_pod(2));
    pod pod3(mock_pod(3));

    pod0.parent_name(pod1.name());
    pod1.parent_name(pod2.name());
    pod2.parent_name(pod3.name());

    model m0;
    m0.pods(
        std::unordered_map<qualified_name, pod> {
            { pod0.name(), pod0 }
        });
    m0.name(model_name(0));

    model m1;
    m1.pods(
        std::unordered_map<qualified_name, pod> {
            { pod1.name(), pod1 }
        });
    m1.name(model_name(1));

    model m2;
    m2.pods(
        std::unordered_map<qualified_name, pod> {
            { pod2.name(), pod2 }
        });
    m2.name(model_name(2));

    builder.add_target(m0);
    builder.add(m1);
    builder.add(m2);

    using dogen::generator::modeling::validation_error;
    auto lambda([](const validation_error& e) {
            const std::string msg(e.what());
            return boost::contains(msg, missing_parent);
        });
    BOOST_CHECK_EXCEPTION(builder.build(), validation_error, lambda);
}

BOOST_AUTO_TEST_CASE(pod_incorrect_meta_type_throws) {
    SETUP_TEST_LOG("pod_incorrect_meta_type_throws");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);

    using namespace dogen::sml;
    pod p(mock_pod(0));

    dogen::sml::qualified_name qn;
    qn.type_name(p.name().type_name());
    qn.model_name(p.name().model_name());
    qn.meta_type(meta_types::primitive);
    p.name(qn);

    model m;
    m.pods(
        std::unordered_map<qualified_name, pod> {
            { p.name(), p }
        });
    m.name(model_name(0));

    builder.add_target(m);

    using dogen::generator::modeling::validation_error;
    auto lambda([](const validation_error& e) {
            const std::string msg(e.what());
            return boost::contains(msg, incorrect_meta_type);
        });
    BOOST_CHECK_EXCEPTION(builder.build(), validation_error, lambda);
}

BOOST_AUTO_TEST_CASE(setting_builder_schema_name_propagates_to_combined_model) {
    SETUP_TEST_LOG("building_empty_model_results_in_empty_combined_model");
    dogen::generator::modeling::sml_builder builder(verbose, schema_name);
    dogen::sml::model m;
    builder.add_target(m);

    const auto combined(builder.build());
    BOOST_CHECK(combined.schema_name() == schema_name);
}

BOOST_AUTO_TEST_SUITE_END()

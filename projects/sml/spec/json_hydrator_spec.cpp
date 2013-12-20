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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/fstream.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/hydration_error.hpp"
#include "dogen/sml/types/json_hydrator.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("json_hydrator_spec");

const std::string model_name("a_model");
const std::string documentation("a_doc");
const std::string type_name("a_type");
const std::string model_key("model_key");
const std::string model_value("model_value");
const std::string odb_pragma_value("odb_pragma_value");
const std::string type_key("type_key");
const std::string type_value("true");
const std::string module_path_key("module_path");
const std::string module_path_value_1("module_1");
const std::string module_path_value_2("module_2");
const std::string module_path_value_3("module_3");

const std::string cpp_std_model_path("library/cpp.std.json");
const std::string cpp_std_model_name("std");
const std::string cpp_boost_model_name("boost");
const std::string cpp_boost_model_path("library/cpp.boost.json");
const std::string hardware_model_path("library/hardware.json");
const std::string hardware_model_name("hardware");

const std::string missing_model_name("model_name");
const std::string missing_type_name("simple_name");
const std::string missing_origin("origin");
const std::string missing_types("types");

const std::string trivial_model(R"({
    "model_name" : "a_model",
    "documentation" : "a_doc",
    "origin" : "system",
    "types" : [
        {
            "meta_type" : "value_object",
            "simple_name" : "a_type",
            "documentation" : "a_doc"
        }
     ]
  }
)");

const std::string tagged_model(R"({
    "model_name" : "a_model",
    "documentation" : "a_doc",
    "origin" : "system",
    "meta_data" : {
            "model_key" : "model_value",
            "ODB_PRAGMA" : "odb_pragma_value"
    },
    "types" : [
        {
            "meta_type" : "value_object",
            "simple_name" : "a_type",
            "documentation" : "a_doc",
            "meta_data" : {
                    "type_key" : true,
                    "ODB_PRAGMA" : "odb_pragma_value"
            }
       }
   ]
}
)");

const std::string no_documentation_model(R"({
    "model_name" : "a_model",
    "origin" : "system",
    "types" : [
        {
            "meta_type" : "value_object",
            "simple_name" : "a_type"
        }
     ]
  }
)");

const std::string no_name_model(R"({
    "origin" : "system",
    "types" : [
        {
            "meta_type" : "value_object",
            "simple_name" : "a_type"
        }
     ]
  }
)");

const std::string no_type_name_model(R"({
    "model_name" : "a_model",
    "origin" : "system",
    "types" : [
        {
            "meta_type" : "value_object"
        }
     ]
  }
)");

const std::string no_origin_model(R"({
    "model_name" : "a_model",
    "types" : [
        {
            "meta_type" : "value_object",
            "simple_name" : "a_type"
        }
     ]
  }
)");

const std::string no_types_model(R"({
    "model_name" : "a_model",
    "origin" : "system"
  }
)");

const std::string empty_types_model(R"({
    "model_name" : "a_model",
    "origin" : "system",
    "types" : [ ]
  }
)");

const std::string module_path_model(R"({
    "model_name" : "a_model",
    "origin" : "system",
    "module_path" : [ "module_1", "module_2", "module_3" ],
    "types" : [
        {
            "meta_type" : "value_object",
            "simple_name" : "a_type",
            "module_path" : [ "module_1" ]
        }
     ]
  }
)");

dogen::sml::model hydrate(const std::string content) {
    std::istringstream s(content);
    dogen::sml::json_hydrator h;
    return h.hydrate(s);
}

}

using dogen::utility::test::contains_checker;
using dogen::sml::hydration_error;

BOOST_AUTO_TEST_SUITE(json_hydrator)

BOOST_AUTO_TEST_CASE(trivial_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("trivial_model_hydrates_into_expected_model");

    const auto m(hydrate(trivial_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_CHECK(m.name().model_name() == model_name);
    BOOST_CHECK(m.name().module_path().empty());
    BOOST_CHECK(m.name().external_module_path().empty());
    BOOST_CHECK(m.documentation() == documentation);

    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& pair(*m.objects().begin());
    const auto& qn(pair.second.name());

    BOOST_CHECK(pair.first == qn);
    BOOST_CHECK(qn.simple_name() == type_name);
    BOOST_CHECK(qn.model_name() == m.name().model_name());
    BOOST_CHECK(qn.module_path().empty());
    BOOST_CHECK(qn.external_module_path().empty());
    BOOST_CHECK(pair.second.documentation() == documentation);
}

BOOST_AUTO_TEST_CASE(tagged_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("tagged_model_hydrates_into_expected_model");

    const auto m(hydrate(tagged_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_CHECK(m.name().model_name() == model_name);
    BOOST_CHECK(m.name().module_path().empty());
    BOOST_CHECK(m.name().external_module_path().empty());
    BOOST_CHECK(m.documentation() == documentation);
    BOOST_CHECK(m.meta_data().size() == 2);

    {
        auto i(m.meta_data().find(dogen::sml::tags::odb_pragma));
        BOOST_REQUIRE(i != m.meta_data().not_found());
        BOOST_REQUIRE(i->second.size() == 1);
        const auto j(i->second.begin());
        BOOST_CHECK(j->second.data() == odb_pragma_value);

        i = m.meta_data().find(model_key);
        BOOST_REQUIRE(i != m.meta_data().not_found());
        BOOST_REQUIRE(i->second.size() == 0);
        BOOST_CHECK(i->second.data() == model_value);
    }

    BOOST_REQUIRE(m.objects().size() == 1);

    const auto& pair(*m.objects().begin());
    const auto& qn(pair.second.name());

    BOOST_CHECK(pair.first == qn);
    BOOST_CHECK(qn.simple_name() == type_name);
    BOOST_CHECK(qn.model_name() == m.name().model_name());
    BOOST_CHECK(qn.module_path().empty());
    BOOST_CHECK(qn.external_module_path().empty());
    BOOST_CHECK(pair.second.documentation() == documentation);

    {
        const auto& o(pair.second);
        auto i(o.meta_data().find(dogen::sml::tags::odb_pragma));
        BOOST_REQUIRE(i != m.meta_data().not_found());
        BOOST_REQUIRE(i->second.size() == 1);
        const auto j(i->second.begin());
        BOOST_CHECK(j->second.data() == odb_pragma_value);

        i = o.meta_data().find(type_key);
        BOOST_REQUIRE(i != m.meta_data().not_found());
        BOOST_REQUIRE(i->second.size() == 0);
        BOOST_CHECK(i->second.data() == type_value);
    }
}

BOOST_AUTO_TEST_CASE(no_documentation_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("no_documentation_model_hydrates_into_expected_model");

    const auto m(hydrate(no_documentation_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_CHECK(m.documentation().empty());
    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& pair(m.objects().begin());
    BOOST_CHECK(pair->second.documentation().empty());
}

BOOST_AUTO_TEST_CASE(no_name_model_throws) {
    SETUP_TEST_LOG_SOURCE("no_name_model_throws");
    contains_checker<hydration_error> c(missing_model_name);
    BOOST_CHECK_EXCEPTION(hydrate(no_name_model), hydration_error, c);
}

BOOST_AUTO_TEST_CASE(no_type_name_model_throws) {
    SETUP_TEST_LOG_SOURCE("no_type_name_model_throws");
    contains_checker<hydration_error> c(missing_type_name);
    BOOST_CHECK_EXCEPTION(hydrate(no_type_name_model), hydration_error, c);
}

BOOST_AUTO_TEST_CASE(no_origin_model_throws) {
    SETUP_TEST_LOG_SOURCE("no_origin_model_throws");
    contains_checker<hydration_error> c(missing_origin);
    BOOST_CHECK_EXCEPTION(hydrate(no_origin_model), hydration_error, c);
}

BOOST_AUTO_TEST_CASE(no_types_model_throws) {
    SETUP_TEST_LOG_SOURCE("no_types_model_throws");
    contains_checker<hydration_error> c(missing_types);
    BOOST_CHECK_EXCEPTION(hydrate(no_types_model), hydration_error, c);
}

BOOST_AUTO_TEST_CASE(empty_types_model_throws) {
    SETUP_TEST_LOG_SOURCE("empty_types_model_throws");
    contains_checker<hydration_error> c(missing_types);
    BOOST_CHECK_EXCEPTION(hydrate(empty_types_model), hydration_error, c);
}

BOOST_AUTO_TEST_CASE(module_path_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("module_path_model_hydrates_into_expected_model");

    const auto m(hydrate(module_path_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    {
        const auto mp(m.name().module_path());
        BOOST_REQUIRE(mp.size() == 3);
        auto i(mp.begin());
        BOOST_CHECK(*i == module_path_value_1);
        BOOST_CHECK((*(++i)) == module_path_value_2);
        BOOST_CHECK((*(++i)) == module_path_value_3);
        BOOST_CHECK(m.name().external_module_path().empty());
    }

    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& pair(*m.objects().begin());
    const auto& qn(pair.second.name());

    BOOST_CHECK(pair.first == qn);
    {
        const auto mp(qn.module_path());
        BOOST_REQUIRE(mp.size() == 1);
        auto i(mp.begin());
        BOOST_CHECK(*i == module_path_value_1);
        BOOST_CHECK(qn.external_module_path().empty());
    }
}

BOOST_AUTO_TEST_CASE(cpp_std_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("cpp_std_model_hydrates_into_expected_model");

    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / cpp_std_model_path);
    boost::filesystem::ifstream s(p);
    dogen::sml::json_hydrator h;
    const auto m(h.hydrate(s));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_CHECK(m.name().model_name() == cpp_std_model_name);
    BOOST_CHECK(m.origin_type() == dogen::sml::origin_types::system);

    const auto& objects(m.objects());
    BOOST_CHECK(!objects.empty());
    for (const auto& pair : objects) {
        const auto& o(pair.second);
        const auto qn(o.name());
        BOOST_CHECK(qn.model_name() == cpp_std_model_name);
        BOOST_CHECK(qn.external_module_path().empty());
        BOOST_CHECK(o.origin_type() == dogen::sml::origin_types::system);

        using dogen::sml::object_types;
        const auto ot(o.object_type());
        BOOST_CHECK(ot != object_types::invalid);
        if (ot == object_types::ordered_container)
            BOOST_CHECK(o.number_of_type_arguments() == 2);
        else if (ot == object_types::hash_container)
            BOOST_CHECK(o.number_of_type_arguments() == 2);
        else if (ot == object_types::sequence_container ||
            ot == object_types::smart_pointer)
            BOOST_CHECK(o.number_of_type_arguments() == 1);
        else
            BOOST_CHECK(o.number_of_type_arguments() == 0);
    }

    const auto primitives(m.primitives());
    BOOST_CHECK(!m.primitives().empty());
    for (const auto& pair : primitives) {
        const auto p(pair.second);
        const auto qn(p.name());
        BOOST_CHECK(qn.model_name() == cpp_std_model_name);
        BOOST_CHECK(qn.external_module_path().empty());
    }

    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.modules().empty());
    BOOST_CHECK(m.references().empty());
    BOOST_CHECK(m.leaves().empty());
    BOOST_CHECK(m.name().external_module_path().empty());
}

BOOST_AUTO_TEST_CASE(cpp_boost_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("cpp_boost_model_hydrates_into_expected_model");

    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / cpp_boost_model_path);
    boost::filesystem::ifstream s(p);
    dogen::sml::json_hydrator h;
    const auto m(h.hydrate(s));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_CHECK(m.name().model_name() == cpp_boost_model_name);
    BOOST_CHECK(m.origin_type() == dogen::sml::origin_types::system);

    const auto& objects(m.objects());
    BOOST_CHECK(!objects.empty());
    for (const auto& pair : objects) {
        const auto& o(pair.second);
        const auto qn(o.name());
        BOOST_CHECK(qn.model_name() == cpp_boost_model_name);
        BOOST_CHECK(qn.external_module_path().empty());

        using dogen::sml::object_types;
        const auto ot(o.object_type());
        BOOST_CHECK(ot != object_types::invalid);
        if (ot == object_types::ordered_container)
            BOOST_CHECK(o.number_of_type_arguments() == 2);
        if (ot == object_types::hash_container)
            BOOST_CHECK(o.number_of_type_arguments() == 2);
        else if (ot == object_types::sequence_container ||
            ot == object_types::smart_pointer)
            BOOST_CHECK(o.number_of_type_arguments() == 1);
        else
            BOOST_CHECK(o.number_of_type_arguments() == 0);

        if (!qn.module_path().empty()) {
            bool module_found(false);
            for (const auto& pair : m.modules()) {
                const auto mod(pair.second);
                auto pp(mod.name().module_path());
                pp.push_back(mod.name().simple_name());
                BOOST_LOG_SEV(lg, info) << "Converted path: " << pp;
                if (qn.module_path() == pp) {
                    module_found = true;
                    break;
                }
            }

            if (!module_found)
                BOOST_LOG_SEV(lg, error) << "Object has undefined module: "
                                         << qn;
            BOOST_CHECK(module_found);
        }
    }
    BOOST_CHECK(m.primitives().empty());
    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(!m.modules().empty());
    BOOST_CHECK(m.references().empty());
    BOOST_CHECK(m.leaves().empty());
    BOOST_CHECK(m.name().external_module_path().empty());
}

BOOST_AUTO_TEST_CASE(hardware_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("hardware_model_hydrates_into_expected_model");

    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / hardware_model_path);
    boost::filesystem::ifstream s(p);
    dogen::sml::json_hydrator h;
    const auto m(h.hydrate(s));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_CHECK(m.name().model_name() == hardware_model_name);
    BOOST_CHECK(m.origin_type() == dogen::sml::origin_types::system);

    BOOST_CHECK(m.objects().empty());
    const auto primitives(m.primitives());
    BOOST_CHECK(!primitives.empty());
    for (const auto& pair : primitives) {
        const auto p(pair.second);
        const auto qn(p.name());
        BOOST_CHECK(qn.model_name().empty());
        BOOST_CHECK(qn.external_module_path().empty());
    }

    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.modules().empty());
    BOOST_CHECK(m.references().empty());
    BOOST_CHECK(m.leaves().empty());
    BOOST_CHECK(m.name().external_module_path().empty());
}

BOOST_AUTO_TEST_SUITE_END()

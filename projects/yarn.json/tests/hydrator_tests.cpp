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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/fstream.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/test/mock_type_factory.hpp"
#include "dogen/annotations/test/mock_type_repository_factory.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/exomodel.hpp"
#include "dogen/yarn/io/meta_model/exomodel_io.hpp"
#include "dogen/yarn.json/types/hydration_error.hpp"
#include "dogen/yarn.json/types/hydrator.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
/*
namespace {

const std::string test_module("yarn.json");
const std::string test_suite("hydrator_tests");

const std::string model_name("a_model");
const std::string documentation("a_doc");
const std::string type_name("a_type");
const std::string model_key("model_key");
const std::string model_value("model_value");
const std::string some_key("some_key");
const std::string some_value("some_value");
const std::string type_key("type_key");
const std::string type_value("model_value");
const std::string internal_modules_key("modules");
const std::string internal_modules_value_1("module_1");
const std::string internal_modules_value_2("module_2");
const std::string internal_modules_value_3("module_3");

const std::string cpp_std_model_path("library/cpp.std.json");
const std::string cpp_std_model_name("std");
const std::string cpp_boost_model_name("boost");
const std::string cpp_boost_model_path("library/cpp.boost.json");
const std::string hardware_model_path("library/cpp.builtins.json");
const std::string hardware_model_name_front("cpp");
const std::string hardware_model_name_back("builtins");

const std::string missing_type_name("name is mandatory.");
const std::string missing_elements("elements");

const std::string trivial_model(R"({
    "root_module" : {
        "meta_name": {
          "simple": "module",
          "external_modules" : "dogen",
          "model_modules" : "yarn",
          "internal_modules" : "meta_model"
        },
        "documentation" : "a_doc",
        "annotation": {
            "yarn.model_modules": "a_model"
        }
    },
    "elements" : [
        {
            "name" : {
                "simple" : "a_type"
            },
            "meta_name": {
              "simple": "object",
              "external_modules" : "dogen",
              "model_modules" : "yarn",
              "internal_modules" : "meta_model"
            },
            "documentation" : "a_doc"
        }
     ]
  }
)");

const std::string no_documentation_model(R"({
    "root_module" : {
        "meta_name": {
          "simple": "module",
          "external_modules" : "dogen",
          "model_modules" : "yarn",
          "internal_modules" : "meta_model"
        },
        "annotation": {
            "yarn.model_modules": "a_model"
        }
    },
    "elements" : [
        {
            "name" : {
                "simple" : "a_type"
            },
            "meta_name": {
              "simple": "object",
              "external_modules" : "dogen",
              "model_modules" : "yarn",
              "internal_modules" : "meta_model"
            }
        }
     ]
  }
)");

const std::string no_name_model(R"({
    "root_module" : {
        "meta_name": {
          "simple": "module",
          "external_modules" : "dogen",
          "model_modules" : "yarn",
          "internal_modules" : "meta_model"
        },
        "annotation": {
            "yarn.model_modules": "a_model"
        }
    },
    "elements" : [
        {
            "name" : {
                "simple" : "a_type"
            },
            "meta_name": {
              "simple": "object",
              "external_modules" : "dogen",
              "model_modules" : "yarn",
              "internal_modules" : "meta_model"
            }
        }
     ]
  }
)");

const std::string no_type_name_model(R"({
    "root_module" : {
        "meta_name": {
          "simple": "module",
          "external_modules" : "dogen",
          "model_modules" : "yarn",
          "internal_modules" : "meta_model"
        },
        "annotation": {
            "yarn.model_modules": "a_model"
        }
    },
    "elements" : [
        {
            "meta_name": {
              "simple": "object",
              "external_modules" : "dogen",
              "model_modules" : "yarn",
              "internal_modules" : "meta_model"
            }
        }
     ]
  }
)");

const std::string no_elements_model(R"({
    "root_module" : {
        "meta_name": {
          "simple": "module",
          "external_modules" : "dogen",
          "model_modules" : "yarn",
          "internal_modules" : "meta_model"
        },
        "annotation": {
            "yarn.model_modules": "a_model"
        }
    }
  }
)");

const std::string empty_elements_model(R"({
    "root_module" : {
        "meta_name": {
          "simple": "module",
          "external_modules" : "dogen",
          "model_modules" : "yarn",
          "internal_modules" : "meta_model"
        },
        "annotation": {
            "yarn.model_modules": "a_model"
        }
    },
    "elements" : [ ]
  }
)");

const std::string internal_modules_model(R"({
    "root_module" : {
        "meta_name": {
          "simple": "module",
          "external_modules" : "dogen",
          "model_modules" : "yarn",
          "internal_modules" : "meta_model"
        },
        "annotation": {
            "yarn.model_modules": "a_model"
        }
    },
    "elements" : [
        {
            "name" : {
                "simple" : "a_type",
                "internal_modules" : "module_1::module_2::module_3"
            },
            "meta_name": {
              "simple": "object",
              "external_modules" : "dogen",
              "model_modules" : "yarn",
              "internal_modules" : "meta_model"
            }
        }
     ]
  }
)");

dogen::annotations::type_repository create_repository() {
    using namespace dogen::annotations;
    test::mock_type_factory f;

    std::list<type> fds;
    fds.push_back(f.make_type(model_key));
    fds.push_back(f.make_type(some_key));
    fds.push_back(f.make_type(type_key, value_types::boolean));

    test::mock_type_repository_factory rf;
    return rf.make(fds);
}

dogen::yarn::meta_model::exomodel hydrate(std::istream& s) {
    const auto rp(create_repository());

    dogen::yarn::json::hydrator h;
    return h.hydrate(s);
}

dogen::yarn::meta_model::exomodel
hydrate(const boost::filesystem::path& p) {
    boost::filesystem::ifstream s(p);
    return hydrate(s);
}

dogen::yarn::meta_model::exomodel
hydrate(const std::string& content) {
    std::istringstream s(content);
    return hydrate(s);
}

}

using dogen::utility::test::contains_checker;
using dogen::yarn::json::hydration_error;

BOOST_AUTO_TEST_SUITE(hydrator_tests)

BOOST_AUTO_TEST_CASE(trivial_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("trivial_model_hydrates_into_expected_model");

    BOOST_LOG_SEV(lg, debug) << "input: " << trivial_model;
    const auto m(hydrate(trivial_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_REQUIRE(m.modules().empty());
    {
        const auto& pair(m.root_module());
        BOOST_REQUIRE(pair.second);
        BOOST_CHECK(pair.second->documentation() == documentation);
        BOOST_CHECK(pair.second->annotation().entries().empty());
    }

    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& pair(*m.objects().begin());
        const auto& n(pair.second->name());

        BOOST_CHECK(n.simple() == type_name);
        const auto& nl(n.location());
        BOOST_CHECK(nl.internal_modules().empty());
        BOOST_CHECK(nl.external_modules().empty());
        BOOST_CHECK(pair.second->documentation() == documentation);
    }
}

BOOST_AUTO_TEST_CASE(no_documentation_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("no_documentation_model_hydrates_into_expected_model");

    const auto m(hydrate(no_documentation_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_REQUIRE(m.modules().empty());
    {
        const auto& pair(m.root_module());
        BOOST_REQUIRE(pair.second);
        BOOST_CHECK(pair.second->documentation().empty());
    }

    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& pair(m.objects().begin());
        BOOST_CHECK(pair->second->documentation().empty());
    }
}

BOOST_AUTO_TEST_CASE(no_type_name_model_throws) {
    SETUP_TEST_LOG_SOURCE("no_type_name_model_throws");
    contains_checker<hydration_error> c(missing_type_name);
    BOOST_CHECK_EXCEPTION(hydrate(no_type_name_model), hydration_error, c);
}

BOOST_AUTO_TEST_CASE(no_elements_model_results_in_empty_model) {
    SETUP_TEST_LOG_SOURCE("no_elements_model_throws");
    const auto m(hydrate(no_elements_model));

    BOOST_CHECK(m.objects().empty());
    BOOST_CHECK(m.builtins().empty());
    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.modules().empty());
    BOOST_REQUIRE(m.root_module().second);
}

BOOST_AUTO_TEST_CASE(empty_elements_model_throws) {
    SETUP_TEST_LOG_SOURCE("empty_elements_model_throws");

    const auto m(hydrate(empty_elements_model));

    BOOST_CHECK(m.objects().empty());
    BOOST_CHECK(m.builtins().empty());
    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.modules().empty());
}

BOOST_AUTO_TEST_CASE(internal_modules_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("internal_modules_model_hydrates_into_expected_model");
    const auto m(hydrate(internal_modules_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& pair(*m.objects().begin());
    const auto& n(pair.second->name());

    const auto mp(n.location().internal_modules());
    BOOST_REQUIRE(mp.size() == 3);

    auto i(mp.begin());
    BOOST_CHECK(*i == internal_modules_value_1);
    BOOST_CHECK((*(++i)) == internal_modules_value_2);
    BOOST_CHECK((*(++i)) == internal_modules_value_3);

    BOOST_CHECK(n.location().external_modules().empty());
}

BOOST_AUTO_TEST_CASE(cpp_std_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("cpp_std_model_hydrates_into_expected_model");

    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / cpp_std_model_path);
    const auto m(hydrate(p));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto& objects(m.objects());
    BOOST_CHECK(!objects.empty());
    for (const auto& pair : objects) {
        const auto& o(*pair.second);
        const auto n(o.name());

        BOOST_REQUIRE(!n.simple().empty());
        BOOST_CHECK(n.location().model_modules().empty());
        BOOST_CHECK(n.location().internal_modules().empty());
        BOOST_CHECK(n.location().external_modules().empty());
    }

    const auto builtins(m.builtins());
    BOOST_CHECK(!m.builtins().empty());
    for (const auto& pair : builtins) {
        const auto p(*pair.second);
        const auto n(p.name());

        BOOST_REQUIRE(!n.simple().empty());
        BOOST_CHECK(n.location().model_modules().empty());
        BOOST_CHECK(n.location().internal_modules().empty());
        BOOST_CHECK(n.location().external_modules().empty());
    }

    BOOST_CHECK(m.enumerations().empty());
    BOOST_REQUIRE(m.modules().empty());
}

BOOST_AUTO_TEST_CASE(cpp_boost_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("cpp_boost_model_hydrates_into_expected_model");

    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / cpp_boost_model_path);
    const auto m(hydrate(p));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto& objects(m.objects());
    BOOST_CHECK(!objects.empty());
    for (const auto& pair : objects) {
        const auto& o(*pair.second);
        const auto n(o.name());

        BOOST_REQUIRE(!n.simple().empty());
        BOOST_CHECK(n.location().model_modules().empty());
        BOOST_CHECK(n.location().external_modules().empty());
    }
    BOOST_CHECK(m.builtins().empty());
    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.modules().empty());
}

BOOST_AUTO_TEST_CASE(hardware_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("hardware_model_hydrates_into_expected_model");
    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / hardware_model_path);
    const auto m(hydrate(p));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_CHECK(m.objects().empty());
    const auto builtins(m.builtins());
    BOOST_CHECK(!builtins.empty());
    for (const auto& pair : builtins) {
        const auto& p(*pair.second);
        const auto n(p.name());
        BOOST_REQUIRE(!n.simple().empty());
        BOOST_CHECK(n.location().model_modules().empty());
        BOOST_CHECK(n.location().internal_modules().empty());
        BOOST_CHECK(n.location().external_modules().empty());
    }

    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.modules().empty());
}

BOOST_AUTO_TEST_SUITE_END()
*/

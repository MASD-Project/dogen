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
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/indexer_interface.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/om/types/cpp_domain_header_formatter.hpp"
#include "dogen/om/test_data/all_td.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string test_module("om");
const std::string test_suite("cpp_domain_header_formatter_spec");
const boost::filesystem::path empty_path;
const boost::filesystem::path non_empty_path("a/file.hpp");

const std::string enumeration_two_enumerators(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
enum class some_type_0 : unsigned int {
    some_type_0 = 0, ///< Some documentation
    some_type_1 = 1 ///< Some documentation
};

}
)");

const std::string value_object_no_properties(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_0 final {
};

}
)");

const std::string value_object_inheritance(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_0 final : public some_type_1 {
};

}
)");

class mock_indexer : public dogen::sml::indexer_interface {
public:
    mock_indexer() = default;
    mock_indexer(const mock_indexer&) = default;
    mock_indexer(mock_indexer&&) = default;
    mock_indexer& operator=(const mock_indexer&) = default;

public:
    /**
     * @pre is_indexed must be true.
     */
    std::list<dogen::sml::property>
    all_properties(const dogen::sml::abstract_object&) const override {
        return std::list<dogen::sml::property> {};
    }

    /**
     * @pre is_indexed must be true.
     */
    std::list<dogen::sml::property>
    local_properties(const dogen::sml::abstract_object&) const override {
        return std::list<dogen::sml::property> {};
    }

    /**
     * @pre is_indexed must be true.
     */
    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >
    inehrited_properties(const dogen::sml::abstract_object&) const override {
        return std::unordered_map<dogen::sml::qname,
                                  std::list<dogen::sml::property> > {};
    }
};

bool is_type_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::simple_name(0) == qn.simple_name();
}

}

using namespace dogen::om;
using namespace dogen::utility::test;
typedef dogen::sml::test::mock_model_factory::object_types object_types;
typedef dogen::sml::test::mock_model_factory::property_types property_types;
typedef dogen::sml::test::mock_model_factory factory;

BOOST_AUTO_TEST_SUITE(cpp_domain_header_formatter)

BOOST_AUTO_TEST_CASE(enumeration_with_two_enumerators_produces_expected_domain_header) {
    SETUP_TEST_LOG_SOURCE("enumeration_with_two_enumerators_produces_expected_domain_header");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto ot(object_types::enumeration);
    const auto m(factory::build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    std::ostringstream s;
    dogen::om::cpp_domain_header_formatter f;
    mock_indexer mi;
    const auto e(m.enumerations().begin()->second);
    f.format(s, e, dogen::om::licence(), dogen::om::modeline(),
        std::string()/*marker*/, mi);
    const auto r(s.str());
    BOOST_CHECK(r == enumeration_two_enumerators);
    BOOST_LOG_SEV(lg, debug) << "expected: " << enumeration_two_enumerators;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(value_object_with_no_properties_produces_expected_domain_header) {
    SETUP_TEST_LOG_SOURCE("value_object_with_no_properties_produces_expected_domain_header");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(factory::build_single_type_model(0));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    std::ostringstream s;
    dogen::om::cpp_domain_header_formatter f;
    mock_indexer mi;
    const auto& o(*m.objects().begin()->second);
    f.format(s, o, dogen::om::licence(), dogen::om::modeline(),
        std::string()/*marker*/, mi);
    const auto r(s.str());
    BOOST_CHECK(r == value_object_no_properties);
    BOOST_LOG_SEV(lg, debug) << "expected: " << value_object_no_properties;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(value_object_with_parent_produces_expected_domain_header) {
    SETUP_TEST_LOG_SOURCE("value_object_with_parent_produces_expected_domain_header");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_model_factory::object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 2);

    boost::shared_ptr<dogen::sml::abstract_object> o;
    for (const auto& pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            o = pair.second;
            BOOST_LOG_SEV(lg, debug) << "found child object: " << pair.first;
        }
    }

    std::ostringstream s;
    dogen::om::cpp_domain_header_formatter f;
    mock_indexer mi;
    f.format(s, *o, dogen::om::licence(), dogen::om::modeline(),
        std::string()/*marker*/, mi);
    const auto r(s.str());
    BOOST_CHECK(r == value_object_inheritance);
    BOOST_LOG_SEV(lg, debug) << "expected: " << value_object_inheritance;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}


BOOST_AUTO_TEST_SUITE_END()

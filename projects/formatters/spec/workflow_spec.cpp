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
#include <ostream>
#include <boost/make_shared.hpp>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/formatters/io/file_io.hpp"
#include "dogen/formatters/io/repository_io.hpp"
#include "dogen/formatters/types/file_formatter_interface.hpp"
#include "dogen/formatters/types/transformer_interface.hpp"
#include "dogen/formatters/types/entity.hpp"
#include "dogen/formatters/types/registrar.hpp"
#include "dogen/formatters/types/workflow.hpp"

namespace {

const std::string empty;
const std::string test_module("formatters");
const std::string test_suite("workflow_spec");

class entity : public dogen::formatters::entity { };

class test_file_formatter : public dogen::formatters::file_formatter_interface {
public:
    void to_stream(std::ostream& s) const {
        s << " { "
          << "\"__type__\": " << "\"test_file_formatter\"" << ", "
          << "\"__parent_0__\": ";
        dogen::formatters::file_formatter_interface::to_stream(s);
        s << " }";
    }

public:
    boost::optional<dogen::formatters::file>
    format(const dogen::formatters::entity& e) const {
        const auto pe(dynamic_cast<const entity * const>(&e));
        if (!pe)
            return boost::optional<dogen::formatters::file>();

        dogen::formatters::file f;
        return f;
    }
};

class test_transformer : public dogen::formatters::transformer_interface {
public:
    test_transformer() : how_many_(0), found_reference_data_(false) { }
    explicit test_transformer(const unsigned int how_many)
    : how_many_(how_many), found_reference_data_(false) { }

public:
    void to_stream(std::ostream& s) const {
        s << " { "
          << "\"__type__\": " << "\"test_transformer\"" << ", "
          << "\"__parent_0__\": ";
        dogen::formatters::transformer_interface::to_stream(s);
        s << " }";
    }

public:
    bool found_reference_data() const {
        return found_reference_data_;
    }

    dogen::formatters::transformer_interface::entities_type
    transform(const dogen::sml::model&,
        const dogen::formatters::annotation_factory& f) const {

        found_reference_data_ = !f.empty();

        dogen::formatters::transformer_interface::entities_type r;
        for (unsigned int i(0); i < how_many_; ++i)
            r.push_back(boost::make_shared<entity>());
        return r;
    }

private:
    const unsigned int how_many_;
    mutable bool found_reference_data_;
};

// test of static registration
dogen::formatters::registrar<test_transformer>
rt(boost::make_shared<test_transformer>());

dogen::formatters::registrar<test_file_formatter>
rff(boost::make_shared<test_file_formatter>());

void unregister_interfaces() {
    auto& repo(dogen::formatters::workflow::repository());
    repo.clear();
    BOOST_REQUIRE(repo.file_formatters().empty());
    BOOST_REQUIRE(repo.transformers().empty());
}

void reregister_interfaces(const unsigned int how_many = 0) {
    unregister_interfaces();

    dogen::formatters::registrar<test_transformer>
        rt(boost::make_shared<test_transformer>(how_many));

    dogen::formatters::registrar<test_file_formatter>
        rff(boost::make_shared<test_file_formatter>());

    auto& repo(dogen::formatters::workflow::repository());
    BOOST_REQUIRE(repo.file_formatters().size() == 1);
    BOOST_REQUIRE(repo.transformers().size() == 1);
}

}

using namespace dogen::formatters;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(workflow)

BOOST_AUTO_TEST_CASE(static_registration_of_interfaces_results_in_the_expected_repository_state) {
    SETUP_TEST_LOG_SOURCE("static_registration_of_interfaces_results_in_the_expected_repository_state");

    using namespace dogen::utility::filesystem;
    const std::list<boost::filesystem::path> d = { data_files_directory() };
    dogen::formatters::workflow w(d);
    BOOST_LOG_SEV(lg, debug) << "repository: " << w.repository();
    BOOST_CHECK(w.repository().file_formatters().size() == 1);
    BOOST_CHECK(w.repository().file_formatters().front().get() != nullptr);

    BOOST_CHECK(w.repository().transformers().size() == 1);
    BOOST_CHECK(w.repository().transformers().front().get() != nullptr);
}

BOOST_AUTO_TEST_CASE(executing_transformer_workflow_with_an_empty_repository_produces_no_files) {
    SETUP_TEST_LOG_SOURCE("executing_transformer_workflow_with_an_empty_repository_produces_no_files");

    unregister_interfaces();

    using namespace dogen::utility::filesystem;
    const std::list<boost::filesystem::path> d = { data_files_directory() };
    dogen::formatters::workflow w(d);

    BOOST_LOG_SEV(lg, debug) << "repository: " << w.repository();
    BOOST_REQUIRE(w.repository().empty());

    const dogen::sml::model m;
    const auto files(w.execute(m));
    BOOST_LOG_SEV(lg, debug) << "files size: " << files.size();
    BOOST_CHECK(files.empty());
}

BOOST_AUTO_TEST_CASE(executing_transformer_workflow_with_a_non_empty_repository_produces_expected_files) {
    SETUP_TEST_LOG_SOURCE("executing_transformer_workflow_with_a_non_empty_repository_produces_expected_files");

    const unsigned int files_to_create(5);
    reregister_interfaces(files_to_create);

    using namespace dogen::utility::filesystem;
    const std::list<boost::filesystem::path> d = { data_files_directory() };
    dogen::formatters::workflow w(d);

    BOOST_LOG_SEV(lg, debug) << "repository: " << w.repository();
    BOOST_REQUIRE(w.repository().file_formatters().size() == 1);
    BOOST_REQUIRE(w.repository().transformers().size() == 1);

    const auto p(dynamic_cast<const test_transformer* const>(
            w.repository().transformers().front().get()));

    BOOST_REQUIRE(p != nullptr);
    BOOST_CHECK(!p->found_reference_data());

    const dogen::sml::model m;
    const auto files(w.execute(m));
    BOOST_LOG_SEV(lg, debug) << "files: " << files;

    BOOST_CHECK(p->found_reference_data());
    BOOST_CHECK(files.size() == files_to_create);
}

BOOST_AUTO_TEST_SUITE_END()

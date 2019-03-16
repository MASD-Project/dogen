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
#include "masd.dogen.generation.cpp/types/formatters/tests/class_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/tests/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.extraction/types/sequence_formatter.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include <boost/throw_exception.hpp>

namespace masd::dogen::generation::cpp::formatters::tests {

std::string class_implementation_formatter::static_id() {
    return traits::class_implementation_archetype();
}

std::string class_implementation_formatter::id() const {
    return static_id();
}

annotations::archetype_location
class_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          class_implementation_formatter::static_id());
    return r;
}

const coding::meta_model::name& class_implementation_formatter::meta_name() const {
    using coding::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

std::string class_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types class_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const coding::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(class_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path class_implementation_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_tests_cpp_implementation(n, static_id());
}

std::list<std::string> class_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const coding::meta_model::element& e) const {

    using coding::meta_model::object;
    const auto& o(assistant::as<object>(e));
    auto builder(f.make());
    builder.add(o.name(), types::traits::class_header_archetype());
    builder.add(o.name(), test_data::traits::class_header_archetype());

    using ic = inclusion_constants;
    builder.add(ic::std::string());
    builder.add(ic::boost::test::unit_test());

    return builder.build();
}

extraction::meta_model::artefact class_implementation_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& o(a.as<coding::meta_model::object>(e));
    {
        auto sbf(a.make_scoped_boilerplate_formatter(o));
        const auto qn(a.get_qualified_name(o.name()));
a.stream() << "BOOST_AUTO_TEST_SUITE(" << o.name().identifiable() << "_tests)" << std::endl;
a.stream() << std::endl;
        /*
         * If we have no attributes at all, we cannot test this
         * type. Insert a fake test for now. The real solution will be
         * to filter based on element state.
         */
        if (o.all_attributes().empty()) {
a.stream() << "BOOST_AUTO_TEST_CASE(fake_test) {" << std::endl;
a.stream() << "    BOOST_CHECK(true);" << std::endl;
a.stream() << "}" << std::endl;
        } else {
a.stream() << "BOOST_AUTO_TEST_CASE(identical_objects_are_equal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const auto a(g());" << std::endl;
a.stream() << "    const auto b(a);" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "    BOOST_CHECK(b == a);" << std::endl;
a.stream() << "    BOOST_CHECK(!(a != b));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(an_object_is_equal_to_itself) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const auto a(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_CHECK(a == a);" << std::endl;
a.stream() << "    BOOST_CHECK(!(a != a));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(distinct_objects_are_unequal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const auto a(g());" << std::endl;
a.stream() << "    const auto b(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_CHECK(!(a == b));" << std::endl;
a.stream() << "    BOOST_CHECK(a != b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(assigning_an_object_to_itself_results_in_the_same_object) {" << std::endl;
a.stream() << "#if defined __clang__ && !defined __apple_build_version__  && __clang_major__ >= 7" << std::endl;
a.stream() << "#pragma clang diagnostic push" << std::endl;
a.stream() << "#pragma clang diagnostic ignored \"-Wself-assign-overloaded\"" << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    auto a(g());" << std::endl;
a.stream() << "    const auto b(a);" << std::endl;
a.stream() << "    const auto c(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    a = a;" << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "    BOOST_CHECK(a != c);" << std::endl;
a.stream() << "#ifdef __clang__" << std::endl;
a.stream() << "#pragma clang diagnostic pop" << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(moved_objects_are_equal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    auto a(g());" << std::endl;
a.stream() << "    const auto b = " << qn << "();" << std::endl;
a.stream() << "    const auto c(a);" << std::endl;
a.stream() << "    BOOST_CHECK(a != b);" << std::endl;
a.stream() << "    BOOST_CHECK(a == c);" << std::endl;
a.stream() << std::endl;
a.stream() << "    const auto d = std::move(a);" << std::endl;
a.stream() << "    BOOST_CHECK(d == c);" << std::endl;
a.stream() << "    BOOST_CHECK(d != b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(assigned_objects_are_equal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const auto a(g());" << std::endl;
a.stream() << "    " << qn << " b;" << std::endl;
a.stream() << "    BOOST_CHECK(a != b);" << std::endl;
a.stream() << std::endl;
a.stream() << "    b = a;" << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(copy_constructed_objects_are_equal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const auto a(g());" << std::endl;
a.stream() << "    auto b(a);" << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << std::endl;
a.stream() << "    b = " << qn << "();" << std::endl;
a.stream() << "    BOOST_CHECK(a != b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_SUITE_END()" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
}

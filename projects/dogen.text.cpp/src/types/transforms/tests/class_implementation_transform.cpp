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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/helpers/name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.text.cpp/types/transforms/tests/traits.hpp"
#include "dogen.text.cpp/types/transforms/tests/class_implementation_transform.hpp"

namespace dogen::text::cpp::transforms::tests {
const physical::entities::archetype& class_implementation_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::class_implementation_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_object_name().qualified().dot());
        return r;
    }());
    return r;
}

const physical::entities::archetype& class_implementation_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types class_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(logger_factory(archetype().meta_name().qualified()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path class_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_tests_cpp_implementation(n, archetype().meta_name().qualified());
}

std::list<std::string> class_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::object;
    const auto& o(assistant::as<object>(e));
    auto builder(f.make());
    builder.add(o.name(), types::traits::class_header_archetype_qn());
    builder.add(o.name(), test_data::traits::class_header_archetype_qn());

    using ic = inclusion_constants;
    builder.add(ic::std::string());
    builder.add(ic::boost::test::unit_test());

    if (o.is_parent())
        builder.add(ic::boost::shared_ptr());

    const auto io_arch(io::traits::class_header_archetype_qn());
    const bool io_enabled(builder.is_enabled(o.name(), io_arch));
    if (io_enabled) {
        builder.add(o.name(), io_arch);
        builder.add(ic::std::sstream());
        builder.add(ic::boost::property_tree::ptree());
        builder.add(ic::boost::property_tree::json_parser());
    }

    using ser = transforms::serialization::traits;
    const auto ser_arch(ser::class_header_archetype_qn());
    const bool ser_enabled(builder.is_enabled(o.name(), ser_arch));
    if (ser_enabled) {
        builder.add(o.name(), ser_arch);

        if (o.type_registrar())
            builder.add(o.type_registrar(), ser::type_registrar_header_archetype_qn());

        builder.add(ic::boost::archive::text_iarchive());
        builder.add(ic::boost::archive::text_oarchive());
        builder.add(ic::boost::archive::binary_iarchive());
        builder.add(ic::boost::archive::binary_oarchive());
        builder.add(ic::boost::archive::polymorphic_iarchive());
        builder.add(ic::boost::archive::polymorphic_oarchive());
        builder.add(ic::boost::serialization::nvp());
        builder.add(ic::boost::archive::xml_iarchive());
        builder.add(ic::boost::archive::xml_oarchive());

        if (o.is_parent())
            builder.add(ic::boost::serialization::shared_ptr());
    }

    using hash = transforms::hash::traits;
    const auto hash_arch(hash::class_header_archetype_qn());
    const bool hash_enabled(builder.is_enabled(o.name(), hash_arch));
    if (hash_enabled)
        builder.add(o.name(), hash_arch);

    return builder.build();
}

void class_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::structural::object>(e));
    {
        auto sbf(ast.make_scoped_boilerplate_formatter(o));
        const auto qn(ast.get_qualified_name(o.name()));
        auto list(e.name().location().internal_modules());
        list.push_back(o.name().simple());
        const std::string test_suite_name(boost::join(list, "_"));

        std::string type_name("auto");
        if (ast.is_cpp_standard_98())
            type_name = qn;

ast.stream() << "BOOST_AUTO_TEST_SUITE(" << test_suite_name << "_tests)" << std::endl;
ast.stream() << std::endl;
        /*
         * If we have no attributes at all, we cannot test this
         * type. Similarly, if test data is not enabled, none of the
         * tests can be generated. In either case, we need to insert a
         * fake test for now. The real solution will be to filter
         * based on element state.
         */
        if (o.all_attributes().empty() || !ast.is_test_data_enabled()) {
            /*
             * No tests.
             */
ast.stream() << "BOOST_AUTO_TEST_CASE(fake_test) {" << std::endl;
ast.stream() << "    BOOST_CHECK(true);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } else {
            /*
             * Types tests. These cannot be performed to parents as
             * they are abstract.
             */
            if (!o.is_parent()) {
ast.stream() << "BOOST_AUTO_TEST_CASE(identical_objects_are_equal) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    const " << type_name << " b(a);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    BOOST_CHECK(a == b);" << std::endl;
ast.stream() << "    BOOST_CHECK(b == a);" << std::endl;
ast.stream() << "    BOOST_CHECK(!(a != b));" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(an_object_is_equal_to_itself) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    BOOST_CHECK(a == a);" << std::endl;
ast.stream() << "    BOOST_CHECK(!(a != a));" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(distinct_objects_are_unequal) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    const " << type_name << " b(g());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    BOOST_CHECK(!(a == b));" << std::endl;
ast.stream() << "    BOOST_CHECK(a != b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
                if (!o.is_immutable()) {
ast.stream() << "BOOST_AUTO_TEST_CASE(assigning_an_object_to_itself_results_in_the_same_object) {" << std::endl;
ast.stream() << "#if defined(__clang__) && !defined(__apple_build_version__)  && (__clang_major__ >= 7)" << std::endl;
ast.stream() << "#pragma clang diagnostic push" << std::endl;
ast.stream() << "#pragma clang diagnostic ignored \"-Wself-assign-overloaded\"" << std::endl;
ast.stream() << "#endif" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    " << type_name << " a(g());" << std::endl;
ast.stream() << "    const " << type_name << " b(a);" << std::endl;
ast.stream() << "    const " << type_name << " c(g());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    a = a;" << std::endl;
ast.stream() << "    BOOST_CHECK(a == b);" << std::endl;
ast.stream() << "    BOOST_CHECK(a != c);" << std::endl;
ast.stream() << "#if defined(__clang__) && !defined(__apple_build_version__)  && (__clang_major__ >= 7)" << std::endl;
ast.stream() << "#pragma clang diagnostic pop" << std::endl;
ast.stream() << "#endif" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
                }

                // FIXME: should be 11 or greater.
                if (!ast.is_cpp_standard_98()) {
ast.stream() << "BOOST_AUTO_TEST_CASE(moved_objects_are_equal) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    g();" << std::endl;
ast.stream() << "    " << type_name << " a(g());" << std::endl;
ast.stream() << "    const " << type_name << " b = " << qn << "();" << std::endl;
ast.stream() << "    const " << type_name << " c(a);" << std::endl;
ast.stream() << "    BOOST_CHECK(a != b);" << std::endl;
ast.stream() << "    BOOST_CHECK(a == c);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    const " << type_name << " d = std::move(a);" << std::endl;
ast.stream() << "    BOOST_CHECK(d == c);" << std::endl;
ast.stream() << "    BOOST_CHECK(d != b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
                }

                if (!o.is_immutable()) {
ast.stream() << "BOOST_AUTO_TEST_CASE(assigned_objects_are_equal) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    g();" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    " << qn << " b;" << std::endl;
ast.stream() << "    BOOST_CHECK(a != b);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    b = a;" << std::endl;
ast.stream() << "    BOOST_CHECK(a == b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(copy_constructed_objects_are_equal) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    g();" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    " << type_name << " b(a);" << std::endl;
ast.stream() << "    BOOST_CHECK(a == b);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    b = " << qn << "();" << std::endl;
ast.stream() << "    BOOST_CHECK(a != b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(swapping_objects_results_in_the_expected_state) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    const " << type_name << " b(g());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    " << type_name << " c(a);" << std::endl;
ast.stream() << "    " << type_name << " d(b);" << std::endl;
ast.stream() << "    BOOST_CHECK(c == a);" << std::endl;
ast.stream() << "    BOOST_CHECK(d == b);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    std::swap(c, d);" << std::endl;
ast.stream() << "    BOOST_CHECK(c == b);" << std::endl;
ast.stream() << "    BOOST_CHECK(d == a);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
                }
            }

            if (ast.is_io_enabled()) {
                /*
                 * IO tests.
                 */
ast.stream() << "BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {" << std::endl;
                if (o.is_parent()) {
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const boost::shared_ptr<" << qn << "> a(g.create_ptr(1));" << std::endl;
ast.stream() << "    std::stringstream s;" << std::endl;
ast.stream() << "    s << *a;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    boost::property_tree::ptree pt;" << std::endl;
ast.stream() << "    BOOST_REQUIRE_NO_THROW(read_json(s, pt));" << std::endl;
                } else {
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    std::stringstream s;" << std::endl;
ast.stream() << "    s << a;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    boost::property_tree::ptree pt;" << std::endl;
ast.stream() << "    BOOST_REQUIRE_NO_THROW(read_json(s, pt));" << std::endl;
                }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            }

            if (ast.is_serialization_enabled()) {
                /*
                 * Serialization tests.
                 */
                 const auto registrar_qn(o.type_registrar() ?
                     ast.get_qualified_name(*o.type_registrar()) : std::string());

                if (o.is_parent()) {
ast.stream() << "BOOST_AUTO_TEST_CASE(xml_roundtrip_produces_the_same_entity) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const boost::shared_ptr<" << qn << "> a(g.create_ptr(1));" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    using namespace boost::archive;" << std::endl;
ast.stream() << "    std::ostringstream os;" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        xml_oarchive oa(os);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<xml_oarchive>(oa);" << std::endl;
                    }
ast.stream() << std::endl;
ast.stream() << "        oa << BOOST_SERIALIZATION_NVP(a);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    boost::shared_ptr<" << qn << "> b;" << std::endl;
ast.stream() << "    std::istringstream is(os.str());" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        xml_iarchive ia(is);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<xml_iarchive>(ia);" << std::endl;
                    }
ast.stream() << "        ia >> BOOST_SERIALIZATION_NVP(b);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    BOOST_REQUIRE(a);" << std::endl;
ast.stream() << "    BOOST_REQUIRE(b);" << std::endl;
ast.stream() << "    BOOST_CHECK(*a == *b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(text_roundtrip_produces_the_same_entity) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const boost::shared_ptr<" << qn << "> a(g.create_ptr(1));" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    using namespace boost::archive;" << std::endl;
ast.stream() << "    std::ostringstream os;" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        text_oarchive oa(os);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<text_oarchive>(oa);" << std::endl;
                    }
ast.stream() << "        oa << a;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    boost::shared_ptr<" << qn << "> b;" << std::endl;
ast.stream() << "    std::istringstream is(os.str());" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        text_iarchive ia(is);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<text_iarchive>(ia);" << std::endl;
                    }
ast.stream() << "        ia >> b;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    BOOST_REQUIRE(a);" << std::endl;
ast.stream() << "    BOOST_REQUIRE(b);" << std::endl;
ast.stream() << "    BOOST_CHECK(*a == *b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(binary_roundtrip_produces_the_same_entity) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const boost::shared_ptr<" << qn << "> a(g.create_ptr(1));" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    using namespace boost::archive;" << std::endl;
ast.stream() << "    std::ostringstream os;" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        binary_oarchive oa(os);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<binary_oarchive>(oa);" << std::endl;
                    }
ast.stream() << "        oa << a;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    boost::shared_ptr<" << qn << "> b;" << std::endl;
ast.stream() << "    std::istringstream is(os.str());" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        binary_iarchive ia(is);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<binary_iarchive>(ia);" << std::endl;
                    }
ast.stream() << "        ia >> b;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    BOOST_REQUIRE(a);" << std::endl;
ast.stream() << "    BOOST_REQUIRE(b);" << std::endl;
ast.stream() << "    BOOST_CHECK(*a == *b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
                } else {

ast.stream() << "BOOST_AUTO_TEST_CASE(xml_roundtrip_produces_the_same_entity) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    using namespace boost::archive;" << std::endl;
ast.stream() << "    std::ostringstream os;" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        xml_oarchive oa(os);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<xml_oarchive>(oa);" << std::endl;
                    }
ast.stream() << "        oa << BOOST_SERIALIZATION_NVP(a);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
ast.stream() << "    std::istringstream is(os.str());" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        xml_iarchive ia(is);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<xml_iarchive>(ia);" << std::endl;
                    }
ast.stream() << "        ia >> BOOST_SERIALIZATION_NVP(b);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    BOOST_CHECK(a == b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(text_roundtrip_produces_the_same_entity) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    using namespace boost::archive;" << std::endl;
ast.stream() << "    std::ostringstream os;" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        text_oarchive oa(os);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<text_oarchive>(oa);" << std::endl;
                    }
ast.stream() << "        oa << a;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
ast.stream() << "    std::istringstream is(os.str());" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        text_iarchive ia(is);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<text_iarchive>(ia);" << std::endl;
                    }
ast.stream() << "        ia >> b;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    BOOST_CHECK(a == b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(binary_roundtrip_produces_the_same_entity) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    using namespace boost::archive;" << std::endl;
ast.stream() << "    std::ostringstream os;" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        binary_oarchive oa(os);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<binary_oarchive>(oa);" << std::endl;
                    }
ast.stream() << "        oa << a;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
ast.stream() << "    std::istringstream is(os.str());" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        binary_iarchive ia(is);" << std::endl;
                    if (o.type_registrar()) {
ast.stream() << "        " << registrar_qn << "::register_types<binary_iarchive>(ia);" << std::endl;
                    }
ast.stream() << "        ia >> b;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    BOOST_CHECK(a == b);" << std::endl;
ast.stream() << "}" << std::endl;
                }
            }

            if (ast.is_hash_enabled() && !o.is_parent()) {
                /*
                 * hash tests.
                 */
ast.stream() << "BOOST_AUTO_TEST_CASE(equal_objects_generate_the_same_hash) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    g();" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    const " << type_name << " b(a);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    std::hash<" << qn << "> hasher;" << std::endl;
ast.stream() << "    BOOST_CHECK(hasher(a) == hasher(b));" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(different_objects_generate_different_hashes) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    g();" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    const " << type_name << " b(g());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    std::hash<" << qn << "> hasher;" << std::endl;
ast.stream() << "    BOOST_CHECK(hasher(a) != hasher(b));" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            }
        }
ast.stream() << "BOOST_AUTO_TEST_SUITE_END()" << std::endl;
    } // sbf
    ast.update_artefact();
}
}

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
#include <boost/predef.h>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/lexical_cast/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.text.cpp/types/transforms/tests/traits.hpp"
#include "dogen.text.cpp/types/transforms/tests/enum_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/tests/enum_implementation_factory.hpp"

namespace dogen::text::cpp::transforms::tests {
namespace {

const std::string transform_id("text.cpp.transforms.tests.enum_implementation_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& enum_implementation_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::enum_implementation_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_enumeration_name().qualified().dot());
        r.referencing_status(physical::entities::referencing_status::not_referable);
        return r;
    }());
    return r;
}

const physical::entities::archetype& enum_implementation_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types enum_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path enum_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(logger_factory(archetype().meta_name().qualified()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path enum_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_tests_cpp_implementation(n, archetype().meta_name().qualified());
}

std::list<std::string> enum_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    auto builder(f.make());
    builder.add(e.name(), types::traits::enum_header_archetype_qn());
    builder.add(e.name(), test_data::traits::enum_header_archetype_qn());

    using ic = inclusion_constants;
    builder.add(ic::std::string());
    builder.add(ic::boost::test::unit_test());
    builder.add(ic::boost::predef());

    const auto io_arch(io::traits::enum_header_archetype_qn());
    const bool io_enabled(builder.is_enabled(e.name(), io_arch));
    if (io_enabled) {
        builder.add(e.name(), io_arch);
        builder.add(ic::std::sstream());
        builder.add(ic::boost::property_tree::ptree());
        builder.add(ic::boost::property_tree::json_parser());
    }

    const auto lc_arch(lexical_cast::traits::enum_header_archetype_qn());
    const bool lc_enabled(builder.is_enabled(e.name(), lc_arch));
    if (lc_enabled) {
        builder.add(e.name(), lc_arch);
        builder.add(ic::boost::lexical_cast());
    }

    using ser = transforms::serialization::traits;
    const auto ser_arch(ser::enum_header_archetype_qn());
    const bool ser_enabled(builder.is_enabled(e.name(), ser_arch));
    if (ser_enabled) {
        builder.add(e.name(), ser_arch);

        builder.add(ic::boost::archive::text_iarchive());
        builder.add(ic::boost::archive::text_oarchive());
        builder.add(ic::boost::archive::binary_iarchive());
        builder.add(ic::boost::archive::binary_oarchive());
        builder.add(ic::boost::archive::polymorphic_iarchive());
        builder.add(ic::boost::archive::polymorphic_oarchive());
        builder.add(ic::boost::serialization::nvp());
        builder.add(ic::boost::archive::xml_iarchive());
        builder.add(ic::boost::archive::xml_oarchive());
    }

    using hash = transforms::hash::traits;
    const auto hash_arch(hash::enum_header_archetype_qn());
    const bool hash_enabled(builder.is_enabled(e.name(), hash_arch));
    if (hash_enabled)
        builder.add(e.name(), hash_arch);

    return builder.build();
}

void enum_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "enum implementation transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& enm(ast.as<logical::entities::structural::enumeration>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        const auto qn(ast.get_qualified_name(e.name()));
        const auto sn(e.name().simple());
        std::string type_name("auto");
        if (ast.is_cpp_standard_98())
            type_name = qn;
ast.stream() << "BOOST_AUTO_TEST_SUITE(" << e.name().simple() << "_tests)" << std::endl;
ast.stream() << std::endl;
        /*
         * If test data is not enabled, none of the tests can be
         * generated. We need to insert a fake test for now. The real
         * solution will be to filter based on element state.
         */
        if (!ast.is_test_data_enabled()) {
            /*
             * No tests.
             */
ast.stream() << "BOOST_AUTO_TEST_CASE(fake_test) {" << std::endl;
ast.stream() << "    BOOST_CHECK(true);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } else {
            if (ast.is_io_enabled()) {
                /*
                 * IO tests.
                 */
ast.stream() << "BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    std::stringstream s;" << std::endl;
ast.stream() << "    s << a;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    boost::property_tree::ptree pt;" << std::endl;
ast.stream() << "    BOOST_REQUIRE_NO_THROW(read_json(s, pt));" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            }

            if (ast.is_lexical_cast_enabled()) {
                /*
                 * Lexical cast tests.
                 */
ast.stream() << "BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {" << std::endl;
ast.stream() << "    using " << qn << ";" << std::endl;
ast.stream() << "    " << sn << " r;" << std::endl;
        for (const auto& enu : enm.enumerators()) {
            const auto enu_sn(enu.name().simple());
            std::string enu_qn;
            if (ast.is_cpp_standard_98())
                enu_qn = ast.get_qualified_namespace(enm.name()) + "::" + enu_sn;
            else
                enu_qn = sn + "::" + enu_sn;
ast.stream() << std::endl;
ast.stream() << "    r = boost::lexical_cast<" << sn << ">(std::string(\"" << enu_sn << "\"));" << std::endl;
ast.stream() << "    BOOST_CHECK(r == " << enu_qn << ");" << std::endl;
ast.stream() << "    r = boost::lexical_cast<" << sn << ">(std::string(\"" << sn + "::" + enu_sn << "\"));" << std::endl;
ast.stream() << "    BOOST_CHECK(r == " << enu_qn << ");" << std::endl;
        }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {" << std::endl;
ast.stream() << "    using " << qn << ";" << std::endl;
ast.stream() << "    BOOST_CHECK_THROW(boost::lexical_cast<" << sn << ">(std::string(\"DOGEN_THIS_IS_INVALID_DOGEN\"))," << std::endl;
ast.stream() << "        boost::bad_lexical_cast);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {" << std::endl;
ast.stream() << "    using " << qn << ";" << std::endl;
ast.stream() << "    std::string r;" << std::endl;
        for (const auto& enu : enm.enumerators()) {
            const auto enu_sn(enu.name().simple());
            std::string enu_qn;
            if (ast.is_cpp_standard_98())
                enu_qn = ast.get_qualified_namespace(enm.name()) + "::" + enu_sn;
            else
                enu_qn = sn + "::" + enu_sn;

ast.stream() << std::endl;
ast.stream() << "    r = boost::lexical_cast<std::string>(" << enu_qn << ");" << std::endl;
ast.stream() << "    BOOST_CHECK(r == \"" << sn + "::" + enu_sn << "\");" << std::endl;
        }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {" << std::endl;
ast.stream() << "#if BOOST_COMP_GNUC" << std::endl;
ast.stream() << "#pragma GCC diagnostic push" << std::endl;
ast.stream() << "#pragma GCC diagnostic ignored \"-Wconversion\"" << std::endl;
ast.stream() << "#endif" << std::endl;
ast.stream() << "    using " << qn << ";" << std::endl;
ast.stream() << "    const " << sn << " r(static_cast<" << sn << ">(" << enm.enumerators().size() + 10 << "));" << std::endl;
ast.stream() << "#if BOOST_COMP_GNUC" << std::endl;
ast.stream() << "#pragma GCC diagnostic pop" << std::endl;
ast.stream() << "#endif" << std::endl;
ast.stream() << "    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r)," << std::endl;
ast.stream() << "        boost::bad_lexical_cast);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            }

            if (ast.is_serialization_enabled()) {
                /*
                 * Serialization tests.
                 */
ast.stream() << "BOOST_AUTO_TEST_CASE(xml_roundtrip_produces_the_same_entity) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    using namespace boost::archive;" << std::endl;
ast.stream() << "    std::ostringstream os;" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        xml_oarchive oa(os);" << std::endl;
ast.stream() << "        oa << BOOST_SERIALIZATION_NVP(a);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
ast.stream() << "    std::istringstream is(os.str());" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        xml_iarchive ia(is);" << std::endl;
ast.stream() << "        ia >> BOOST_SERIALIZATION_NVP(b);" << std::endl;
ast.stream() << "    }" << std::endl;
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
ast.stream() << "        xml_oarchive oa(os);" << std::endl;
ast.stream() << "        oa << BOOST_SERIALIZATION_NVP(a);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
ast.stream() << "    std::istringstream is(os.str());" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        xml_iarchive ia(is);" << std::endl;
ast.stream() << "        ia >> BOOST_SERIALIZATION_NVP(b);" << std::endl;
ast.stream() << "    }" << std::endl;
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
ast.stream() << "        text_oarchive oa(os);" << std::endl;
ast.stream() << "        oa << a;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
ast.stream() << "    std::istringstream is(os.str());" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        text_iarchive ia(is);" << std::endl;
ast.stream() << "        ia >> b;" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << "    BOOST_CHECK(a == b);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            }

             if (ast.is_hash_enabled()) {
                 /*
                  * hash tests.
                  */
ast.stream() << "BOOST_AUTO_TEST_CASE(equal_enums_generate_the_same_hash) {" << std::endl;
ast.stream() << "    " << qn << "_generator g;" << std::endl;
ast.stream() << "    g();" << std::endl;
ast.stream() << "    const " << type_name << " a(g());" << std::endl;
ast.stream() << "    const " << type_name << " b(a);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    std::hash<" << qn << "> hasher;" << std::endl;
ast.stream() << "    BOOST_CHECK(hasher(a) == hasher(b));" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_AUTO_TEST_CASE(different_enums_generate_different_hashes) {" << std::endl;
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
    stp.end_transform(a);
}

}

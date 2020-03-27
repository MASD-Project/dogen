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
#include <boost/predef.h>
#include <boost/throw_exception.hpp>
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/io/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/lexical_cast/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/tests/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/tests/enum_implementation_transform.hpp"

namespace dogen::m2t::cpp::transforms::tests {

std::string enum_implementation_transform::static_id() {
    return traits::enum_implementation_archetype_qn();
}

std::string enum_implementation_transform::id() const {
    return static_id();
}

physical::entities::name
enum_implementation_transform::physical_name() const {
    using physical::helpers::name_factory;
    static auto r(name_factory::make(cpp::traits::backend_qn(),
        cpp::traits::tests_part(), traits::facet_qn(),
        enum_implementation_transform::static_id()));
    return r;
}

const logical::entities::name& enum_implementation_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

inclusion_support_types enum_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path enum_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(enum_implementation_transform::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path enum_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_tests_cpp_implementation(n, static_id());
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

physical::entities::artefact enum_implementation_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name(), false/*requires_header_guard*/);
    const auto& enm(a.as<logical::entities::structural::enumeration>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        const auto qn(a.get_qualified_name(e.name()));
        const auto sn(e.name().simple());
        std::string type_name("auto");
        if (a.is_cpp_standard_98())
            type_name = qn;
a.stream() << "BOOST_AUTO_TEST_SUITE(" << e.name().simple() << "_tests)" << std::endl;
a.stream() << std::endl;
        /*
         * If test data is not enabled, none of the tests can be
         * generated. We need to insert a fake test for now. The real
         * solution will be to filter based on element state.
         */
        if (!a.is_test_data_enabled()) {
            /*
             * No tests.
             */
a.stream() << "BOOST_AUTO_TEST_CASE(fake_test) {" << std::endl;
a.stream() << "    BOOST_CHECK(true);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } else {
            if (a.is_io_enabled()) {
                /*
                 * IO tests.
                 */
a.stream() << "BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    std::stringstream s;" << std::endl;
a.stream() << "    s << a;" << std::endl;
a.stream() << std::endl;
a.stream() << "    boost::property_tree::ptree pt;" << std::endl;
a.stream() << "    BOOST_REQUIRE_NO_THROW(read_json(s, pt));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }

            if (a.is_lexical_cast_enabled()) {
                /*
                 * Lexical cast tests.
                 */
a.stream() << "BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {" << std::endl;
a.stream() << "    using " << qn << ";" << std::endl;
a.stream() << "    " << sn << " r;" << std::endl;
        for (const auto& enu : enm.enumerators()) {
            const auto enu_sn(enu.name().simple());
            std::string enu_qn;
            if (a.is_cpp_standard_98())
                enu_qn = a.get_qualified_namespace(enm.name()) + "::" + enu_sn;
            else
                enu_qn = sn + "::" + enu_sn;
a.stream() << std::endl;
a.stream() << "    r = boost::lexical_cast<" << sn << ">(std::string(\"" << enu_sn << "\"));" << std::endl;
a.stream() << "    BOOST_CHECK(r == " << enu_qn << ");" << std::endl;
a.stream() << "    r = boost::lexical_cast<" << sn << ">(std::string(\"" << sn + "::" + enu_sn << "\"));" << std::endl;
a.stream() << "    BOOST_CHECK(r == " << enu_qn << ");" << std::endl;
        }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {" << std::endl;
a.stream() << "    using " << qn << ";" << std::endl;
a.stream() << "    BOOST_CHECK_THROW(boost::lexical_cast<" << sn << ">(std::string(\"DOGEN_THIS_IS_INVALID_DOGEN\"))," << std::endl;
a.stream() << "        boost::bad_lexical_cast);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {" << std::endl;
a.stream() << "    using " << qn << ";" << std::endl;
a.stream() << "    std::string r;" << std::endl;
        for (const auto& enu : enm.enumerators()) {
            const auto enu_sn(enu.name().simple());
            std::string enu_qn;
            if (a.is_cpp_standard_98())
                enu_qn = a.get_qualified_namespace(enm.name()) + "::" + enu_sn;
            else
                enu_qn = sn + "::" + enu_sn;

a.stream() << std::endl;
a.stream() << "    r = boost::lexical_cast<std::string>(" << enu_qn << ");" << std::endl;
a.stream() << "    BOOST_CHECK(r == \"" << sn + "::" + enu_sn << "\");" << std::endl;
        }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {" << std::endl;
a.stream() << "#if BOOST_COMP_GNUC" << std::endl;
a.stream() << "#pragma GCC diagnostic push" << std::endl;
a.stream() << "#pragma GCC diagnostic ignored \"-Wconversion\"" << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << "    using " << qn << ";" << std::endl;
a.stream() << "    const " << sn << " r(static_cast<" << sn << ">(" << enm.enumerators().size() + 10 << "));" << std::endl;
a.stream() << "#if BOOST_COMP_GNUC" << std::endl;
a.stream() << "#pragma GCC diagnostic pop" << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << "    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r)," << std::endl;
a.stream() << "        boost::bad_lexical_cast);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }

            if (a.is_serialization_enabled()) {
                /*
                 * Serialization tests.
                 */
a.stream() << "BOOST_AUTO_TEST_CASE(xml_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    using namespace boost::archive;" << std::endl;
a.stream() << "    std::ostringstream os;" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        xml_oarchive oa(os);" << std::endl;
a.stream() << "        oa << BOOST_SERIALIZATION_NVP(a);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
a.stream() << "    std::istringstream is(os.str());" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        xml_iarchive ia(is);" << std::endl;
a.stream() << "        ia >> BOOST_SERIALIZATION_NVP(b);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(text_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    using namespace boost::archive;" << std::endl;
a.stream() << "    std::ostringstream os;" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        xml_oarchive oa(os);" << std::endl;
a.stream() << "        oa << BOOST_SERIALIZATION_NVP(a);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
a.stream() << "    std::istringstream is(os.str());" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        xml_iarchive ia(is);" << std::endl;
a.stream() << "        ia >> BOOST_SERIALIZATION_NVP(b);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(binary_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    using namespace boost::archive;" << std::endl;
a.stream() << "    std::ostringstream os;" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        text_oarchive oa(os);" << std::endl;
a.stream() << "        oa << a;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
a.stream() << "    std::istringstream is(os.str());" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        text_iarchive ia(is);" << std::endl;
a.stream() << "        ia >> b;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }

             if (a.is_hash_enabled()) {
                 /*
                  * hash tests.
                  */
a.stream() << "BOOST_AUTO_TEST_CASE(equal_enums_generate_the_same_hash) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    g();" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    const " << type_name << " b(a);" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::hash<" << qn << "> hasher;" << std::endl;
a.stream() << "    BOOST_CHECK(hasher(a) == hasher(b));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(different_enums_generate_different_hashes) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    g();" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    const " << type_name << " b(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::hash<" << qn << "> hasher;" << std::endl;
a.stream() << "    BOOST_CHECK(hasher(a) != hasher(b));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }
        }
a.stream() << "BOOST_AUTO_TEST_SUITE_END()" << std::endl;
    } // sbf
    return a.make_artefact();
}

}

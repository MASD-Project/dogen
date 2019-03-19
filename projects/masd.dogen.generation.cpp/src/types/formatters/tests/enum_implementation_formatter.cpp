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
#include "masd.dogen.generation.cpp/types/formatters/tests/enum_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/tests/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include <boost/throw_exception.hpp>
#include "masd.dogen.extraction/types/sequence_formatter.hpp"

namespace masd::dogen::generation::cpp::formatters::tests {

std::string enum_implementation_formatter::static_id() {
    return traits::enum_implementation_archetype();
}

std::string enum_implementation_formatter::id() const {
    return static_id();
}

annotations::archetype_location
enum_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          enum_implementation_formatter::static_id());
    return r;
}

const coding::meta_model::name& enum_implementation_formatter::meta_name() const {
    using coding::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

std::string enum_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types enum_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path enum_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const coding::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(enum_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path enum_implementation_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_tests_cpp_implementation(n, static_id());
}

std::list<std::string> enum_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const coding::meta_model::element& e) const {

    auto builder(f.make());
    builder.add(e.name(), types::traits::enum_header_archetype());
    builder.add(e.name(), test_data::traits::enum_header_archetype());

    using ic = inclusion_constants;
    builder.add(ic::std::string());
    builder.add(ic::boost::test::unit_test());

    const auto io_arch(io::traits::enum_header_archetype());
    const bool io_enabled(builder.is_enabled(e.name(), io_arch));
    if (io_enabled) {
        builder.add(e.name(), io_arch);
        builder.add(ic::std::sstream());
        builder.add(ic::boost::property_tree::ptree());
        builder.add(ic::boost::property_tree::json_parser());
    }

    using ser = formatters::serialization::traits;
    const auto ser_arch(ser::enum_header_archetype());
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

    using hash = formatters::hash::traits;
    const auto hash_arch(hash::class_header_archetype());
    const bool hash_enabled(builder.is_enabled(e.name(), hash_arch));
    if (hash_enabled)
        builder.add(e.name(), hash_arch);

    return builder.build();
}

extraction::meta_model::artefact enum_implementation_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        const auto qn(a.get_qualified_name(e.name()));
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
a.stream() << "    const auto a(g());" << std::endl;
a.stream() << "    std::stringstream s;" << std::endl;
a.stream() << "    s << a;" << std::endl;
a.stream() << std::endl;
a.stream() << "    boost::property_tree::ptree pt;" << std::endl;
a.stream() << "    BOOST_REQUIRE_NO_THROW(read_json(s, pt));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }

            if (a.is_serialization_enabled()) {
                /*
                 * Serialization tests.
                 */
a.stream() << "BOOST_AUTO_TEST_CASE(xml_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const auto a(g());" << std::endl;
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
a.stream() << "    const auto a(g());" << std::endl;
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
a.stream() << "    const auto a(g());" << std::endl;
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
a.stream() << "BOOST_AUTO_TEST_CASE(equal_objects_generate_the_same_hash) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    g();" << std::endl;
a.stream() << "    const auto a(g());" << std::endl;
a.stream() << "    const auto b(a);" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::hash<" << qn << "> hasher;" << std::endl;
a.stream() << "    BOOST_CHECK(hasher(a) == hasher(b));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(different_objects_generate_different_hashes) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    g();" << std::endl;
a.stream() << "    const auto a(g());" << std::endl;
a.stream() << "    const auto b(g());" << std::endl;
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

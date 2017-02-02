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
#include "dogen/quilt.cpp/types/formatters/test_data/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

std::string class_implementation_formatter::static_artefact() {
    return traits::class_implementation_archetype();
}

std::string class_implementation_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
class_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(),  cpp::traits::kernel(),
          traits::facet(),
          class_implementation_formatter::static_artefact());
    return r;
}

std::type_index class_implementation_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::object)));
    return r;
}

inclusion_support_types class_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(class_implementation_formatter::static_artefact()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path class_implementation_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_artefact());
}

std::list<std::string> class_implementation_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {

    const auto& o(assistant::as<yarn::object>(static_artefact(), e));
    auto builder(f.make());
    builder.add(o.name(), traits::class_header_archetype());

    const auto si(builder.make_special_includes(o));
    if (si.has_path)
        builder.add(inclusion_constants::std::sstream());

    const auto carch(traits::canonical_archetype());
    builder.add(o.transparent_associations(), carch);
    builder.add(o.opaque_associations(), carch);
    builder.add(o.parents(), carch);
    builder.add(o.leaves(), carch);

    return builder.build();
}

dogen::formatters::artefact class_implementation_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& o(a.as<yarn::object>(static_artefact(), e));

    {
        const auto sn(o.name().simple());
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter());
        if (!o.local_attributes().empty()) {
a.stream() << "namespace {" << std::endl;
        a.add_helper_methods(o.name().id());
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        }

        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));

            /*
             * Default constructor.
             */
            if (!o.is_parent()) {
a.stream() << std::endl;
a.stream() << sn << "_generator::" << sn << "_generator() : position_(0) { }" << std::endl;
            }

            /*
             * Populate method.
             */
            if (!o.is_immutable()) {
                bool no_args(o.local_attributes().empty() && o.parents().empty());
                if (no_args) {
a.stream() << std::endl;
a.stream() << "void " << sn << "_generator::" << std::endl;
a.stream() << "populate(const unsigned int /*position*/, result_type& /*v*/) {" << std::endl;
                } else {
a.stream() << std::endl;
a.stream() << "void " << sn << "_generator::" << std::endl;
a.stream() << "populate(const unsigned int position, result_type& v) {" << std::endl;
                }

                if (!o.parents().empty()) {
                    const auto& pn(o.parents().front());
                    const auto pqn(a.get_qualified_name(pn));
a.stream() << "    " << pqn << "_generator::populate(position, v);" << std::endl;
                }
                unsigned int i(0);
                for (const auto attr : o.local_attributes()) {
a.stream() << "    v." << attr.name().simple() << "(create_" << attr.parsed_type().identifiable() << "(position + " << i << "));" << std::endl;
                    ++i;
                }
a.stream() << "}" << std::endl;
            }

            /*
             * Create method.
             */
            if (!o.is_parent()) {
                 const bool no_arg(o.all_attributes().empty());
a.stream() << std::endl;
a.stream() << sn << "_generator::result_type" << std::endl;
a.stream() << sn << "_generator::create(const unsigned int" << (no_arg ? "/*position*/" : " position") << ") {" << std::endl;
                if (o.is_immutable()) {
a.stream() << "    return " << sn << "(" << std::endl;
                    if (o.local_attributes().empty())
a.stream() << std::endl;
                    else {
                        dogen::formatters::sequence_formatter sf(o.local_attributes().size());
                        for (const auto attr : o.local_attributes()) {
a.stream() << "        create_" << attr.parsed_type().identifiable() << "(position + " << sf.current_position() << ")" << sf.postfix() << std::endl;
                            sf.next();
                        }
                    }
a.stream() << "        );" << std::endl;
                } else {
a.stream() << "    " << sn << " r;" << std::endl;
                    if (!o.all_attributes().empty())
a.stream() << "    " << sn << "_generator::populate(position, r);" << std::endl;
a.stream() << "    return r;" << std::endl;
                }
a.stream() << "}" << std::endl;
            }

            /*
             * Create method ptr.
             */
a.stream() << std::endl;
a.stream() << sn << "_generator::result_type*" << std::endl;
a.stream() << sn << "_generator::create_ptr(const unsigned int position) {" << std::endl;
            if (o.leaves().empty()) {
                if (o.is_immutable())
a.stream() << "    return new " << sn << "(create(position));" << std::endl;
                else {
a.stream() << "    " << sn << "* p = new " << sn << "();" << std::endl;
a.stream() << "    " << sn << "_generator::populate(position, *p);" << std::endl;
a.stream() << "    return p;" << std::endl;
                }
            } else {
                auto leaves(o.leaves());
                const auto front(leaves.front());
                leaves.pop_front();
                unsigned int i(0);
                unsigned int total(leaves.size());
                for (const auto& l : leaves) {
a.stream() << "    if ((position % " << total << ") == " << i++ << ")" << std::endl;
a.stream() << "        return " << a.get_qualified_name(l) << "_generator::create_ptr(position);" << std::endl;
                }
a.stream() << "    return " << a.get_qualified_name(front) << "_generator::create_ptr(position);" << std::endl;
            }
a.stream() << "}" << std::endl;
            /*
             * Function operator
             */
             if (!o.is_parent()) {
a.stream() << std::endl;
a.stream() << sn << "_generator::result_type" << std::endl;
a.stream() << sn << "_generator::operator()() {" << std::endl;
a.stream() << "    return create(position_++);" << std::endl;
a.stream() << "}" << std::endl;
            }
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
} } } } }

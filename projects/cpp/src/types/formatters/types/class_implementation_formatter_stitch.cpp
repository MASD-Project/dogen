/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright(C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/formatters/io/inserter_implementation_helper_stitch.hpp"
#include "dogen/cpp/types/formatters/types/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

dogen::formatters::file class_implementation_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::class_info& c) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        fa.add_helper_methods();

        {
            auto snf(fa.make_scoped_namespace_formatter());

            /*
             * Default constructor.
             */
            if (c.requires_manual_default_constructor()) {
fa.stream() << std::endl;
fa.stream() << c.name() << "::" << c.name() << "()" << std::endl;
                auto sf(fa.make_sequence_formatter(c.properties().size()));
                sf.prefix_configuration().first(": ").not_first("  ");
                sf.postfix_configuration().last(" { }");
                for (const auto p : c.properties()) {
                    if (!p.type().is_primitive() && !p.type().is_enumeration())
                        continue;
fa.stream() << "    " << sf.prefix() << fa.make_member_variable_name(p) << "(static_cast<" << p.type().complete_name() << ">(0))" << sf.postfix() << std::endl;
                }
fa.stream() << std::endl;
            }

            /*
             * Move constructor.
             */
            if (c.requires_manual_move_constructor()) {
fa.stream() << std::endl;
fa.stream() << c.name() << "::" << c.name() << "(" << c.name() << "&& rhs)" << std::endl;
                unsigned int size(c.parents().size() + c.properties().size());
                auto sf(fa.make_sequence_formatter(size));
                sf.prefix_configuration().first(": ").not_first("  ");
                sf.postfix_configuration().last(" { }");

                for (const auto p : c.parents())
fa.stream() << "    " << sf.prefix() << p.qualified_name() << "(std::forward<" << p.qualified_name() << ">(rhs))" << sf.postfix() << std::endl;

                for (const auto p : c.properties())
fa.stream() << "    " << sf.prefix() << fa.make_member_variable_name(p) << "(std::move(rhs." << fa.make_member_variable_name(p) << "))" << sf.postfix() << std::endl;
fa.stream() << std::endl;
            }

            /*
             * Complete constructor.
             */
            if (!c.all_properties().empty()) {
                const auto prop_count(c.all_properties().size());
                if (prop_count == 1) {
                     const auto p(*c.all_properties().begin());
fa.stream() << c.name() << "::" << c.name() << "(const " << p.type().complete_name() << fa.make_by_ref_text(p) << " " << p.name() << ")" << std::endl;
                } else
fa.stream() << c.name() << "::" << c.name() << "(" << std::endl;

                auto sf(fa.make_sequence_formatter(prop_count));
                sf.postfix_configuration().last(")");
                for (const auto p : c.properties())
fa.stream() << "    const " << p.type().complete_name() << fa.make_by_ref_text(p) << " " << p.name() << sf.postfix() << std::endl;

                sf.reset();
                sf.prefix_configuration().first(": ").not_first("  ");
                sf.postfix_configuration().last(" { }");

                for (const auto p : c.properties())
fa.stream() << "    " << sf.prefix() << fa.make_member_variable_name(p) << "(" << p.name() << ")" << sf.postfix() << std::endl;
fa.stream() << std::endl;
            }

            /*
             * Streaming
             */
            if (fa.is_io_enabled()) {

fa.stream() << c.name() << "::to_stream(std::ostream& s) const {" << std::endl;
                io::inserter_implementation_helper_stitch(fa, c);
fa.stream() << "    return(s);" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
            }

            /*
             * Swap
             */
            if (!c.is_immutable() && (!c.all_properties().empty() || c.is_parent())) {
                const bool empty(c.all_properties().empty() && c.parents().empty());
fa.stream() << "void " << c.name() << "::swap(" << c.name() << "& " << (empty ? "" : " other") << ") noexcept {" << std::endl;
               if (!c.parents().empty()) {
                    for (const auto p : c.parents())
fa.stream() << "    " << p.name() << "::swap(other);" << std::endl;
fa.stream() << std::endl;

               }

               if (!c.properties().empty()) {
fa.stream() << "    using std::swap;" << std::endl;
                   for (const auto p : c.properties())
fa.stream() << "    swap(" << fa.make_member_variable_name(p) << ", other." << fa.make_member_variable_name(p) << ");" << std::endl;
               }
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
            }

            /*
             * Equals
             */
            if (!c.is_parent() && !c.parents().empty()) {
fa.stream() << "bool " << c.name() << "::equals(const " << c.original_parent_name_qualified() << "& other) const {" << std::endl;
fa.stream() << "    const " << c.name() << "* const p(dynamic_cast<const " << c.name() << "* const>(&other));" << std::endl;
fa.stream() << "     if (!p) return false;" << std::endl;
fa.stream() << "        return *this == *p;" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
                std::string method_name;
                if (c.is_parent())
                    method_name = "compare";
                else
                    method_name = "operator==";
fa.stream() << "bool " << c.name() << "::" << method_name << "(const " << c.name() << "& " << (c.all_properties().empty() ? "/*rhs*/" : "rhs") << ") const {" << std::endl;

                if (c.all_properties().empty())
fa.stream() << "    return true;" << std::endl;
                else {
fa.stream() << "    return " << std::endl;
                    auto sf(fa.make_sequence_formatter(c.parents().size()));
                    sf.postfix_configuration().not_first(" &&");
                    for (const auto p : c.parents())
fa.stream() << "    " << p.name() << "::compare(rhs)" << sf.postfix() << std::endl;
                    sf.reset(c.properties().size());
                    sf.postfix_configuration().not_first(" &&");
                    sf.postfix_configuration().last(";");
                    for (const auto p : c.properties()) {
fa.stream() << "    " << fa.make_member_variable_name(p) << " == rhs." << fa.make_member_variable_name(p) << sf.postfix() << std::endl;
                    }
                }
fa.stream() << "}" << std::endl;
            }
        } // snf
fa.stream() << std::endl;
    } // sbf
    return fa.make_file(false/*overwrite*/);
}

} } } }

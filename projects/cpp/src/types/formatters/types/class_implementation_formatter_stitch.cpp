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
#include "dogen/formatters/types/sequence_formatter.hpp"
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
                // FIXME: this was just too hard to hack with a sequence.
                // FIXME: indentation is all off too.
                std::ostringstream ss;
                bool is_first(true);
                for (const auto p : c.properties()) {
                    if (!p.type().is_primitive() && !p.type().is_enumeration())
                        continue;

                    if (!is_first)
                        ss << "," << std::endl << "      ";

                    ss << fa.make_member_variable_name(p)
                       << "(static_cast<" << p.type().complete_name()
                       << ">(0))";

                    is_first = false;
                }
                ss << " { }";
                const std::string out(ss.str());
fa.stream() << "    : " << out << std::endl;
            }

            /*
             * Move constructor.
             */
            if (c.requires_manual_move_constructor()) {
fa.stream() << std::endl;
fa.stream() << c.name() << "::" << c.name() << "(" << c.name() << "&& rhs)" << std::endl;
                unsigned int size(c.parents().size() + c.properties().size());

                dogen::formatters::sequence_formatter sf(size);
                sf.prefix_configuration().first(": ").not_first("  ");
                sf.postfix_configuration().last(" { }");
                for (const auto p : c.parents()) {
fa.stream() << "    " << sf.prefix() << p.qualified_name() << "(" << std::endl;
fa.stream() << "        std::forward<" << p.qualified_name() << ">(rhs))" << sf.postfix() << std::endl;
                    sf.next();
                }

                for (const auto p : c.properties()) {
fa.stream() << "    " << sf.prefix() << fa.make_member_variable_name(p) << "(std::move(rhs." << fa.make_member_variable_name(p) << "))" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Complete constructor.
             */
            if (!fa.is_complete_constructor_disabled() && !c.all_properties().empty()) {
                const auto prop_count(c.all_properties().size());
                if (prop_count == 1) {
                     const auto p(*c.all_properties().begin());
fa.stream() << std::endl;
fa.stream() << c.name() << "::" << c.name() << "(const " << p.type().complete_name() << fa.make_by_ref_text(p) << " " << p.name() << ")" << std::endl;
                } else {
fa.stream() << std::endl;
fa.stream() << c.name() << "::" << c.name() << "(" << std::endl;

                    dogen::formatters::sequence_formatter sf(prop_count);
                    sf.postfix_configuration().last(")");
                    for (const auto p : c.all_properties()) {
fa.stream() << "    const " << p.type().complete_name() << fa.make_by_ref_text(p) << " " << p.name() << sf.postfix() << std::endl;
                        sf.next();
                    }
                }

                int sequence_size(c.properties().size() + c.parents().size());
                for (const auto p : c.parents())
                    sequence_size += (p.properties().size() > 1 ?
                        p.properties().size() : 0);

                dogen::formatters::sequence_formatter sf(sequence_size);
                sf.prefix_configuration().first(": ").not_first("  ");
                sf.postfix_configuration().last(" { }");
                for (const auto p : c.parents()) {
                    if (p.properties().size() <= 1) {
fa.stream() << "    " << sf.prefix() << p.qualified_name() << "(" << (p.properties().empty() ? "" : p.properties().front().name()) << ")" << sf.postfix() << std::endl;
                        sf.next();
                    } else {
fa.stream() << "    " << sf.prefix() << p.qualified_name() << "(" << sf.postfix(true/*skip*/) << std::endl;
                        sf.next();
                        dogen::formatters::sequence_formatter sf2(p.properties().size());
                        sf2.element_separator("");

                        sf2.prefix_configuration().first("  ").not_first("  ");
                        sf2.postfix_configuration().last(")");
                        for (const auto prop : p.properties()) {
fa.stream() << "    " << sf2.prefix() << prop.name() << sf2.postfix() << sf.postfix() << std::endl;
                            sf2.next();
                            sf.next();
                        }
                    }
                }

                for (const auto p : c.properties()) {
fa.stream() << "    " << sf.prefix() << fa.make_member_variable_name(p) << "(" << p.name() << ")" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Streaming
             */
            if (fa.is_io_enabled()) {
                if (c.is_parent() || !c.parents().empty()) {
fa.stream() << std::endl;
fa.stream() << "void " << c.name() << "::to_stream(std::ostream& s) const {" << std::endl;
                io::inserter_implementation_helper_stitch(fa, c, true/*inside_class*/);
fa.stream() << "}" << std::endl;
                }
            }

            /*
             * Swap
             */
            if (!c.is_immutable() && (!c.all_properties().empty() || c.is_parent())) {
                const bool empty(c.all_properties().empty() && c.parents().empty());
fa.stream() << std::endl;
fa.stream() << "void " << c.name() << "::swap(" << c.name() << "&" << (empty ? "" : " other") << ") noexcept {" << std::endl;
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
            }

            /*
             * Equals method
             */
            if (!c.is_parent() && !c.parents().empty()) {
fa.stream() << std::endl;
fa.stream() << "bool " << c.name() << "::equals(const " << c.root_parent_name_qualified() << "& other) const {" << std::endl;
fa.stream() << "    const " << c.name() << "* const p(dynamic_cast<const " << c.name() << "* const>(&other));" << std::endl;
fa.stream() << "    if (!p) return false;" << std::endl;
fa.stream() << "    return *this == *p;" << std::endl;
fa.stream() << "}" << std::endl;
            }

            /*
             * Equals operator
             */
            std::string method_name;
            if (c.is_parent())
                method_name = "compare";
            else
                method_name = "operator==";
fa.stream() << std::endl;
fa.stream() << "bool " << c.name() << "::" << method_name << "(const " << c.name() << "& " << (c.all_properties().empty() ? "/*rhs*/" : "rhs") << ") const {" << std::endl;

            if (c.all_properties().empty())
fa.stream() << "    return true;" << std::endl;
            else {
                dogen::formatters::sequence_formatter sf(c.parents().size());
                sf.element_separator("");
                sf.prefix_configuration().first("return ").not_first("    ");
                sf.postfix_configuration().not_last(" &&");
                if (c.properties().empty())
                    sf.postfix_configuration().last(";");
                else
                    sf.postfix_configuration().last(" &&");

                for (const auto p : c.parents()) {
fa.stream() << "    " << sf.prefix() << p.name() << "::compare(rhs)" << sf.postfix() << std::endl;
                    sf.next();
                }
                sf.reset(c.properties().size());
                sf.element_separator("");
                if (c.parents().empty())
                   sf.prefix_configuration().first("return ");
                else
                   sf.prefix_configuration().first("    ");
                sf.prefix_configuration().not_first("    ");
                sf.postfix_configuration().last(";").not_last(" &&");
                for (const auto p : c.properties()) {
fa.stream() << "    " << sf.prefix() << fa.make_member_variable_name(p) << " == rhs." << fa.make_member_variable_name(p) << sf.postfix() << std::endl;
                    sf.next();
                }
            }
fa.stream() << "}" << std::endl;

            /*
             * Assignment
             */
            if (!c.all_properties().empty() && !c.is_parent() && !c.is_immutable()) {
fa.stream() << std::endl;
fa.stream() << c.name() << "& " << c.name() << "::operator=(" << c.name() << " other) {" << std::endl;
fa.stream() << "    using std::swap;" << std::endl;
fa.stream() << "    swap(*this, other);" << std::endl;
fa.stream() << "    return *this;" << std::endl;
fa.stream() << "}" << std::endl;
            }

            /*
             * Getters and setters
             */
             for (const auto p : c.properties()) {
                 if (p.type().is_primitive() || p.type().is_enumeration()) {
fa.stream() << std::endl;
fa.stream() << p.type().complete_name() << " " << c.name() << "::" << p.name() << "() const {" << std::endl;
fa.stream() << "    return " << fa.make_member_variable_name(p) << ";" << std::endl;
fa.stream() << "}" << std::endl;
                    if (!c.is_immutable()) {
fa.stream() << std::endl;
fa.stream() << (p.is_fluent() ? c.name() + "&" : "void") << " " << c.name() << "::" << p.name() << "(const " << p.type().complete_name() << " v) {" << std::endl;
fa.stream() << "    " << fa.make_member_variable_name(p) << " = v;" << std::endl;
                        if (p.is_fluent()) {
fa.stream() << "    return *this;" << std::endl;
                        }
fa.stream() << "}" << std::endl;
                    }
                } else {
fa.stream() << std::endl;
fa.stream() << "const " << p.type().complete_name() << "& " << c.name() << "::" << p.name() << "() const {" << std::endl;
fa.stream() << "    return " << fa.make_member_variable_name(p) << ";" << std::endl;
fa.stream() << "}" << std::endl;
                    if (!c.is_immutable()) {
fa.stream() << std::endl;
fa.stream() << p.type().complete_name() << "& " << c.name() << "::" << p.name() << "() {" << std::endl;
fa.stream() << "    return " << fa.make_member_variable_name(p) << ";" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
fa.stream() << (p.is_fluent() ? c.name() + "&" : "void") << " " << c.name() << "::" << p.name() << "(const " << p.type().complete_name() << "& v) {" << std::endl;
fa.stream() << "    " << fa.make_member_variable_name(p) << " = v;" << std::endl;
                        if (p.is_fluent()) {
fa.stream() << "    return *this;" << std::endl;
                        }
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
fa.stream() << (p.is_fluent() ? c.name() + "&" : "void") << " " << c.name() << "::" << p.name() << "(const " << p.type().complete_name() << "&& v) {" << std::endl;
fa.stream() << "    " << fa.make_member_variable_name(p) << " = std::move(v);" << std::endl;
                        if (p.is_fluent()) {
fa.stream() << "    return *this;" << std::endl;
                        }
fa.stream() << "}" << std::endl;
                    }
                }
            }
fa.stream() << std::endl;
        } // snf
    } // sbf
    return fa.make_file();
}

} } } }

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
#include "dogen/quilt.cpp/types/formatters/io/inserter_implementation_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/types/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {

dogen::formatters::file class_implementation_formatter_stitch(
    assistant& a, const properties::class_info& c) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        a.add_helper_methods(c);
        a.add_helper_methods();

        {
            auto snf(a.make_scoped_namespace_formatter(c.namespaces()));

            /*
             * Default constructor.
             */
            if (c.requires_manual_default_constructor()) {
a.stream() << std::endl;
a.stream() << c.name() << "::" << c.name() << "()" << std::endl;
                // FIXME: this was just too hard to hack with a sequence.
                // FIXME: indentation is all off too.
                std::ostringstream ss;
                bool is_first(true);
                for (const auto p : c.properties()) {
                    if (!p.type().is_primitive() && !p.type().is_enumeration())
                        continue;

                    if (!is_first)
                        ss << "," << std::endl << "      ";

                    ss << a.make_member_variable_name(p)
                       << "(static_cast<" << p.type().complete_name()
                       << ">(0))";

                    is_first = false;
                }
                ss << " { }";
                const std::string out(ss.str());
a.stream() << "    : " << out << std::endl;
            }

            /*
             * Move constructor.
             */
            if (c.requires_manual_move_constructor()) {
a.stream() << std::endl;
a.stream() << c.name() << "::" << c.name() << "(" << c.name() << "&& rhs)" << std::endl;
                unsigned int size(c.parents().size() + c.properties().size());

                dogen::formatters::sequence_formatter sf(size);
                sf.prefix_configuration().first(": ").not_first("  ");
                sf.postfix_configuration().last(" { }");
                for (const auto p : c.parents()) {
a.stream() << "    " << sf.prefix() << p.qualified_name() << "(" << std::endl;
a.stream() << "        std::forward<" << p.qualified_name() << ">(rhs))" << sf.postfix() << std::endl;
                    sf.next();
                }

                for (const auto p : c.properties()) {
a.stream() << "    " << sf.prefix() << a.make_member_variable_name(p) << "(std::move(rhs." << a.make_member_variable_name(p) << "))" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Complete constructor.
             */
            if (!a.is_complete_constructor_disabled() && !c.all_properties().empty()) {
                const auto prop_count(c.all_properties().size());
                if (prop_count == 1) {
                     const auto p(*c.all_properties().begin());
a.stream() << std::endl;
a.stream() << c.name() << "::" << c.name() << "(const " << p.type().complete_name() << a.make_by_ref_text(p) << " " << p.name() << ")" << std::endl;
                } else {
a.stream() << std::endl;
a.stream() << c.name() << "::" << c.name() << "(" << std::endl;

                    dogen::formatters::sequence_formatter sf(prop_count);
                    sf.postfix_configuration().last(")");
                    for (const auto p : c.all_properties()) {
a.stream() << "    const " << p.type().complete_name() << a.make_by_ref_text(p) << " " << p.name() << sf.postfix() << std::endl;
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
a.stream() << "    " << sf.prefix() << p.qualified_name() << "(" << (p.properties().empty() ? "" : p.properties().front().name()) << ")" << sf.postfix() << std::endl;
                        sf.next();
                    } else {
a.stream() << "    " << sf.prefix() << p.qualified_name() << "(" << sf.postfix(true/*skip*/) << std::endl;
                        sf.next();
                        dogen::formatters::sequence_formatter sf2(p.properties().size());
                        sf2.element_separator("");

                        sf2.prefix_configuration().first("  ").not_first("  ");
                        sf2.postfix_configuration().last(")");
                        for (const auto prop : p.properties()) {
a.stream() << "    " << sf2.prefix() << prop.name() << sf2.postfix() << sf.postfix() << std::endl;
                            sf2.next();
                            sf.next();
                        }
                    }
                }

                for (const auto p : c.properties()) {
a.stream() << "    " << sf.prefix() << a.make_member_variable_name(p) << "(" << p.name() << ")" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Streaming
             */
            if (a.is_io_enabled()) {
                if (c.is_parent() || !c.parents().empty()) {
a.stream() << std::endl;
a.stream() << "void " << c.name() << "::to_stream(std::ostream& s) const {" << std::endl;
                io::inserter_implementation_helper_stitch(a, c, true/*inside_class*/);
a.stream() << "}" << std::endl;
                }
            }

            /*
             * Swap
             */
            if (!c.is_immutable() && (!c.all_properties().empty() || c.is_parent())) {
                const bool empty(c.all_properties().empty() && c.parents().empty());
a.stream() << std::endl;
a.stream() << "void " << c.name() << "::swap(" << c.name() << "&" << (empty ? "" : " other") << ") noexcept {" << std::endl;
               if (!c.parents().empty()) {
                    for (const auto p : c.parents())
a.stream() << "    " << p.name() << "::swap(other);" << std::endl;
a.stream() << std::endl;

               }

               if (!c.properties().empty()) {
a.stream() << "    using std::swap;" << std::endl;
                   for (const auto p : c.properties())
a.stream() << "    swap(" << a.make_member_variable_name(p) << ", other." << a.make_member_variable_name(p) << ");" << std::endl;
               }
a.stream() << "}" << std::endl;
            }

            /*
             * Equals method
             */
            if (!c.is_parent() && !c.parents().empty()) {
a.stream() << std::endl;
a.stream() << "bool " << c.name() << "::equals(const " << c.root_parent_name_qualified() << "& other) const {" << std::endl;
a.stream() << "    const " << c.name() << "* const p(dynamic_cast<const " << c.name() << "* const>(&other));" << std::endl;
a.stream() << "    if (!p) return false;" << std::endl;
a.stream() << "    return *this == *p;" << std::endl;
a.stream() << "}" << std::endl;
            }

            /*
             * Equals operator
             */
            std::string method_name;
            if (c.is_parent())
                method_name = "compare";
            else
                method_name = "operator==";
a.stream() << std::endl;
a.stream() << "bool " << c.name() << "::" << method_name << "(const " << c.name() << "& " << (c.all_properties().empty() ? "/*rhs*/" : "rhs") << ") const {" << std::endl;

            if (c.all_properties().empty())
a.stream() << "    return true;" << std::endl;
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
a.stream() << "    " << sf.prefix() << p.name() << "::compare(rhs)" << sf.postfix() << std::endl;
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
a.stream() << "    " << sf.prefix() << a.make_member_variable_name(p) << " == rhs." << a.make_member_variable_name(p) << sf.postfix() << std::endl;
                    sf.next();
                }
            }
a.stream() << "}" << std::endl;

            /*
             * Assignment
             */
            if (!c.all_properties().empty() && !c.is_parent() && !c.is_immutable()) {
a.stream() << std::endl;
a.stream() << c.name() << "& " << c.name() << "::operator=(" << c.name() << " other) {" << std::endl;
a.stream() << "    using std::swap;" << std::endl;
a.stream() << "    swap(*this, other);" << std::endl;
a.stream() << "    return *this;" << std::endl;
a.stream() << "}" << std::endl;
            }

            /*
             * Getters and setters
             */
             for (const auto p : c.properties()) {
                 if (p.type().is_primitive() || p.type().is_enumeration()) {
a.stream() << std::endl;
a.stream() << p.type().complete_name() << " " << c.name() << "::" << p.name() << "() const {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(p) << ";" << std::endl;
a.stream() << "}" << std::endl;
                    if (!c.is_immutable()) {
a.stream() << std::endl;
a.stream() << (p.is_fluent() ? c.name() + "&" : "void") << " " << c.name() << "::" << p.name() << "(const " << p.type().complete_name() << " v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(p) << " = v;" << std::endl;
                        if (p.is_fluent()) {
a.stream() << "    return *this;" << std::endl;
                        }
a.stream() << "}" << std::endl;
                    }
                } else {
a.stream() << std::endl;
a.stream() << "const " << p.type().complete_name() << "& " << c.name() << "::" << p.name() << "() const {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(p) << ";" << std::endl;
a.stream() << "}" << std::endl;
                    if (!c.is_immutable()) {
a.stream() << std::endl;
a.stream() << p.type().complete_name() << "& " << c.name() << "::" << p.name() << "() {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(p) << ";" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << (p.is_fluent() ? c.name() + "&" : "void") << " " << c.name() << "::" << p.name() << "(const " << p.type().complete_name() << "& v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(p) << " = v;" << std::endl;
                        if (p.is_fluent()) {
a.stream() << "    return *this;" << std::endl;
                        }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << (p.is_fluent() ? c.name() + "&" : "void") << " " << c.name() << "::" << p.name() << "(const " << p.type().complete_name() << "&& v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(p) << " = std::move(v);" << std::endl;
                        if (p.is_fluent()) {
a.stream() << "    return *this;" << std::endl;
                        }
a.stream() << "}" << std::endl;
                    }
                }
            }
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_file();
}

} } } } }

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
    assistant& a, const yarn::object& o) {

    {
        const auto sn(o.name().simple());
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter());
        a.add_helper_methods(o.name().id());

        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));

            /*
             * Default constructor.
             */
            if (a.requires_manual_default_constructor()) {
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "()" << std::endl;
                // FIXME: this was just too hard to hack with a sequence.
                // FIXME: indentation is all off too.
                std::ostringstream ss;
                bool is_first(true);
                for (const auto attr : o.local_attributes()) {
                    if (!attr.parsed_type().is_current_simple_type())
                        continue;

                    if (!is_first)
                        ss << "," << std::endl << "      ";

                    ss << a.make_member_variable_name(attr)
                       << "(static_cast<" << a.get_qualified_name(attr.parsed_type())
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
            if (a.requires_manual_move_constructor()) {
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "(" << sn << "&& rhs)" << std::endl;
                unsigned int size((o.parent() ? 1 : 0) + o.local_attributes().size());

                dogen::formatters::sequence_formatter sf(size);
                sf.prefix_configuration().first(": ").not_first("  ");
                sf.postfix_configuration().last(" { }");
                if (o.parent()) {
                    const auto& pn(*o.parent());
                    const auto pqn(a.get_qualified_name(pn));
a.stream() << "    " << sf.prefix() << pqn << "(" << std::endl;
a.stream() << "        std::forward<" << pqn << ">(rhs))" << sf.postfix() << std::endl;
                    sf.next();
                }

                for (const auto attr : o.local_attributes()) {
a.stream() << "    " << sf.prefix() << a.make_member_variable_name(attr) << "(std::move(rhs." << a.make_member_variable_name(attr) << "))" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Complete constructor.
             */
            if (!o.all_attributes().empty()) {
                const auto attr_count(o.all_attributes().size());
                if (attr_count == 1) {
                     const auto attr(*o.all_attributes().begin());
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << ")" << std::endl;
                } else {
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "(" << std::endl;

                    dogen::formatters::sequence_formatter sf(attr_count);
                    sf.postfix_configuration().last(")");
                    for (const auto attr : o.all_attributes()) {
a.stream() << "    const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << sf.postfix() << std::endl;
                        sf.next();
                    }
                }

                int sequence_size(o.local_attributes().size() + (o.parent() ? 1 : 0));
                for (const auto pair : o.inherited_attributes()) {
                    const auto& pattrs(pair.second);
                    sequence_size += (pattrs.size() > 1 ? pattrs.size() : 0);
                }

                dogen::formatters::sequence_formatter sf(sequence_size);
                sf.postfix_configuration().last(" { }");
                sf.prefix_configuration().first(": ").not_first("  ");
                for (const auto pair : o.inherited_attributes()) {
                    const auto pqn(a.get_qualified_name(pair.first));
                    const auto& pattrs(pair.second);
                    if (pattrs.size() <= 1) {
a.stream() << "    " << sf.prefix() << pqn << "(" << (pattrs.empty() ? "" : pattrs.front().name().simple()) << ")" << sf.postfix() << std::endl;
                        sf.next();
                    } else {
a.stream() << "    " << sf.prefix() << pqn << "(" << sf.postfix(true/*skip*/) << std::endl;
                        sf.next();
                        dogen::formatters::sequence_formatter sf2(pattrs.size());
                        sf2.element_separator("");

                        sf2.prefix_configuration().first("  ").not_first("  ");
                        sf2.postfix_configuration().last(")");
                        for (const auto attr : pattrs) {
a.stream() << "    " << sf2.prefix() << attr.name().simple() << sf2.postfix() << sf.postfix() << std::endl;
                            sf2.next();
                            sf.next();
                        }
                    }
                }

                for (const auto attr : o.local_attributes()) {
a.stream() << "    " << sf.prefix() << a.make_member_variable_name(attr) << "(" << attr.name().simple() << ")" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Visitation.
             */
            if (o.is_visitation_leaf()) {
                std::string bvn;
                std::string dvn;
                std::string rpn;
                if (o.derived_visitor()) {
                    bvn = a.get_qualified_name(*o.base_visitor());
                    dvn = o.derived_visitor()->simple();
                    rpn = a.get_qualified_name(*o.root_parent());
                } else {
                    bvn = o.base_visitor()->simple();
                    rpn = o.root_parent()->simple();
                }
a.stream() << std::endl;
a.stream() << "void " << sn << "::accept(const " << bvn << "& v) const {" << std::endl;
                if (o.derived_visitor()) {
a.stream() << "    typedef const " << dvn << "* derived_ptr;" << std::endl;
a.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
a.stream() << "    if (dv)" << std::endl;
a.stream() << "        dv->visit(*this);" << std::endl;
                } else {
a.stream() << "    v.visit(*this);" << std::endl;
                }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "void " << sn << "::accept(" << bvn << "& v) const {" << std::endl;
                if (o.derived_visitor()) {
a.stream() << "    typedef " << dvn << "* derived_ptr;" << std::endl;
a.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
a.stream() << "    if (dv)" << std::endl;
a.stream() << "        dv->visit(*this);" << std::endl;
                } else {
a.stream() << "    v.visit(*this);" << std::endl;
                }
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "void " << sn << "::accept(const " << bvn << "& v) {" << std::endl;
                if (o.derived_visitor()) {
a.stream() << "    typedef const " << dvn << "* derived_ptr;" << std::endl;
a.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
a.stream() << "    if (dv)" << std::endl;
a.stream() << "        dv->visit(*this);" << std::endl;
                } else {
a.stream() << "    v.visit(*this);" << std::endl;
                }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "void " << sn << "::accept(" << bvn << "& v) {" << std::endl;
                if (o.derived_visitor()) {
a.stream() << "    typedef " << dvn << "* derived_ptr;" << std::endl;
a.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
a.stream() << "    if (dv)" << std::endl;
a.stream() << "        dv->visit(*this);" << std::endl;
                } else {
a.stream() << "    v.visit(*this);" << std::endl;
                }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Streaming
             */
            if (a.is_io_enabled()) {
                if (o.in_inheritance_relationship()) {
a.stream() << std::endl;
a.stream() << "void " << sn << "::to_stream(std::ostream& s) const {" << std::endl;
                io::inserter_implementation_helper_stitch(a, o, true/*inside_class*/);
a.stream() << "}" << std::endl;
                }
            }

            /*
             * Swap
             */
            if (!o.is_immutable() && (!o.all_attributes().empty() || o.is_parent())) {
                const bool empty(o.all_attributes().empty() && !o.parent());
a.stream() << std::endl;
a.stream() << "void " << sn << "::swap(" << sn << "&" << (empty ? "" : " other") << ") noexcept {" << std::endl;
               if (o.parent()) {
                    const auto& pn(*o.parent());
a.stream() << "    " << pn.simple() << "::swap(other);" << std::endl;
a.stream() << std::endl;

               }

               if (!o.local_attributes().empty()) {
a.stream() << "    using std::swap;" << std::endl;
                   for (const auto attr : o.local_attributes())
a.stream() << "    swap(" << a.make_member_variable_name(attr) << ", other." << a.make_member_variable_name(attr) << ");" << std::endl;
               }
a.stream() << "}" << std::endl;
            }

            /*
             * Equals method
             */
            // FIXME: looking at root_parent as a hack due to service leafs not
            // FIXME: being processed atm.
            if (!o.is_parent() && o.parent() && o.root_parent()) {
                const auto rpn(*o.root_parent());
a.stream() << std::endl;
a.stream() << "bool " << sn << "::equals(const " << a.get_qualified_name(rpn) << "& other) const {" << std::endl;
a.stream() << "    const " << sn << "* const p(dynamic_cast<const " << sn << "* const>(&other));" << std::endl;
a.stream() << "    if (!p) return false;" << std::endl;
a.stream() << "    return *this == *p;" << std::endl;
a.stream() << "}" << std::endl;
            }

            /*
             * Equals operator
             */
            std::string method_name;
            if (o.is_parent())
                method_name = "compare";
            else
                method_name = "operator==";
a.stream() << std::endl;
a.stream() << "bool " << sn << "::" << method_name << "(const " << sn << "& " << (o.all_attributes().empty() ? "/*rhs*/" : "rhs") << ") const {" << std::endl;

            if (o.all_attributes().empty())
a.stream() << "    return true;" << std::endl;
            else {
                dogen::formatters::sequence_formatter sf(o.parent() ? 1 : 0);
                sf.element_separator("");
                sf.prefix_configuration().first("return ").not_first("    ");
                sf.postfix_configuration().not_last(" &&");
                if (o.local_attributes().empty())
                    sf.postfix_configuration().last(";");
                else
                    sf.postfix_configuration().last(" &&");

                if (o.parent()) {
                    const auto& pn(*o.parent());
a.stream() << "    " << sf.prefix() << pn.simple() << "::compare(rhs)" << sf.postfix() << std::endl;
                    sf.next();
                }
                sf.reset(o.local_attributes().size());
                sf.element_separator("");
                if (!o.parent())
                   sf.prefix_configuration().first("return ");
                else
                   sf.prefix_configuration().first("    ");
                sf.prefix_configuration().not_first("    ");
                sf.postfix_configuration().last(";").not_last(" &&");
                for (const auto attr : o.local_attributes()) {
a.stream() << "    " << sf.prefix() << a.make_member_variable_name(attr) << " == rhs." << a.make_member_variable_name(attr) << sf.postfix() << std::endl;
                    sf.next();
                }
            }
a.stream() << "}" << std::endl;

            /*
             * Assignment
             */
            if (!o.all_attributes().empty() && !o.is_parent() && !o.is_immutable()) {
a.stream() << std::endl;
a.stream() << sn << "& " << sn << "::operator=(" << sn << " other) {" << std::endl;
a.stream() << "    using std::swap;" << std::endl;
a.stream() << "    swap(*this, other);" << std::endl;
a.stream() << "    return *this;" << std::endl;
a.stream() << "}" << std::endl;
            }

            /*
             * Getters and setters
             */
             for (const auto attr : o.local_attributes()) {
                 if (attr.parsed_type().is_current_simple_type()) {
a.stream() << std::endl;
a.stream() << a.get_qualified_name(attr.parsed_type()) << " " << sn << "::" << attr.name().simple() << "() const {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(attr) << ";" << std::endl;
a.stream() << "}" << std::endl;
                    if (!o.is_immutable()) {
a.stream() << std::endl;
a.stream() << (attr.is_fluent() ? sn + "&" : "void") << " " << sn << "::" << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << " v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(attr) << " = v;" << std::endl;
                        if (attr.is_fluent()) {
a.stream() << "    return *this;" << std::endl;
                        }
a.stream() << "}" << std::endl;
                    }
                } else {
a.stream() << std::endl;
a.stream() << "const " << a.get_qualified_name(attr.parsed_type()) << "& " << sn << "::" << attr.name().simple() << "() const {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(attr) << ";" << std::endl;
a.stream() << "}" << std::endl;
                    if (!o.is_immutable()) {
a.stream() << std::endl;
a.stream() << a.get_qualified_name(attr.parsed_type()) << "& " << sn << "::" << attr.name().simple() << "() {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(attr) << ";" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << (o.is_fluent() ? sn + "&" : "void") << " " << sn << "::" << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << "& v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(attr) << " = v;" << std::endl;
                        if (o.is_fluent()) {
a.stream() << "    return *this;" << std::endl;
                        }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << (o.is_fluent() ? sn + "&" : "void") << " " << sn << "::" << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << "&& v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(attr) << " = std::move(v);" << std::endl;
                        if (o.is_fluent()) {
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

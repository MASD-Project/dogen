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
#include "dogen/quilt.cpp/types/formatters/types/class_header_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {

dogen::formatters::artefact
class_header_formatter_stitch(assistant& a, const yarn::object& o) {
    {
        const auto sn(o.name().simple());
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
            a.comment(o.documentation());
            if (!o.parent()) {
a.stream() << "class " << sn << " " << a.make_final_keyword_text(o) << "{" << std::endl;
            } else {
                const auto& pn(*o.parent());
                const auto pqn(a.get_qualified_name(pn));
a.stream() << "class " << sn << " " << a.make_final_keyword_text(o) << ": public " << pqn << " {" << std::endl;
            }
a.stream() << "public:" << std::endl;
            /*
             * Compiler generated constructors and destructors.
             */
            if (!a.requires_manual_default_constructor())
a.stream() << "    " << sn << "() = default;" << std::endl;
a.stream() << "    " << sn << "(const " << sn << "&) = default;" << std::endl;
            if (!a.requires_manual_move_constructor())
a.stream() << "    " << sn << "(" << sn << "&&) = default;" << std::endl;
            if (!o.in_inheritance_relationship())
a.stream() << "    ~" << sn << "() = default;" << std::endl;
            if (o.is_immutable())
a.stream() << "    " << sn << "& operator=(const " << sn << "&) = delete;" << std::endl;
            else if (o.all_attributes().empty())
a.stream() << "    " << sn << "& operator=(const " << sn << "&) = default;" << std::endl;
a.stream() << std::endl;
            /*
             * Manually generated default constructor.
             */
            if (a.requires_manual_default_constructor()) {
a.stream() << "public:" << std::endl;
a.stream() << "    " << sn << "();" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated destructor.
             *
             * according to MEC++, item 33, base classes should always be
             * abstract. this avoids all sorts of tricky problems with
             * assignment and swap.
             *
             * incidentally, this also fixes some strange clang errors:
             * undefined reference to `vtable.
             */
            if (o.is_parent()) {
a.stream() << "    virtual ~" << sn << "() noexcept = 0;" << std::endl;
a.stream() << std::endl;
            } else if (o.is_child() != 0) {
a.stream() << "    virtual ~" << sn << "() noexcept { }" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated move constructor.
             */
            if (a.requires_manual_move_constructor()) {
a.stream() << "public:" << std::endl;
a.stream() << "    " << sn << "(" << sn << "&& rhs);" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated complete constructor.
             */
            if (!o.all_attributes().empty()) {
a.stream() << "public:" << std::endl;
                const auto attr_count(o.all_attributes().size());
                if (attr_count == 1) {
                    const auto attr(*o.all_attributes().begin());
a.stream() << "    explicit " << sn << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << ");" << std::endl;
                } else {
a.stream() << "    " << sn << "(" << std::endl;
                    dogen::formatters::sequence_formatter sf(attr_count);
                    sf.postfix_configuration().last(");");
                    for (const auto& attr : o.all_attributes()) {
a.stream() << "        const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << sf.postfix() << std::endl;
                        sf.next();
                    }
                }
a.stream() << std::endl;
            }

            /*
             * Serialisaton Friends
             */
            if (a.is_serialization_enabled()) {
a.stream() << "private:" << std::endl;
a.stream() << "    template<typename Archive>" << std::endl;
a.stream() << "    friend void boost::serialization::save(Archive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "    template<typename Archive>" << std::endl;
a.stream() << "    friend void boost::serialization::load(Archive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Visitation.
             */
            if (o.is_visitation_root()) {
                const auto vsn(o.base_visitor()->simple());
a.stream() << "public:" << std::endl;
a.stream() << "    virtual void accept(const " << vsn << "& v) const = 0;" << std::endl;
a.stream() << "    virtual void accept(" << vsn << "& v) const = 0;" << std::endl;
a.stream() << "    virtual void accept(const " << vsn << "& v) = 0;" << std::endl;
a.stream() << "    virtual void accept(" << vsn << "& v) = 0;" << std::endl;
a.stream() << std::endl;
            } else if (o.is_visitation_leaf()) {
                std::string bvn;
                std::string rpn;
                if (o.derived_visitor()) {
                    bvn = a.get_qualified_name(*o.base_visitor());
                    rpn = a.get_qualified_name(*o.root_parent());
                } else {
                    bvn = o.base_visitor()->simple();
                    rpn = o.root_parent()->simple();
                }
a.stream() << "public:" << std::endl;
a.stream() << "    using " << rpn << "::accept;" << std::endl;
a.stream() << std::endl;
a.stream() << "    virtual void accept(const " << bvn << "& v) const override;" << std::endl;
a.stream() << "    virtual void accept(" << bvn << "& v) const override;" << std::endl;
a.stream() << "    virtual void accept(const " << bvn << "& v) override;" << std::endl;
a.stream() << "    virtual void accept(" << bvn << "& v) override;" << std::endl;
            }

            /*
             * Streaming
             */
            if (a.is_io_enabled()) {
                if (o.is_parent()) {
a.stream() << "public:" << std::endl;
a.stream() << "    virtual void to_stream(std::ostream& s) const;" << std::endl;
a.stream() << std::endl;
                } else if (o.parent()) {
a.stream() << "public:" << std::endl;
a.stream() << "    void to_stream(std::ostream& s) const override;" << std::endl;
a.stream() << std::endl;
                }
            }

            /*
             * Getters and setters.
             */
            if (!o.local_attributes().empty()) {
a.stream() << "public:" << std::endl;
                for (const auto& attr : o.local_attributes()) {
                    a.comment_start_method_group(attr.documentation(), !attr.is_immutable());

                    if (attr.parsed_type().is_current_simple_type()) {
a.stream() << "    " << a.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << "() const;" << std::endl;
                        if (attr.is_immutable()) {
a.stream() << std::endl;
                            continue;
                        }
a.stream() << "    " << a.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " v);" << std::endl;
                    } else {
a.stream() << "    const " << a.get_qualified_name(attr.parsed_type()) << "& " << attr.name().simple() << "() const;" << std::endl;
                        if (attr.is_immutable()) {
a.stream() << std::endl;
                            continue;
                        }
a.stream() << "    " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << "();" << std::endl;
a.stream() << "    " << a.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " v);" << std::endl;
a.stream() << "    " << a.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << "&& v);" << std::endl;
                    }
                    a.comment_end_method_group(attr.documentation(), !attr.is_immutable());
a.stream() << std::endl;
                }
            }

            /*
             * Equality.
             *
             * Equality is only public in leaf classes - MEC++-33.
             */
            if (o.is_parent()) {
a.stream() << "protected:" << std::endl;
a.stream() << "    bool compare(const " << sn << "& rhs) const;" << std::endl;
            } else {
a.stream() << "public:" << std::endl;
a.stream() << "    bool operator==(const " << sn << "& rhs) const;" << std::endl;
a.stream() << "    bool operator!=(const " << sn << "& rhs) const {" << std::endl;
a.stream() << "        return !this->operator==(rhs);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
            }

            if (o.in_inheritance_relationship()) {
a.stream() << "public:" << std::endl;
                if (o.is_parent() && !o.is_child()) {
a.stream() << "    virtual bool equals(const " << sn << "& other) const = 0;" << std::endl;
                } else if (o.is_parent()) {
                    const auto rpn(*o.root_parent());
a.stream() << "    virtual bool equals(const " << a.get_qualified_name(rpn) << "& other) const = 0;" << std::endl;
                } else if (o.root_parent()) {
                    const auto rpn(*o.root_parent());
a.stream() << "    bool equals(const " << a.get_qualified_name(rpn) << "& other) const override;" << std::endl;
                }
a.stream() << std::endl;
             }

            /*
             * Swap and assignment.
             *
             * Swap and assignment are only public in leaf classes - MEC++-33
             */
            if ((!o.all_attributes().empty() || o.is_parent()) && !o.is_immutable()) {
                if (o.is_parent()) {
a.stream() << "protected:" << std::endl;
                } else {
a.stream() << "public:" << std::endl;
                }
a.stream() << "    void swap(" << sn << "& other) noexcept;" << std::endl;
                if (!o.is_parent() && !o.is_immutable()) {
a.stream() << "    " << sn << "& operator=(" << sn << " other);" << std::endl;
                }
a.stream() << std::endl;
            }

            /*
             * Member variables.
             */
            if (!o.local_attributes().empty()) {
a.stream() << "private:" << std::endl;
                for (const auto& attr : o.local_attributes()) {
a.stream() << "    " << a.get_qualified_name(attr.parsed_type()) << " " << a.make_member_variable_name(attr) << ";" << std::endl;
                }
            }
a.stream() << "};" << std::endl;
a.stream() << std::endl;
            /*
             * Destructor implementation.
             */
            if (o.is_parent()) {
a.stream() << "inline " << sn << "::~" << sn << "() noexcept { }" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Global equality operator implementation.
             */
            if (o.is_parent()) {
a.stream() << "inline bool operator==(const " << sn << "& lhs, const " << sn << "& rhs) {" << std::endl;
a.stream() << "    return lhs.equals(rhs);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }
        }

        if (!o.all_attributes().empty() && !o.is_parent() && !o.is_immutable()) {
a.stream() << std::endl;
a.stream() << "namespace std {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>" << std::endl;
a.stream() << "inline void swap(" << std::endl;
a.stream() << "    " << qn << "& lhs," << std::endl;
a.stream() << "    " << qn << "& rhs) {" << std::endl;
a.stream() << "    lhs.swap(rhs);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
        }
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
} } } } }

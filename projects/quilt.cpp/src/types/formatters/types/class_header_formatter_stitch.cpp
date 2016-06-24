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

dogen::formatters::file class_header_formatter_stitch(
    assistant& a, const properties::class_info& c) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            auto snf(a.make_scoped_namespace_formatter(c.namespaces()));
a.stream() << std::endl;
            a.comment(c.documentation());
            if (c.parents().empty()) {
a.stream() << "class " << c.name() << " " << a.make_final_keyword_text(c) << "{" << std::endl;
            } else if (c.parents().size() == 1) {
a.stream() << "class " << c.name() << " " << a.make_final_keyword_text(c) << ": public " << c.parents().front().qualified_name() << " {" << std::endl;
            } else {
                dogen::formatters::sequence_formatter sf(c.parents().size());
                for (const auto p : c.parents()) {
a.stream() << "    public " << p.qualified_name() << sf.postfix() << std::endl;
                    sf.next();
                }
            }
a.stream() << "public:" << std::endl;
            /*
             * Compiler generated constructors and destructors.
             */
            if (!c.requires_manual_default_constructor())
a.stream() << "    " << c.name() << "() = default;" << std::endl;
a.stream() << "    " << c.name() << "(const " << c.name() << "&) = default;" << std::endl;
            if (!c.requires_manual_move_constructor())
a.stream() << "    " << c.name() << "(" << c.name() << "&&) = default;" << std::endl;
            if (!c.is_parent() && c.parents().empty())
a.stream() << "    ~" << c.name() << "() = default;" << std::endl;
            if (c.is_immutable())
a.stream() << "    " << c.name() << "& operator=(const " << c.name() << "&) = delete;" << std::endl;
            else if (c.all_properties().empty())
a.stream() << "    " << c.name() << "& operator=(const " << c.name() << "&) = default;" << std::endl;
a.stream() << std::endl;
            /*
             * Manually generated default constructor.
             */
            if (c.requires_manual_default_constructor()) {
a.stream() << "public:" << std::endl;
a.stream() << "    " << c.name() << "();" << std::endl;
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
            if (c.is_parent()) {
a.stream() << "    virtual ~" << c.name() << "() noexcept = 0;" << std::endl;
a.stream() << std::endl;
            } else if (c.parents().size() != 0) {
a.stream() << "    virtual ~" << c.name() << "() noexcept { }" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated move constructor.
             */
            if (c.requires_manual_move_constructor()) {
a.stream() << "public:" << std::endl;
a.stream() << "    " << c.name() << "(" << c.name() << "&& rhs);" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated complete constructor.
             */
            if (!a.is_complete_constructor_disabled() && !c.all_properties().empty()) {
a.stream() << "public:" << std::endl;
                const auto prop_count(c.all_properties().size());
                if (prop_count == 1) {
                    const auto p(*c.all_properties().begin());
a.stream() << "    explicit " << c.name() << "(const " << p.type().complete_name() << a.make_by_ref_text(p) << " " << p.name() << ");" << std::endl;
                } else {
a.stream() << "    " << c.name() << "(" << std::endl;
                    dogen::formatters::sequence_formatter sf(prop_count);
                    sf.postfix_configuration().last(");");
                    for (const auto& p : c.all_properties()) {
a.stream() << "        const " << p.type().complete_name() << a.make_by_ref_text(p) << " " << p.name() << sf.postfix() << std::endl;
                        sf.next();
                    }
                }
a.stream() << std::endl;
            }

            /*
             * Friends
             */
            if (a.is_serialization_enabled()) {
a.stream() << "private:" << std::endl;
a.stream() << "    template<typename Archive>" << std::endl;
a.stream() << "    friend void boost::serialization::save(Archive& ar, const " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "    template<typename Archive>" << std::endl;
a.stream() << "    friend void boost::serialization::load(Archive& ar, " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Visitation.
             */
            if (c.is_visitable()) {
a.stream() << "public:" << std::endl;
a.stream() << "    virtual void accept(const " << c.name() << "_visitor& v) const = 0;" << std::endl;
a.stream() << "    virtual void accept(" << c.name() << "_visitor& v) const = 0;" << std::endl;
a.stream() << "    virtual void accept(const " << c.name() << "_visitor& v) = 0;" << std::endl;
a.stream() << "    virtual void accept(" << c.name() << "_visitor& v) = 0;" << std::endl;
a.stream() << std::endl;
            } else if (c.is_root_parent_visitable() && !c.is_parent()) {
a.stream() << "public:" << std::endl;
a.stream() << "    using " << c.root_parent_name() << "::accept;" << std::endl;
a.stream() << std::endl;
a.stream() << "    virtual void accept(const " << c.root_parent_name() << "_visitor& v) const override {" << std::endl;
a.stream() << "        v.visit(*this);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    virtual void accept(" << c.root_parent_name() << "_visitor& v) const override {" << std::endl;
a.stream() << "        v.visit(*this);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    virtual void accept(const " << c.root_parent_name() << "_visitor& v) override {" << std::endl;
a.stream() << "        v.visit(*this);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    virtual void accept(" << c.root_parent_name() << "_visitor& v) override {" << std::endl;
a.stream() << "        v.visit(*this);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Streaming
             */
            if (a.is_io_enabled()) {
                if (c.is_parent()) {
a.stream() << "public:" << std::endl;
a.stream() << "    virtual void to_stream(std::ostream& s) const;" << std::endl;
a.stream() << std::endl;
                } else if (!c.parents().empty()) {
a.stream() << "public:" << std::endl;
a.stream() << "    void to_stream(std::ostream& s) const override;" << std::endl;
a.stream() << std::endl;
                }
            }

            /*
             * Getters and setters.
             */
            if (!c.properties().empty()) {
a.stream() << "public:" << std::endl;
                for (const auto p : c.properties()) {
                    a.comment_start_method_group(p.documentation(), !p.is_immutable());

                    if (p.type().is_primitive() || p.type().is_enumeration()) {
a.stream() << "    " << p.type().complete_name() << " " << p.name() << "() const;" << std::endl;
                        if (p.is_immutable()) {
a.stream() << std::endl;
                            continue;
                        }
a.stream() << "    " << a.make_setter_return_type(c.name(), p) << " " << p.name() << "(const " << p.type().complete_name() << a.make_by_ref_text(p) << " v);" << std::endl;
                    } else {
a.stream() << "    const " << p.type().complete_name() << "& " << p.name() << "() const;" << std::endl;
                        if (p.is_immutable()) {
a.stream() << std::endl;
                            continue;
                        }
a.stream() << "    " << p.type().complete_name() << a.make_by_ref_text(p) << " " << p.name() << "();" << std::endl;
a.stream() << "    " << a.make_setter_return_type(c.name(), p) << " " << p.name() << "(const " << p.type().complete_name() << a.make_by_ref_text(p) << " v);" << std::endl;
a.stream() << "    " << a.make_setter_return_type(c.name(), p) << " " << p.name() << "(const " << p.type().complete_name() << "&& v);" << std::endl;
                    }
                    a.comment_end_method_group(p.documentation(), !p.is_immutable());
a.stream() << std::endl;
                }
            }

            /*
             * Equality.
             *
             * Equality is only public in leaf classes - MEC++-33.
             */
            if (c.is_parent()) {
a.stream() << "protected:" << std::endl;
a.stream() << "    bool compare(const " << c.name() << "& rhs) const;" << std::endl;
            } else {
a.stream() << "public:" << std::endl;
a.stream() << "    bool operator==(const " << c.name() << "& rhs) const;" << std::endl;
a.stream() << "    bool operator!=(const " << c.name() << "& rhs) const {" << std::endl;
a.stream() << "        return !this->operator==(rhs);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
            }

            if (c.is_parent() || !c.parents().empty()) {
a.stream() << "public:" << std::endl;
                if (c.is_parent() && c.parents().empty()) {
a.stream() << "    virtual bool equals(const " << c.name() << "& other) const = 0;" << std::endl;
                } else if (c.is_parent()) {
a.stream() << "    virtual bool equals(const " << c.root_parent_name_qualified() << "& other) const = 0;" << std::endl;
                } else if (!c.parents().empty()) {
a.stream() << "    bool equals(const " << c.root_parent_name_qualified() << "& other) const override;" << std::endl;
                }
a.stream() << std::endl;
             }

            /*
             * Swap and assignment.
             *
             * Swap and assignment are only public in leaf classes - MEC++-33
             */
            if ((!c.all_properties().empty() || c.is_parent()) && !c.is_immutable()) {
                if (c.is_parent()) {
a.stream() << "protected:" << std::endl;
                } else {
a.stream() << "public:" << std::endl;
                }
a.stream() << "    void swap(" << c.name() << "& other) noexcept;" << std::endl;
                if (!c.is_parent() && !c.is_immutable()) {
a.stream() << "    " << c.name() << "& operator=(" << c.name() << " other);" << std::endl;
                }
a.stream() << std::endl;
            }

            /*
             * Member variables.
             */
            if (!c.properties().empty()) {
a.stream() << "private:" << std::endl;
                for (const auto& p : c.properties()) {
a.stream() << "    " << p.type().complete_name() << " " << a.make_member_variable_name(p) << ";" << std::endl;
                }
            }
a.stream() << "};" << std::endl;
a.stream() << std::endl;
            /*
             * Destructor implementation.
             */
            if (c.is_parent()) {
a.stream() << "inline " << c.name() << "::~" << c.name() << "() noexcept { }" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Global equality operator implementation.
             */
            if (c.is_parent()) {
a.stream() << "inline bool operator==(const " << c.name() << "& lhs, const " << c.name() << "& rhs) {" << std::endl;
a.stream() << "    return lhs.equals(rhs);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }
        }

        if (!c.all_properties().empty() && !c.is_parent() && !c.is_immutable()) {
a.stream() << std::endl;
a.stream() << "namespace std {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>" << std::endl;
a.stream() << "inline void swap(" << std::endl;
a.stream() << "    " << c.qualified_name() << "& lhs," << std::endl;
a.stream() << "    " << c.qualified_name() << "& rhs) {" << std::endl;
a.stream() << "    lhs.swap(rhs);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_file();
}
} } } } }

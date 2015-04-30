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
#include "dogen/cpp/types/formatters/types/class_header_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/formatting_assistant.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

dogen::formatters::file class_header_formatter_stitch(
    formatters::formatting_assistant& fa,
    const formattables::class_info& c) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        {
            auto snf(fa.make_scoped_namespace_formatter());

fa.stream() << std::endl;
fa.stream() << "class " << c.name() << " " << fa.make_final_keyword_text(c) << "{" << std::endl;
fa.stream() << "public:" << std::endl;
            /*
             * Compiler generated constructors and destructors.
             */
            if (!c.requires_manual_default_constructor())
fa.stream() << "    " << c.name() << "() = default;" << std::endl;
fa.stream() << "    " << c.name() << "(const " << c.name() << "&) = default;" << std::endl;
            if (!c.requires_manual_move_constructor())
fa.stream() << "    " << c.name() << "(" << c.name() << "&&) = default;" << std::endl;
            if (!c.is_parent() && c.parents().empty())
fa.stream() << "    ~" << c.name() << "() = default;" << std::endl;
            if (c.is_immutable())
fa.stream() << "    " << c.name() << "& operator=(const " << c.name() << "&) = delete;" << std::endl;
            if (c.all_properties().empty())
fa.stream() << "    " << c.name() << "& operator=(const " << c.name() << "&) = default;" << std::endl;
fa.stream() << std::endl;
            /*
             * Manually generated constructors and destructors.
             */
            if (c.requires_manual_default_constructor()) {
fa.stream() << "public:" << std::endl;
fa.stream() << "    " << c.name() << "();" << std::endl;
fa.stream() << std::endl;
            }
            if (c.requires_manual_move_constructor()) {
fa.stream() << "public:" << std::endl;
fa.stream() << "    " << c.name() << "(" << c.name() << "&& rhs);" << std::endl;
fa.stream() << std::endl;
            }

            if (!c.disable_complete_constructor()) {
fa.stream() << "public:" << std::endl;
                const auto prop_count(c.all_properties().size());
                if (prop_count == 1) {
                    const auto p(*c.all_properties().begin());
fa.stream() << "    explicit " << c.name() << "(" << p.type().complete_name() << fa.make_by_ref_text(p) << " " << p.name() << ");" << std::endl;
                } else {
fa.stream() << "    " << c.name() << "(" << std::endl;
                    int pos(0);
                    for (const auto& p : c.all_properties()) {
fa.stream() << "        const " << p.type().complete_name() << fa.make_by_ref_text(p) << " " << p.name() << fa.make_parameter_separator_text(prop_count, pos) << std::endl;
                    ++pos;
                    }
                }
fa.stream() << std::endl;
            }

            /*
             * Friends
             */
            if (fa.is_serialization_enabled()) {
fa.stream() << "private:" << std::endl;
fa.stream() << "    template<typename Archive>" << std::endl;
fa.stream() << "    friend void boost::serialization::save(Archive& ar, const " << c.name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
fa.stream() << "    template<typename Archive>" << std::endl;
fa.stream() << "    friend void boost::serialization::load(Archive& ar, " << c.name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
            }

            /*
             * Visitation.
             */
            if (c.is_visitable()) {
fa.stream() << "public:" << std::endl;
fa.stream() << "    virtual void accept(const " << c.name() << "_visitor& v) const = 0;" << std::endl;
fa.stream() << "    virtual void accept(" << c.name() << "_visitor& v) const = 0;" << std::endl;
fa.stream() << "    virtual void accept(const " << c.name() << "_visitor& v) = 0;" << std::endl;
fa.stream() << "    virtual void accept(" << c.name() << "_visitor& v) = 0;" << std::endl;
fa.stream() << std::endl;
            } else if (c.is_original_parent_visitable() && !c.is_parent()) {
fa.stream() << "public:" << std::endl;
fa.stream() << "    virtual void accept(const " << c.original_parent_name() << "_visitor& v) const override {" << std::endl;
fa.stream() << "        v.visit(*this);" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << std::endl;
fa.stream() << "    virtual void accept(" << c.original_parent_name() << "_visitor& v) const override {" << std::endl;
fa.stream() << "        v.visit(*this);" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << std::endl;
fa.stream() << "    virtual void accept(const " << c.original_parent_name() << "_visitor& v) override {" << std::endl;
fa.stream() << "        v.visit(*this);" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << std::endl;
fa.stream() << "    virtual void accept(" << c.original_parent_name() << "_visitor& v) override {" << std::endl;
fa.stream() << "        v.visit(*this);" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << std::endl;
            }

            /*
             * Streaming
             */
            if (fa.is_io_enabled()) {
                if (c.is_parent()) {
fa.stream() << "public:" << std::endl;
fa.stream() << "    virtual void to_stream(std::ostream& s) const;" << std::endl;
fa.stream() << std::endl;
                } else if (!c.parents().empty()) {
fa.stream() << "    void to_stream(std::ostream& s) const override;" << std::endl;
fa.stream() << std::endl;
                }
            }

            /*
             * Getters and setters.
             */
            if (!c.properties().empty()) {
fa.stream() << "public:" << std::endl;
                for (const auto p : c.properties()) {
                    if (p.type().is_primitive() || p.type().is_enumeration()) {
fa.stream() << "    " << p.type().complete_name() << " " << p.name() << "() const;" << std::endl;
                        if (p.is_immutable())
                            continue;

fa.stream() << "    " << fa.make_setter_return_type(c.name(), p) << " " << p.name() << "(const " << p.type().complete_name() << fa.make_by_ref_text(p) << " v);" << std::endl;
                    } else {
fa.stream() << "    const " << p.type().complete_name() << "& " << p.name() << "() const;" << std::endl;
                        if (p.is_immutable())
                            continue;

fa.stream() << "    " << p.type().complete_name() << "& " << p.name() << "() const;" << std::endl;
fa.stream() << "    " << fa.make_setter_return_type(c.name(), p) << " " << p.name() << "(const " << p.type().complete_name() << fa.make_by_ref_text(p) << " v);" << std::endl;
fa.stream() << "    " << fa.make_setter_return_type(c.name(), p) << " " << p.name() << "(const " << p.type().complete_name() << "&& v);" << std::endl;
                    }
fa.stream() << std::endl;
                }
            }

            /*
             * Equality.
             *
             * Equality is only public in leaf classes - MEC++-33.
             */
            if (c.is_parent()) {
fa.stream() << "protected:" << std::endl;
fa.stream() << "    bool compare(const " << c.name() << "& rhs) const;" << std::endl;
            } else {
fa.stream() << "public:" << std::endl;
fa.stream() << "    bool operator==(const " << c.name() << "& rhs) const;" << std::endl;
fa.stream() << "    bool operator!=(const " << c.name() << "& rhs) const {" << std::endl;
fa.stream() << "        return !this->operator==(rhs);" << std::endl;
fa.stream() << "    }" << std::endl;
            }

            if (c.is_parent() && c.parents().empty()) {
fa.stream() << "    virtual bool equals(const " << c.name() << "& other) const = 0;" << std::endl;
            } else if (c.is_parent()) {
fa.stream() << "    virtual bool equals(const " << c.original_parent_name_qualified() << "& other) const = 0;" << std::endl;
            } else if (!c.parents().empty()) {
fa.stream() << "    bool equals(const " << c.original_parent_name_qualified() << "& other) const override;" << std::endl;
            }
fa.stream() << std::endl;
            /*
             * Swap and assignment.
             *
             * Swap and assignment are only public in leaf classes - MEC++-33
             */
            if (!c.all_properties().empty() && !c.is_immutable()) {
                if (c.is_parent()) {
fa.stream() << "protected:" << std::endl;
                } else {
fa.stream() << "public:" << std::endl;
                }
fa.stream() << "    void swap(" << c.name() << "& other) noexcept;" << std::endl;
                if (!c.is_parent()) {
fa.stream() << "    " << c.name() << "& operator=(" << c.name() << " other);" << std::endl;
                }
            }
fa.stream() << std::endl;
            /*
             * Member variables.
             */
            if (!c.properties().empty()) {
fa.stream() << "private:" << std::endl;
                for (const auto& p : c.properties()) {
fa.stream() << "    " << p.type().complete_name() << " " << fa.make_member_variable_name(p) << ";" << std::endl;
                }
            }
fa.stream() << "};" << std::endl;
fa.stream() << std::endl;
            if (c.is_parent()) {
fa.stream() << "inline " << c.name() << "::~" << c.name() << "() noexcept { }" << std::endl;
fa.stream() << std::endl;
            }

            if (fa.is_io_enabled() && fa.is_io_integrated()) {
fa.stream() << "    std::ostream& operator<<(std::ostream& s, const " << c.name() << "& v);" << std::endl;
fa.stream() << std::endl;
            }

            if (!c.is_parent()) {
fa.stream() << "inline bool operator==(const " << c.name() << "& lhs, const " << c.name() << "& rhs) {" << std::endl;
fa.stream() << "    return lhs.equals(rhs);" << std::endl;
fa.stream() << "}" << std::endl;
            }
        } // snf
    } // sbf
fa.stream() << std::endl;
    return fa.make_file();
}

} } } }

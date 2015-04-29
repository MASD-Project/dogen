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
#include "dogen/cpp/types/formatters/serialization/traits.hpp"

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

            using formatters::serialization::traits;
            const auto disable_serialization(
                !fa.is_formatter_enabled(traits::class_header_formatter_name()));
            if (!disable_serialization) {
fa.stream() << "private:" << std::endl;
fa.stream() << "    template<typename Archive>" << std::endl;
fa.stream() << "    friend void boost::serialization::save(Archive& ar, const " << c.name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
fa.stream() << "    template<typename Archive>" << std::endl;
fa.stream() << "    friend void boost::serialization::load(Archive& ar, " << c.name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
            }
fa.stream() << std::endl;
fa.stream() << "};" << std::endl;
fa.stream() << std::endl;
        }
    }
fa.stream() << std::endl;
    return fa.make_file();
}

} } } }

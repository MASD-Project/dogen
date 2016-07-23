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
#include "dogen/quilt.cpp/types/formatters/test_data/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

dogen::formatters::file class_implementation_formatter_stitch(
    assistant& a, const properties::class_info& c) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        if (!c.properties().empty()) {
a.stream() << "namespace {" << std::endl;
        a.add_helper_methods();
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        }

        {
            auto snf(a.make_scoped_namespace_formatter(c.namespaces()));


            /*
             * Default constructor.
             */
            if (!c.is_parent()) {
a.stream() << std::endl;
a.stream() << c.name() << "_generator::" << c.name() << "_generator() : position_(0) { }" << std::endl;
            }

            /*
             * Populate method.
             */
            if (!c.is_immutable()) {
                bool no_args(c.properties().empty() && c.parents().empty());
                if (no_args) {
a.stream() << std::endl;
a.stream() << "void " << c.name() << "_generator::" << std::endl;
a.stream() << "populate(const unsigned int /*position*/, result_type& /*v*/) {" << std::endl;
                } else {
a.stream() << std::endl;
a.stream() << "void " << c.name() << "_generator::" << std::endl;
a.stream() << "populate(const unsigned int position, result_type& v) {" << std::endl;
                }

                for (const auto p : c.parents()) {
a.stream() << "    " << p.qualified_name() << "_generator::populate(position, v);" << std::endl;
                }
                unsigned int i(0);
                for (const auto p : c.properties()) {
a.stream() << "    v." << p.name() << "(create_" << p.type().complete_identifiable_name() << "(position + " << i << "));" << std::endl;
                    ++i;
                }
a.stream() << "}" << std::endl;
            }

            /*
             * Create method.
             */
            if (!c.is_parent()) {
                 const bool no_arg(c.all_properties().empty());
a.stream() << std::endl;
a.stream() << c.name() << "_generator::result_type" << std::endl;
a.stream() << c.name() << "_generator::create(const unsigned int" << (no_arg ? "/*position*/" : " position") << ") {" << std::endl;
                if (c.is_immutable()) {
a.stream() << "    return " << c.name() << "(" << std::endl;
                    // FIXME: hack
                    if (c.properties().empty())
a.stream() << std::endl;
                    else {
                        dogen::formatters::sequence_formatter sf(c.properties().size());
                        for (const auto p : c.properties()) {
a.stream() << "        create_" << p.type().complete_identifiable_name() << "(position + " << sf.current_position() << ")" << sf.postfix() << std::endl;
                            sf.next();
                        }
                    }
a.stream() << "        );" << std::endl;
                } else {
a.stream() << "    " << c.name() << " r;" << std::endl;
                    if (!c.all_properties().empty())
a.stream() << "    " << c.name() << "_generator::populate(position, r);" << std::endl;
a.stream() << "    return r;" << std::endl;
                }
a.stream() << "}" << std::endl;
            }

            /*
             * Create method ptr.
             */
a.stream() << std::endl;
a.stream() << c.name() << "_generator::result_type*" << std::endl;
a.stream() << c.name() << "_generator::create_ptr(const unsigned int position) {" << std::endl;
            if (c.leaves().empty()) {
                if (c.is_immutable())
a.stream() << "    return new " << c.name() << "(create(position));" << std::endl;
                else {
a.stream() << "    " << c.name() << "* p = new " << c.name() << "();" << std::endl;
a.stream() << "    " << c.name() << "_generator::populate(position, *p);" << std::endl;
a.stream() << "    return p;" << std::endl;
                }
            } else {
                auto leaves(c.leaves());
                const auto front(leaves.front());
                leaves.pop_front();
                unsigned int i(0);
                unsigned int total(leaves.size());
                for (const auto l : leaves) {
a.stream() << "    if ((position % " << total << ") == " << i++ << ")" << std::endl;
a.stream() << "        return " << l << "_generator::create_ptr(position);" << std::endl;
                }
a.stream() << "    return " << front << "_generator::create_ptr(position);" << std::endl;
            }
a.stream() << "}" << std::endl;
            /*
             * Function operator
             */
             if (!c.is_parent()) {
a.stream() << std::endl;
a.stream() << c.name() << "_generator::result_type" << std::endl;
a.stream() << c.name() << "_generator::operator()() {" << std::endl;
a.stream() << "    return create(position_++);" << std::endl;
a.stream() << "}" << std::endl;
            }
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_file();
}
} } } } }

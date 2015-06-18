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
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace test_data {

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
            if (!c.is_parent()) {
fa.stream() << c.name() << "_generator::" << c.name() << "_generator() : position_(0) { }" << std::endl;
            }

            /*
             * Populate method.
             */
            if (!c.is_immutable()) {
                bool no_args(c.properties().empty() && c.parents().empty());
                if (no_args)
fa.stream() << "void " << c.name() << "_generator populate(const unsigned int /*position*/, result_type& /*v*/) {" << std::endl;
                else
fa.stream() << "void " << c.name() << "_generator populate(const unsigned int position, result_type& v) {" << std::endl;
                for (const auto p : c.parents()) {
fa.stream() << "    " << p.qualified_name() << "_generator::populate(position, v);" << std::endl;
                }
                unsigned int i(0);
                for (const auto p : c.properties()) {
fa.stream() << "    v." << p.name() << "(create_" << p.type().complete_identifiable_name() << "(position + " << i << "));" << std::endl;
                    ++i;
                }
fa.stream() << "}" << std::endl;
            }

            /*
             * Create method.
             */
            if (c.is_parent()) {
                 const bool no_arg(c.all_properties().empty());
fa.stream() << c.name() << "_generator::result_type" << std::endl;
fa.stream() << c.name() << "::create(const unsigned int" << (no_arg ? "/*position*/" : " position") << ") {" << std::endl;
                if (c.is_immutable()) {
fa.stream() << "    return " << c.name() << "(" << std::endl;
                    unsigned int i(0);
                    for (const auto p : c.properties()) {
fa.stream() << "        create_" << p.type().complete_identifiable_name() << "(position + " << i << ")" << std::endl;
                    }
fa.stream() << "        );" << std::endl;
                } else {
fa.stream() << "    " << c.name() << " r;" << std::endl;
                    if (!c.all_properties().empty())
fa.stream() << "    " << c.name() << "::populate(position, r);" << std::endl;
fa.stream() << "    return r;" << std::endl;
                }
fa.stream() << "}" << std::endl;
            }

            /*
             * Create method ptr.
             */
fa.stream() << c.name() << "_generator::result_type*" << std::endl;
fa.stream() << c.name() << "::create_ptr(const unsigned int position) {" << std::endl;
            if (c.leaves().empty()) {
                if (c.is_immutable())
fa.stream() << "    return new " << c.name() << "(create(position));" << std::endl;
                else {
fa.stream() << "    " << c.name() << "* p = new " << c.name() << "();" << std::endl;
fa.stream() << "    " << c.name() << "_generator::populate(position, *p);" << std::endl;
fa.stream() << "    return p;  " << std::endl;
                }
            } else {
                auto leaves(c.leaves());
                const auto front(leaves.front());
                leaves.pop_front();
                unsigned int i(0);
                unsigned int total(leaves.size());
                for (const auto l : leaves) {
fa.stream() << "    if ((position % " << total << ") == " << i++ << ")" << std::endl;
fa.stream() << "        return " << l << "_generator::create_ptr(position);" << std::endl;
                }
fa.stream() << "    return " << front << "_generator::create_ptr(position);" << std::endl;
            }

            /*
             * Function operator
             */
             if (!c.is_parent()) {
fa.stream() << c.name() << "_generator::result_type" << std::endl;
fa.stream() << "::operator()() {" << std::endl;
fa.stream() << "    return create(position_++);" << std::endl;
fa.stream() << "}" << std::endl;
            }
        } // snf
    } // sbf
    // return fa.make_file();
    return fa.make_file(false/*overwrite*/);
}
} } } }

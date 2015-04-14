/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <sstream>
#include "dogen/stitch/test/mock_text_template_factory.hpp"

namespace {

const std::string single_line_text("This is a template");
const std::string line_text("This is line numnber: ");
const std::string first_part_of_mixed_line("Start mixed line.");
const std::string scriptlet_in_mixed_line("my_variable.print()");
const std::string second_part_of_mixed_line("End mixed line.");

const std::string single_line_scriptlet("unsigned int i(0);");
const std::string scriptlet_line("unsigned int i");

}

namespace dogen {
namespace stitch {
namespace test {

mixed_content_block mock_text_template_factory::
make_text_only_mixed_content_block(
    const unsigned int how_many) const {
    std::ostringstream ss;
    mixed_content_block r;
    for(unsigned int i = 0; i != how_many; ++i) {
        ss << line_text << i;
        r.content().push_back(ss.str());
        ss.str("");
    }
    return r;
}

mixed_content_block mock_text_template_factory::
make_mixed_content_only_mixed_content_block(
    const unsigned int how_many) const {

    std::ostringstream ss;
    mixed_content_block r;
    for(unsigned int i = 0; i != how_many; ++i) {
        segment s0;
        s0.content(first_part_of_mixed_line);
        s0.type(segment_types::text);

        mixed_content_line l;
        l.segments().push_back(s0);

        segment s1;
        s1.content(scriptlet_in_mixed_line);
        s1.type(segment_types::scriptlet);
        l.segments().push_back(s1);

        segment s2;
        s2.content(second_part_of_mixed_line);
        s2.type(segment_types::text);
        l.segments().push_back(s2);

        r.content().push_back(l);
    }
    return r;
}

scriptlet_block mock_text_template_factory::
make_scriptlet_block(const unsigned int how_many) const {
    scriptlet_block r;
    std::ostringstream ss;
    for(unsigned int i = 0; i != how_many; ++i) {
        ss << scriptlet_line << i << ";";
        r.content().push_back(ss.str());
        ss.str("");
    }
    return r;
}

text_template mock_text_template_factory::make_empty_template() const {
    text_template r;
    return r;
}

text_template mock_text_template_factory::make_single_text_line() const {
    text_template r;
    r.content().push_back(make_text_only_mixed_content_block());
    return r;
}

text_template mock_text_template_factory::make_multiple_text_lines(
    const unsigned int how_many) const {
    text_template r;
    r.content().push_back(make_text_only_mixed_content_block(how_many));
    return r;
}

text_template mock_text_template_factory::
make_single_line_scriptlet_block() const {
    text_template r;
    r.content().push_back(make_scriptlet_block());
    return r;
}

text_template mock_text_template_factory::
make_multi_line_scriptlet_block(const unsigned int how_many) const {
    text_template r;
    r.content().push_back(make_scriptlet_block(how_many));
    return r;
}

text_template mock_text_template_factory::
make_text_scriptlet_text_single_line() const {
    text_template r;
    r.content().push_back(make_text_only_mixed_content_block());
    r.content().push_back(make_scriptlet_block());
    r.content().push_back(make_text_only_mixed_content_block());
    return r;
}

text_template mock_text_template_factory::
make_scriptlet_text_scriptlet_single_line() const {
    text_template r;
    r.content().push_back(make_scriptlet_block());
    r.content().push_back(make_text_only_mixed_content_block());
    r.content().push_back(make_scriptlet_block());
    return r;
}

text_template mock_text_template_factory::
make_text_scriptlet_text_multi_line(const unsigned int how_many) const {
    text_template r;
    r.content().push_back(make_text_only_mixed_content_block(how_many));
    r.content().push_back(make_scriptlet_block(how_many));
    r.content().push_back(make_text_only_mixed_content_block(how_many));
    return r;
}

text_template mock_text_template_factory::
make_scriptlet_text_scriptlet_multi_line(const unsigned int how_many) const {
    text_template r;
    r.content().push_back(make_scriptlet_block(how_many));
    r.content().push_back(make_text_only_mixed_content_block(how_many));
    r.content().push_back(make_scriptlet_block(how_many));
    return r;
}

text_template mock_text_template_factory::
make_mixed_content_single_line() const {
    text_template r;
    r.content().push_back(make_mixed_content_only_mixed_content_block());
    return r;
}

text_template mock_text_template_factory::
make_mixed_content_multi_line(const unsigned int how_many) const {
    text_template r;
    r.content().push_back(
        make_mixed_content_only_mixed_content_block(how_many));
    return r;
}

text_template mock_text_template_factory::make_complex_structure() const {
    text_template r;
    r.content().push_back(make_text_only_mixed_content_block(3));
    r.content().push_back(make_scriptlet_block(4));
    r.content().push_back(make_mixed_content_only_mixed_content_block(2));
    r.content().push_back(make_scriptlet_block());
    r.content().push_back(make_text_only_mixed_content_block());
    return r;
}

} } }

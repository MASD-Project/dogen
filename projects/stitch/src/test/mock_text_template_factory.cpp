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
#include "dogen/formatters/test/mock_general_settings_factory.hpp"
#include "dogen/stitch/test/mock_text_template_factory.hpp"

namespace {

const std::string stream_variable_name("stream_");
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

text_template mock_text_template_factory::
make_text_template_with_trivial_settings() const {
    stitching_settings s;
    s.stream_variable_name(stream_variable_name);

    text_template r;
    r.settings().stitching_settings(s);
    return r;
}

std::list<line> mock_text_template_factory::
make_text_only_lines(const unsigned int how_many) const {
    std::ostringstream ss;
    std::list<line> r;
    for(unsigned int i = 0; i != how_many; ++i) {
        segment sg;
        sg.type(segment_types::text);

        ss << line_text << i;
        sg.content(ss.str());
        ss.str("");

        line l;
        l.segments().push_back(sg);
        r.push_back(l);
    }
    return r;
}

std::list<line> mock_text_template_factory::
make_mixed_content_lines(const unsigned int how_many) const {
    std::ostringstream ss;
    std::list<line> r;
    for(unsigned int i = 0; i != how_many; ++i) {
        segment s0;
        s0.type(segment_types::text);
        s0.content(first_part_of_mixed_line);

        line l;
        l.segments().push_back(s0);

        segment s1;
        s1.content(scriptlet_in_mixed_line);
        s1.type(segment_types::scriptlet);
        l.segments().push_back(s1);

        segment s2;
        s2.content(second_part_of_mixed_line);
        s2.type(segment_types::text);
        l.segments().push_back(s2);

        r.push_back(l);
    }
    return r;
}

std::list<line> mock_text_template_factory::
make_scriptlet_only_lines(const unsigned int how_many) const {
    std::ostringstream ss;
    std::list<line> r;
    for(unsigned int i = 0; i != how_many; ++i) {
        segment sg;
        sg.type(segment_types::scriptlet);

        ss << scriptlet_line << i << ";";
        sg.content(ss.str());
        ss.str("");

        line l;
        l.segments().push_back(sg);
        r.push_back(l);
    }
    return r;
}

text_template mock_text_template_factory::make_empty_template() const {
    text_template r(make_text_template_with_trivial_settings());
    return r;
}

text_template mock_text_template_factory::make_single_text_line() const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_text_only_lines());
    return r;
}

text_template mock_text_template_factory::make_multiple_text_lines(
    const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_text_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_single_scriptlet_line() const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_scriptlet_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_multiple_scriptlet_lines(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_scriptlet_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_text_scriptlet_text_single_line() const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_text_only_lines());
    r.lines().splice(r.lines().end(), make_scriptlet_only_lines());
    r.lines().splice(r.lines().end(), make_text_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_scriptlet_text_scriptlet_single_line() const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_scriptlet_only_lines());
    r.lines().splice(r.lines().end(), make_text_only_lines());
    r.lines().splice(r.lines().end(), make_scriptlet_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_text_scriptlet_text_multi_line(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_text_only_lines(how_many));
    r.lines().splice(r.lines().end(), make_scriptlet_only_lines(how_many));
    r.lines().splice(r.lines().end(), make_text_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_scriptlet_text_scriptlet_multi_line(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_scriptlet_only_lines(how_many));
    r.lines().splice(r.lines().end(), make_text_only_lines(how_many));
    r.lines().splice(r.lines().end(), make_scriptlet_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_mixed_content_single_line() const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_mixed_content_lines());
    return r;
}

text_template mock_text_template_factory::
make_mixed_content_multi_line(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_mixed_content_lines(how_many));
    return r;
}

text_template mock_text_template_factory::make_complex_structure() const {
    text_template r(make_text_template_with_trivial_settings());
    r.lines(make_text_only_lines(3));
    r.lines().splice(r.lines().end(), make_scriptlet_only_lines(4));
    r.lines().splice(r.lines().end(), make_mixed_content_lines(2));
    r.lines().splice(r.lines().end(), make_scriptlet_only_lines());
    r.lines().splice(r.lines().end(), make_text_only_lines());
    return r;
}

text_template mock_text_template_factory::make_with_general_settings() const {
    dogen::formatters::test::mock_general_settings_factory factory_;
    const auto gs(factory_.make_general_settings());

    text_template r(make_text_template_with_trivial_settings());
    r.settings().general_settings(gs);
    r.lines(make_text_only_lines());
    return r;
}

text_template
mock_text_template_factory::make_with_containing_namespace() const {
    text_template r(make_text_template_with_trivial_settings());
    auto& cn(r.settings().stitching_settings().containing_namespaces());
    cn.push_back("first");
    cn.push_back("second");
    r.lines(make_text_only_lines());
    return r;
}

} } }

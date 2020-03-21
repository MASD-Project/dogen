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
#include <sstream>
#include "dogen.templating/test/mock_text_template_factory.hpp"

namespace {

const std::string empty;
const std::string stream_variable_name("stream_");
const std::string single_line_text("This is a template");
const std::string line_text("This is line numnber: ");
const std::string text_with_quotes("\"double quote\" \\\"double "
    "quote quote\\\" 'single'");
const std::string first_text_block_in_mixed_line("Start mixed line.");
const std::string expression_block_in_mixed_line("my_variable.print()");
const std::string second_text_block_in_mixed_line("End mixed line.");
const std::string expression_block("some_function()");
const std::string standard_control_block("unsigned int i");

const std::string decoration_preamble_key(
    "masd.decoration.preamble");
const std::string decoration_postamble_key(
    "masd.decoration.postamble");
const auto external_keys = std::unordered_map<std::string, std::string> {
    { decoration_preamble_key, empty },
    { decoration_postamble_key, empty }
};

const std::string decoration_preamble(R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
)");

}

namespace dogen::templating::test {

using namespace stitch;

text_template mock_text_template_factory::
make_text_template_with_trivial_properties() const {
    properties sp;
    sp.stream_variable_name(stream_variable_name);

    text_template r;
    r.properties(sp);
    r.supplied_kvps(external_keys);
    return r;
}

std::list<line> mock_text_template_factory:: make_text_block_only_lines(
    const unsigned int how_many, const bool empty_content) const {
    std::ostringstream ss;
    std::list<line> r;
    for(unsigned int i = 0; i != how_many; ++i) {
        block b;
        b.type(block_types::text_block);

        if (empty_content)
            b.content(empty);
        else {
            ss << line_text << i;
            b.content(ss.str());
            ss.str("");
        }

        line l;
        l.blocks().push_back(b);
        r.push_back(l);
    }
    return r;
}

std::list<line> mock_text_template_factory::
make_mixed_content_lines(const unsigned int how_many) const {
    std::ostringstream ss;
    std::list<line> r;
    for(unsigned int i = 0; i != how_many; ++i) {
        block b0;
        b0.type(block_types::text_block);
        b0.content(first_text_block_in_mixed_line);

        line l;
        l.blocks().push_back(b0);

        block b1;
        b1.content(expression_block_in_mixed_line);
        b1.type(block_types::expression_block);
        l.blocks().push_back(b1);

        block b2;
        b2.content(second_text_block_in_mixed_line);
        b2.type(block_types::text_block);
        l.blocks().push_back(b2);

        r.push_back(l);
    }
    return r;
}

std::list<line> mock_text_template_factory::
make_standard_control_block_only_lines(const unsigned int how_many) const {
    std::ostringstream ss;
    std::list<line> r;
    for(unsigned int i = 0; i != how_many; ++i) {
        block b;
        b.type(block_types::standard_control_block);

        ss << standard_control_block << i << ";";
        b.content(ss.str());
        ss.str("");

        line l;
        l.blocks().push_back(b);
        r.push_back(l);
    }
    return r;
}

std::list<line> mock_text_template_factory::
make_expression_block_only_lines(const unsigned int how_many) const {
    std::ostringstream ss;
    std::list<line> r;
    for(unsigned int i = 0; i != how_many; ++i) {
        block b;
        b.type(block_types::expression_block);

        ss << expression_block;
        if (how_many > 1)
            ss << " + i" << i;
        b.content(ss.str());
        ss.str("");

        line l;
        l.blocks().push_back(b);
        r.push_back(l);
    }
    return r;
}

std::list<line>
mock_text_template_factory::make_variable_block(const std::string& v) const {
    block b;
    b.type(block_types::variable_block);
    b.content(v);
    const line l(std::list<block> { b });
    const std::list<line> r({ l });
    return r;
}

text_template mock_text_template_factory::make_empty_template() const {
    text_template r(make_text_template_with_trivial_properties());
    return r;
}

text_template mock_text_template_factory::make_single_text_block_line() const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_text_block_only_lines());
    return r;
}

text_template mock_text_template_factory::make_multiple_text_block_lines(
    const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_text_block_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_single_expression_block_line() const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_expression_block_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_multiple_expression_block_lines(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_expression_block_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_single_standard_control_block_line() const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_standard_control_block_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_multiple_standard_control_block_lines(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_standard_control_block_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_text_expression_text_single_line() const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_text_block_only_lines());
    auto& l(r.body().lines());
    l.splice(l.end(), make_expression_block_only_lines());
    l.splice(l.end(), make_text_block_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_expression_text_expression_single_line() const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_expression_block_only_lines());
    auto& l(r.body().lines());
    l.splice(l.end(), make_text_block_only_lines());
    l.splice(l.end(), make_expression_block_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_text_expression_text_multi_line(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_text_block_only_lines(how_many));
    auto& l(r.body().lines());
    l.splice(l.end(), make_expression_block_only_lines(how_many));
    l.splice(l.end(), make_text_block_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_expression_text_expression_multi_line(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_expression_block_only_lines(how_many));
    auto& l(r.body().lines());
    l.splice(l.end(), make_text_block_only_lines(how_many));
    l.splice(l.end(), make_expression_block_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_text_standard_control_text_single_line() const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_text_block_only_lines());
    auto& l(r.body().lines());
    l.splice(l.end(), make_standard_control_block_only_lines());
    l.splice(l.end(), make_text_block_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_standard_control_text_standard_control_single_line() const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_standard_control_block_only_lines());
    auto& l(r.body().lines());
    l.splice(l.end(), make_text_block_only_lines());
    l.splice(l.end(), make_standard_control_block_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_text_standard_control_text_multi_line(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_text_block_only_lines(how_many));
    auto& l(r.body().lines());
    l.splice(l.end(), make_standard_control_block_only_lines(how_many));
    l.splice(l.end(), make_text_block_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_standard_control_text_standard_control_multi_line(
    const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_standard_control_block_only_lines(how_many));
    auto& l(r.body().lines());
    l.splice(l.end(), make_text_block_only_lines(how_many));
    l.splice(l.end(), make_standard_control_block_only_lines(how_many));
    return r;
}

text_template mock_text_template_factory::
make_mixed_content_single_line() const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_mixed_content_lines());
    return r;
}

text_template mock_text_template_factory::
make_mixed_content_multi_line(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_mixed_content_lines(how_many));
    return r;
}

text_template mock_text_template_factory::make_text_line_with_quotes() const {
    text_template r(make_text_template_with_trivial_properties());

    block b;
    b.type(block_types::text_block);
    b.content(text_with_quotes);

    line l;
    l.blocks().push_back(b);
    r.body().lines().push_back(l);

    return r;
}

text_template mock_text_template_factory::make_complex_structure() const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_text_block_only_lines(3));
    auto& l(r.body().lines());
    l.splice(l.end(), make_standard_control_block_only_lines(4));
    l.splice(l.end(), make_mixed_content_lines(2));
    l.splice(l.end(), make_standard_control_block_only_lines());
    l.splice(l.end(), make_text_block_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_with_decoration_properties() const {
    text_template r(make_text_template_with_trivial_properties());

    const auto external_keys = std::unordered_map<std::string, std::string> {
        { decoration_preamble_key, decoration_preamble },
        { decoration_postamble_key, empty }
    };
    r.supplied_kvps(external_keys);
    r.body().lines(make_text_block_only_lines());
    return r;
}

text_template
mock_text_template_factory::make_with_containing_namespace() const {
    text_template r(make_text_template_with_trivial_properties());
    auto& cn(r.properties().containing_namespaces());
    cn.push_back("first");
    cn.push_back("second");
    r.body().lines(make_text_block_only_lines());
    return r;
}

text_template mock_text_template_factory::
make_empty_text_lines(const unsigned int how_many) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_text_block_only_lines(how_many, true/*empty_content*/));
    return r;
}

text_template
mock_text_template_factory::make_with_variable(const std::string& n) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_variable_block(n));
    return r;
}

text_template mock_text_template_factory::
make_with_variable(const std::string& k, const std::string& v) const {
    text_template r(make_text_template_with_trivial_properties());
    r.body().lines(make_variable_block(k));
    r.supplied_kvps()[k] = v;
    return r;
}

}

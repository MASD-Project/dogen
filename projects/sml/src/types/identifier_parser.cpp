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
#include <iostream>
#include <functional>
#include <boost/tokenizer.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include "dogen/sml/types/parsing_error.hpp"
#include "dogen/sml/types/identifier_parser.hpp"
#include "dogen/sml/types/nested_qualified_name_builder.hpp"

namespace {

const char* delimiter = "::";
const std::string error_msg("Failed to parse string: ");
using namespace boost::spirit;

using dogen::sml::nested_qualified_name_builder;

template<typename Iterator>
struct grammar : qi::grammar<Iterator> {
    std::shared_ptr<nested_qualified_name_builder> builder;
    qi::rule<Iterator, std::string()> nested_name, name, nondigit, alphanum,
        primitive, signable_primitive;
    qi::rule<Iterator> identifier, scope_operator, type_name, template_id,
        templated_name, template_argument_list, template_argument;

    std::function<void()> start_template_, next_type_argument_, end_template_;
    std::function<void(const std::string&)> add_nested_name_, add_primitive_;

    void add_nested_name(const std::string& s) {
        builder->add_name(s);
    }

    void add_primitive(const std::string& s) {
        builder->add_primitive(s);
    }

    void start_template() {
        builder->start_children();
    }

    void next_type_argument() {
        builder->next_child();
    }

    void end_template() {
        builder->end_children();
    }

    void setup_functors() {
        add_nested_name_ = std::bind(&grammar::add_nested_name, this,
            std::placeholders::_1);
        add_primitive_ = std::bind(&grammar::add_primitive, this,
            std::placeholders::_1);
        start_template_ = std::bind(&grammar::start_template, this);
        next_type_argument_ = std::bind(&grammar::next_type_argument, this);
        end_template_ = std::bind(&grammar::end_template, this);
    }

    grammar(std::shared_ptr<nested_qualified_name_builder> b)
        : grammar::base_type(type_name), builder(b) {
        setup_functors();
        using qi::on_error;
        using qi::fail;
        using boost::spirit::qi::labels::_val;
        using boost::spirit::qi::_1;
        using boost::spirit::ascii::string;

        using boost::phoenix::val;
        using boost::phoenix::at_c;
        using boost::phoenix::push_back;
        using boost::phoenix::construct;

        alphanum = boost::spirit::qi::alnum | string("_");
        nondigit = boost::spirit::qi::alpha | string("_");
        name %= lexeme[nondigit >> *(alphanum)];
        scope_operator = "::";
        nested_name = name[add_nested_name_]
            >> *(scope_operator >> name[add_nested_name_]);
        signable_primitive =
            -(string("unsigned") >> string(" ")) >>
            (
                string("short") | string("wchar_t") | string("char") |
                string("int") |
                (
                    string("long") >> -(string(" ") >> string("long"))));
        primitive =
            string("bool") |
            signable_primitive |
            string("float") | string("double") | string("void");
        type_name %= primitive[add_primitive_] |
            (nested_name >> -(templated_name));

        templated_name = qi::lit("<")[start_template_]
            >> template_argument_list >> qi::lit(">")[end_template_];
        template_argument_list %= type_name
            >> *(qi::lit(",")[next_type_argument_] >> type_name);

        on_error<fail>
            (
                type_name,
                std::cout << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
                );
    }
};

}

namespace dogen {
namespace sml {

identifier_parser::
identifier_parser(const std::unordered_set<std::string>& packages,
    const std::list<std::string>& external_package_path,
    const std::string model_name)
    : packages_(packages), external_package_path_(external_package_path),
      model_name_(model_name) { }

nested_qualified_name identifier_parser::
parse_qualified_name(const std::string& n) {
    std::string::const_iterator it(n.begin());
    std::string::const_iterator end(n.end());

    std::shared_ptr<nested_qualified_name_builder>
        builder(new nested_qualified_name_builder(packages_,
                external_package_path_, model_name_));
    grammar<std::string::const_iterator> g(builder);
    const bool ok(boost::spirit::qi::parse(it, end, g));

    if (!ok || it != end)
        throw parsing_error(error_msg + n);

    return builder->build();
}

std::list<std::string>
identifier_parser::parse_scoped_name(const std::string& n) {
    const boost::char_separator<char> sep(delimiter);
    boost::tokenizer<boost::char_separator<char> > tokens(n, sep);

    std::list<std::string> r;
    boost::copy(tokens, std::inserter(r, r.end()));
    return r;
}

} }

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
#include <boost/tokenizer.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/spirit/include/qi.hpp>
#include "dogen/sml/domain/parsing_error.hpp"
#include "dogen/sml/utility/identifier_parser.hpp"

namespace {

const char* delimiter = "::";
const std::string error_msg("Failed to parse string: ");
using namespace boost::spirit;

/**
 * @brief
 *
 * EBNF:
 *
 * identifier = nondigit | identifier nondigit | identifier digit
 * nondigit = boost::spirit::qi::alpha | '_'
 * digit = boost::spirit::qi::digit
 * primitive = 'char' | 'wchar_t' | 'bool' | 'short' | 'int' | 'long'
 *    'signed' | 'unsigned' | 'float' | 'double' | 'void'
 * scope_resolution = '::'
 * cv_qualifier = 'const'
 * cv_qualifier_seq = cv_qualifier [ cv_qualifier_seq ]
 * ptr_operator = '*' [ cv_qualifier_seq ] | '&' | [ '::' ]
 * abstract_declarator = ptr_operator [ abstract_declarator ]
 *
 * nested_name_specifier = class_or_namespace_name '::' [nested_name_specifier]
 * class_or_namespace_name = class_name | namespace_name
 * class_name = identifier
 * namespace_name = identifier | template_id
 * template_id = template_name '<' [ template_argument_list ] '>'
 * template_argument_list = template_argument | template_argument_list ',' template_argument
 * template_argument = type_id | id_expression
 * type_id = type_specifier_seq [ abstract_declarator ]
 * type_specifier_seq = type_specifier | type_specifier_seq
 * type_specifier = simple_type_specifier | cv_qualifier
 * simple_type_specifier =
 *
 * [ '::' ] [ nested_name_specifier ] type_name
 * [ '::' ] nested_name_specifier 'template' template_id
 * primitive
 *
 * type_name = class_name
 * nested_name_specifier '*' [ cv_qualifier_seq ]

 *
 */
template<typename Iterator>
struct grammar : qi::grammar<Iterator> {
    qi::rule<Iterator> digit, nondigit, identifier, name,
        scope_operator, nested_name, unsigned_keyword, signable_primitive,
        primitive, type_name, template_id, templated_name,
        template_argument_list, template_argument;

    grammar() : grammar::base_type(type_name) {
        digit = boost::spirit::qi::digit;
        nondigit = boost::spirit::qi::alpha | "_";
        name = nondigit >> *(nondigit | digit);
        scope_operator = "::";
        nested_name = name >> *(scope_operator >> name);
        signable_primitive =
            -(qi::lit("unsigned") >> qi::lit(" ")) >>
            (
                qi::lit("short") | "wchar_t" | "char" | "int" |
                (
                    qi::lit("long") >> -(qi::lit(" ") >> qi::lit("long"))));
        primitive =
            qi::lit("bool") |
            signable_primitive |
            "float" | "double" |
            "void";
        type_name = primitive | (nested_name >> -(templated_name));

        templated_name = "<" >> template_argument_list >> ">";
        template_argument_list = nested_name >> *("," >> nested_name);

        // template_argument_list = template_argument |
        //     (template_argument_list >> "," >> template_argument);
        // template_argument = nested_name;

        // cv_qualifier = "const";
        // cv_qualifier_seq = cv_qualifier -(cv_qualifier_seq);
        // ptr_operator = qi::lit("*") -(cv_qualifier_seq) | "&"
        //     | -(scope_resolution);
        // abstract_declarator = ptr_operator -(abstract_declarator);
    }
};

}

namespace dogen {
namespace sml {
namespace utility {

identifier_parser::
identifier_parser(const std::unordered_set<std::string>& packages,
    const std::list<std::string>& external_package_path,
    const std::string model_name)
    : packages_(packages), external_package_path_(external_package_path),
      model_name_(model_name) { }

std::list<qualified_name>identifier_parser::
parse_qualified_name(const std::string& n) {
    std::string::const_iterator it(n.begin());
    std::string::const_iterator end(n.end());

    grammar<std::string::const_iterator> g;
    const bool ok(boost::spirit::qi::parse(it, end, g));

    if (!ok || it != end)
        throw parsing_error(error_msg + n);

    std::list<qualified_name> r;

    qualified_name main_type;
    if (n.find(delimiter) == std::string::npos) {
        main_type.type_name(n);
        r.push_back(main_type);
        return r;
    }

    const boost::char_separator<char> sep(delimiter);
    boost::tokenizer<boost::char_separator<char> > tokens(n, sep);

    std::list<std::string> token_list;
    std::copy(tokens.begin(), tokens.end(), std::back_inserter(token_list));

    const auto i(packages_.find(token_list.front()));
    if (i != packages_.end()) {
        main_type.model_name(model_name_);
    } else {
        main_type.model_name(token_list.front());
        token_list.pop_front();
    }

    main_type.type_name(token_list.back());
    token_list.pop_back();

    if (!token_list.empty())
        main_type.package_path(token_list);

    r.push_back(main_type);

    return r;
}

std::list<std::string>
identifier_parser::parse_scoped_name(const std::string& n) {
    const boost::char_separator<char> sep(delimiter);
    boost::tokenizer<boost::char_separator<char> > tokens(n, sep);

    std::list<std::string> r;
    boost::copy(tokens, std::inserter(r, r.end()));
    return r;
}

} } }

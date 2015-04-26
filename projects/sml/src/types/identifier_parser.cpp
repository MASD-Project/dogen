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
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <functional>
#include <boost/throw_exception.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/nested_qname_io.hpp"
#include "dogen/sml/types/parsing_error.hpp"
#include "dogen/sml/types/nested_qname_builder.hpp"
#include "dogen/sml/types/identifier_parser.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("sml.identifier_parser"));

const std::string error_msg("Failed to parse string: ");
using namespace boost::spirit;

using dogen::sml::nested_qname_builder;

namespace distinct {

namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
namespace repo = boost::spirit::repository;

namespace traits {

template <typename Tail>
struct distinct_spec
    : spirit::result_of::terminal<repo::tag::distinct(Tail)> {};

template <typename String>
struct char_spec
    : spirit::result_of::terminal<spirit::tag::ascii::char_(String)> {};

}

template <typename Tail>
inline typename traits::distinct_spec<Tail>::type
distinct_spec(Tail const& tail) { return repo::distinct(tail); }

template <typename String>
inline typename traits::char_spec<String>::type
char_spec(String const& str) { return ascii::char_(str); }

typedef traits::char_spec<std::string>::type charset_tag_type;
typedef traits::distinct_spec<charset_tag_type>::type keyword_tag_type;

const std::string keyword_spec("0-9a-zA-Z_");
const keyword_tag_type keyword = distinct_spec(char_spec(keyword_spec));

}

template<typename Iterator>
struct grammar : qi::grammar<Iterator> {
    std::shared_ptr<nested_qname_builder> builder;
    qi::rule<Iterator, std::string()> nested_name, name, nondigit, alphanum,
        primitive, signable_primitive;
    qi::rule<Iterator> identifier, scope_operator, type_name, template_id,
        templated_name, template_argument_list, template_argument;

    std::function<void()> start_template_, next_type_argument_, end_template_;
    std::function<void(const std::string&)> add_nested_name_, add_primitive_;

    void add_nested_name(const std::string& s) { builder->add_name(s); }
    void add_primitive(const std::string& s) { builder->add_primitive(s); }
    void start_template() { builder->start_children(); }
    void next_type_argument() { builder->next_child(); }
    void end_template() { builder->end_children(); }

    void setup_functors() {
        add_nested_name_ = std::bind(&grammar::add_nested_name, this,
            std::placeholders::_1);
        add_primitive_ = std::bind(&grammar::add_primitive, this,
            std::placeholders::_1);
        start_template_ = std::bind(&grammar::start_template, this);
        next_type_argument_ = std::bind(&grammar::next_type_argument, this);
        end_template_ = std::bind(&grammar::end_template, this);
    }

    grammar(std::shared_ptr<nested_qname_builder> b)
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
                distinct::keyword[string("short")] |
                distinct::keyword[string("wchar_t")] |
                distinct::keyword[string("char")] |
                distinct::keyword[string("int")] |
                (
                    string("long") >> -(string(" ") >> string("long"))));
        primitive =
            distinct::keyword[string("bool")] |
            signable_primitive |
            distinct::keyword[string("float")] |
            distinct::keyword[string("double")] |
            distinct::keyword[string("void")];
        type_name %= primitive[add_primitive_] |
            (nested_name >> -(templated_name));

        templated_name = qi::lit("<")[start_template_]
            >> template_argument_list >> qi::lit(">")[end_template_];
        template_argument_list %= type_name
            >> *(qi::lit(",")[next_type_argument_] >> *qi::space >> type_name);

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
identifier_parser(const std::unordered_set<std::string>& modules,
    const std::list<std::string>& external_module_path,
    const std::string model_name)
    : modules_(modules), external_module_path_(external_module_path),
      model_name_(model_name) { }

nested_qname identifier_parser::parse_qname(const std::string& n) const {
    std::string::const_iterator it(n.begin());
    std::string::const_iterator end(n.end());

    BOOST_LOG_SEV(lg, debug) << "parsing qname: " << n;

    std::shared_ptr<nested_qname_builder>
        builder(new nested_qname_builder(modules_,
                external_module_path_, model_name_));
    grammar<std::string::const_iterator> g(builder);
    const bool ok(boost::spirit::qi::parse(it, end, g));

    if (!ok || it != end) {
        BOOST_LOG_SEV(lg, error) << error_msg << n;
        BOOST_THROW_EXCEPTION(parsing_error(error_msg + n));
    }

    const auto r(builder->build());
    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    return r;
}

} }

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
#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_SPIRIT_DEBUG
#include <functional>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.logical/io/entities/name_tree_io.hpp"
#include "dogen.logical/types/helpers/parsing_error.hpp"
#include "dogen.logical/types/helpers/name_tree_builder.hpp"
#include "dogen.logical/types/helpers/legacy_name_tree_parser.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("logical.helpers.legacy_name_tree_parser"));

const std::string unsupported_technical_space(
    "Invalid or unsupported technical space: ");
const std::string error_msg("Failed to parse string: ");
using namespace boost::spirit;

using dogen::logical::helpers::name_tree_builder;

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

using dogen::identification::entities::technical_space;
using dogen::logical::helpers::parsing_error;

template<typename Iterator>
struct grammar : qi::grammar<Iterator> {
    boost::shared_ptr<name_tree_builder> builder;
    qi::rule<Iterator> match_signable_builtin;
    qi::rule<Iterator, std::string()> name_tree, name, nondigit, alphanum,
        builtin;
    qi::rule<Iterator> identifier, scope_operator, type_name, template_id,
        templated_name, template_argument_list, template_argument;

    std::function<void()> start_template_, next_type_argument_, end_template_;
    std::function<void(const std::string&)> add_name_tree_, add_builtin_;

    void add_name_tree(const std::string& s) { builder->add_name(s); }
    void add_builtin(const std::string& s) { builder->add_builtin(s); }
    void start_template() { builder->start_children(); }
    void next_type_argument() { builder->next_child(); }
    void end_template() { builder->end_children(); }

    void setup_functors() {
        add_name_tree_ = std::bind(&grammar::add_name_tree, this,
            std::placeholders::_1);
        add_builtin_ = std::bind(&grammar::add_builtin, this,
            std::placeholders::_1);
        start_template_ = std::bind(&grammar::start_template, this);
        next_type_argument_ = std::bind(&grammar::next_type_argument, this);
        end_template_ = std::bind(&grammar::end_template, this);
    }

    std::string scope_operator_for_technical_space(const technical_space ts) {
        switch (ts) {
        case technical_space::csharp: return ".";
        case technical_space::cpp:
        case technical_space::agnostic: return "::";
        default: {
            const auto s(boost::lexical_cast<std::string>(ts));
            BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
            BOOST_THROW_EXCEPTION(
                parsing_error(unsupported_technical_space + s));
        } }
    }

    grammar(boost::shared_ptr<name_tree_builder> b,
        const technical_space ts)
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
        scope_operator = scope_operator_for_technical_space(ts);

        name_tree = name[add_name_tree_]
            >> *(scope_operator >> name[add_name_tree_]);
        match_signable_builtin =
            -(distinct::keyword["unsigned"] >> ' ') >>
            (
                distinct::keyword["short"] |
                distinct::keyword["wchar_t"] |
                distinct::keyword["char"] |
                distinct::keyword["int"] |
                distinct::keyword["long"] >> -(' ' >> distinct::keyword["long"])
            );
        builtin = qi::raw [
            distinct::keyword["bool"] |
            match_signable_builtin |
            distinct::keyword["float"] |
            distinct::keyword["double"] |
            distinct::keyword["void"]
        ];
        type_name %= builtin[add_builtin_] |
            (name_tree >> -(templated_name));

        templated_name = qi::lit("<")[start_template_]
            >> template_argument_list >> qi::lit(">")[end_template_];
        template_argument_list %= type_name
            >> *(qi::lit(",")[next_type_argument_] >> *qi::space >> type_name);

        on_error<fail>
            (
                type_name,
                std::cout << val("Error! Expecting ")
                << _4                             // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2) // iterators to error-pos, end
                << val("\"")
                << std::endl
                );

        using qi::debug;
        BOOST_SPIRIT_DEBUG_NODE(name_tree);
        BOOST_SPIRIT_DEBUG_NODE(name);
        BOOST_SPIRIT_DEBUG_NODE(nondigit);
        BOOST_SPIRIT_DEBUG_NODE(alphanum);
        BOOST_SPIRIT_DEBUG_NODE(builtin);
        BOOST_SPIRIT_DEBUG_NODE(match_signable_builtin);
        BOOST_SPIRIT_DEBUG_NODE(identifier);
        BOOST_SPIRIT_DEBUG_NODE(scope_operator);
        BOOST_SPIRIT_DEBUG_NODE(type_name);
        BOOST_SPIRIT_DEBUG_NODE(template_id);
        BOOST_SPIRIT_DEBUG_NODE(templated_name);
        BOOST_SPIRIT_DEBUG_NODE(template_argument_list);
        BOOST_SPIRIT_DEBUG_NODE(template_argument);
    }
};

}

namespace dogen::logical::helpers {

legacy_name_tree_parser::
legacy_name_tree_parser(const identification::entities::technical_space ts)
    : technical_space_(ts) {}

entities::name_tree
legacy_name_tree_parser::parse(const std::string& s) const {
    BOOST_LOG_SEV(lg, debug) << "parsing name: " << s;

    auto builder(boost::make_shared<name_tree_builder>());
    grammar<std::string::const_iterator> g(builder, technical_space_);

    std::string::const_iterator i(s.begin());
    std::string::const_iterator end(s.end());
    const bool ok(boost::spirit::qi::parse(i, end, g));

    if (!ok || i != end) {
        BOOST_LOG_SEV(lg, error) << error_msg << s;
        BOOST_THROW_EXCEPTION(parsing_error(error_msg + s));
    }

    auto r(builder->build());
    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    return r;
}

}

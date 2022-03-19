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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_NEW_LOGICAL_NAME_TREE_PARSER_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_NEW_LOGICAL_NAME_TREE_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/stl.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/object.hpp>
#include <boost/phoenix/fusion.hpp>
#include <boost/phoenix/function.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.identification/io/entities/logical_name_tree_io.hpp"
#include "dogen.identification/types/helpers/parsing_error.hpp"
#include "dogen.identification/types/helpers/logical_name_tree_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg = logger_factory("identification.new_logical_name_tree_parser");

const std::string unsupported_technical_space(
    "Invalid or unsupported technical space: ");
const std::string error_msg("Failed to parse string: ");
using namespace boost::spirit;

using dogen::identification::helpers::logical_name_tree_builder;

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

template<typename NameTreeBuilder>
struct name_tree_listener
{
    bool is_const    = false;
    bool is_volatile = false;
    //NOTE: Might need mutable, too. and thread_local also exists.
    //this is optional, because `char`, `signed char` and `unsigned
    //char` are three types -> essentially a tristate bool.
    boost::optional<bool> sign;

    /*
        special values are "long", "long long", "short" and "int".
    */
    std::string type_name;

    struct cv_pointer
    {
        bool is_const;
        bool is_volatile;
    };

    std::vector<cv_pointer> pointers;
    bool is_reference = false;
    boost::optional<int> is_array;
    bool set_const()
    {
        bool & const_ = pointers.empty() ? is_const : pointers.back().is_const;
        if (const_)
            return false;
        else
        {
            const_ = true;
            return true;
        }
    }

    bool set_volatile()
    {
        bool & volatile_ = pointers.empty() ? is_volatile :
            pointers.back().is_volatile;
        if (volatile_)
            return false;
        else
        {
            volatile_ = true;
            return true;
        }
    }

    bool set_signed()
    {
        if (sign)
            return false;
        else
        {
            sign = true;
            return true;
        }
    }
    bool set_unsigned()
    {
        if (sign)
            return false;
        else
        {
            sign = false;
            return true;
        }
    }
    bool set_short()
    {
        if (type_name.empty() || (type_name == "int"))
        {
            type_name = "short";
            return true;
        }
        return false;
    }
    bool set_int()
    {
        //note: this does accept long int double --> I'll this in the parser
        if (type_name.empty())
        {
            type_name = "int";
            return true;
        }
        else if ((type_name == "long") || (type_name == "long long") ||
            (type_name == "short"))
            return true;
        else
            return false;
    }
    bool set_long()
    {
        if (type_name.empty() || (type_name == "int"))
            type_name = "long";
        else if (type_name == "long")
            type_name = "long long";
        else if (type_name == "double")
            type_name = "long double";
        else
            return false;
        return true;
    }

    bool set_double() //because "long double"
    {
        if (type_name.empty())
            type_name = "double";
        else if (type_name == "long")
            type_name = "long double";
        else
            return false;
        return true;
    }

    bool set_reference()
    {
        if (is_reference || !pointers.empty())
            return false;

        is_reference = true;
        return true;
    }
    bool set_name(const std::string & st)
    {
        if (type_name.empty())
        {
            type_name = st;
            return true;
        }
        else
            return false;
    }

    bool has_name()
    {
        return !type_name.empty();
    }

    void add_pointer()
    {
        pointers.push_back({false, false}); //can always be done because int &* is a reference to a pointer
    }

    bool set_array(int size)
    {
        if (is_array)
            return false;
        else
            is_array = size;
        return true;
    }

    NameTreeBuilder ntb;

    name_tree_listener() {}
    name_tree_listener(const std::unordered_set<std::string>& top_level_modules,
        const dogen::identification::entities::logical_location& model_location)
        : ntb(top_level_modules, model_location) {}

    void apply()
    {
        //your logic goes here, i.e. put it into the name_tree_build as ye wisheth
    }

    //in case you want to check a type is correct. NOTE: that could get the location too, but that would need more template stuff; but then you could add "#line foo.cpp 42"
    bool validate_typename(const std::string & ) { return true; }

};

//Type to be extended later on
template<typename Iterator, typename Skipper, typename NameTreeBuilder>
struct custom_type_grammar : qi::grammar<Iterator, Skipper>
{
    name_tree_listener<NameTreeBuilder> * listener;

    qi::rule<Iterator, std::string(), Skipper> scope;
    qi::rule<Iterator, std::string(), Skipper> id;
    qi::rule<Iterator, std::string(), Skipper> type_name;

    qi::rule<Iterator, Skipper> custom_type;

    std::function<void(const std::string & st, qi::unused_type, bool & pass)> make()
    {
        return [this](const std::string & st, qi::unused_type, bool & pass)
        {
            pass = listener->validate_typename(st);
            if (pass)
                listener->set_name(st);
        };
    }


    std::string scope_operator_for_technical_space(
        const dogen::identification::entities::technical_space ts) {
        switch (ts) {
        case dogen::identification::entities::technical_space::csharp:
            return ".";
        case dogen::identification::entities::technical_space::cpp:
            return "::";
        default: {
            const auto s(boost::lexical_cast<std::string>(ts));
            BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
            BOOST_THROW_EXCEPTION(
                dogen::identification::helpers::parsing_error(
                    unsupported_technical_space + s));
            return "";
        } }
    }

    static bool is_keyword(const std::string & input)
    {
        const static std::vector<const char*> keywords =
            {
                "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break",
                "case", "catch", "char", "char16_t", "char32_t", "class", "compl", "const", "constexpr",
                "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast",
                "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto",
                "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq",
                "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast",
                "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch",
                "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union",
                "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
            };
        return std::count_if(keywords.begin(), keywords.end(), [&](const char * st){return st == input;}) != 0;
    }

    std::string scope_str;
    custom_type_grammar(name_tree_listener<NameTreeBuilder> * listener,
        const dogen::identification::entities::technical_space ts)
          : custom_type_grammar::base_type(custom_type), listener(listener),
            scope_str(scope_operator_for_technical_space(ts))
    {
        namespace phoenix = boost::phoenix;
        scope = scope_str;
        id = qi::lexeme[(qi::char_("_A-Za-z") >> *qi::char_("_A-Za-z0-9"))];
        type_name = -qi::lit("::") >> ( id[qi::_val += qi::_1, qi::_pass = !phoenix::bind(&custom_type_grammar<Iterator, Skipper, NameTreeBuilder>::is_keyword, qi::_1)] % scope[qi::_val += qi::_1] ); //>> id[qi::_val += qi::_1] );

        custom_type = type_name[make()];
    }
};

template<typename Iterator, typename Skipper, typename NameTreeBuilder>
struct grammar : qi::grammar<Iterator, Skipper> {

    typedef name_tree_listener<NameTreeBuilder> listener_t;
    listener_t * listener;
    std::function<void(qi::unused_type, qi::unused_type, bool & pass)>
    make_attribute_setter(bool (listener_t::* ptr)())
    {
        return [this, ptr](qi::unused_type, qi::unused_type, bool & pass)
        {
            pass = (listener->*ptr)();
        };
    }

    std::function<void(qi::unused_type)>
    make_attribute_setter(void (listener_t::* ptr)())
    {
        return [this, ptr](qi::unused_type)
        {
            (listener->*ptr)();
        };
    }

    struct set_name_
    {
        listener_t * listener;
        const char *id;
        template<typename Context>
        void operator()(qi::unused_type, Context&, bool & pass) const
        {
            pass = listener->set_name(id);
        }
    };

    set_name_ set_name(const char* id)
    {
        return set_name_{ listener, id };
    }

    custom_type_grammar<Iterator, Skipper, NameTreeBuilder> custom_type;

    qi::rule<Iterator, Skipper> qualifier;
    qi::rule<Iterator, Skipper> builtin_simple;
    qi::rule<Iterator, Skipper> sign;
    qi::rule<Iterator, Skipper> lengthable;
    qi::rule<Iterator, Skipper> signable;
    qi::rule<Iterator, Skipper> long_double;
    qi::rule<Iterator, Skipper> multitoken;
    qi::rule<Iterator, Skipper> builtin;
    qi::rule<Iterator, Skipper> pointer;
    qi::rule<Iterator, Skipper> reference;
    qi::rule<Iterator, Skipper> array_;

    qi::rule<Iterator, Skipper> type;
    qi::rule<Iterator, Skipper> type_name;

    std::function<void()> start_template_, next_type_argument_, end_template_;
    std::function<void(const std::string&)> add_name_tree_, add_builtin_;

    void add_name_tree(/*const std::string& s*/) {} // builder->add_name(s);
    void add_builtin  (/*const std::string& s*/) {}// { builder->add_builtin(s); }
    void start_template() { } //builder->start_children();
    void next_type_argument() { } //builder->next_child(); }
    void end_template() { } //builder->end_children(); }

    void setup_functors() {/*
        add_name_tree_ = std::bind(&grammar::add_name_tree, this,
            std::placeholders::_1);
        add_builtin_ = std::bind(&grammar::add_builtin, this,
            std::placeholders::_1);
        start_template_ = std::bind(&grammar::start_template, this);
        next_type_argument_ = std::bind(&grammar::next_type_argument, this);
        end_template_ = std::bind(&grammar::end_template, this);*/
    }

    grammar(listener_t &l,
        const dogen::identification::entities::technical_space ts)
                : grammar::base_type(type_name), listener(&l),
                  custom_type{ &l , ts } {
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

        builtin_simple =
            distinct::keyword["bool"]    [set_name("bool")]     |
            distinct::keyword["float"]   [set_name("float")]    |
            distinct::keyword["void"]    [set_name("void")]     |
            distinct::keyword["char16_t"][set_name("char16_t")] |
            distinct::keyword["char32_t"][set_name("char32_t")]
            ;

        qualifier = distinct::keyword["const"]   [make_attribute_setter(&listener_t::set_const)] |
                    distinct::keyword["volatile"][make_attribute_setter(&listener_t::set_volatile)];

        long_double = -distinct::keyword["long"]  [make_attribute_setter(&listener_t::set_long)]   >> repeat(0,2)[qualifier] >>
                       distinct::keyword["double"][make_attribute_setter(&listener_t::set_double)] >> repeat(0,2)[qualifier] >>
                      -distinct::keyword["long"]  [make_attribute_setter(&listener_t::set_long)];

        sign = distinct::keyword["signed"]  [make_attribute_setter(&listener_t::set_signed)]
             | distinct::keyword["unsigned"][make_attribute_setter(&listener_t::set_unsigned)];


        lengthable
                   = distinct::keyword["int"]  [make_attribute_setter(&listener_t::set_int)]
                   | distinct::keyword["long"] [make_attribute_setter(&listener_t::set_long)]
                   | distinct::keyword["short"][make_attribute_setter(&listener_t::set_short)];

        signable = distinct::keyword["char"]   [set_name("char")] |
                   distinct::keyword["wchar_t"][set_name("wchar_t")];

        //now, invalid combinations except for the long double is handled by the listener, so I'll just throw everything together
        //note that this allows a plain "const", so that will be handled by the has_name function
        multitoken = +(sign  | lengthable | signable | qualifier) >> qi::eps[make_attribute_setter(&listener_t::has_name)];

        builtin = builtin_simple | multitoken | long_double;

        type = repeat(0,2)[qualifier] >> ( builtin | custom_type ) >> repeat(0,2)[qualifier] ;

        reference = qi::lit('&')[make_attribute_setter(&listener_t::set_reference)];

        pointer = qi::lit('*')[make_attribute_setter(&listener_t::add_pointer)] >> repeat(0,2)[qualifier];

        auto set_array = [this](int size) {listener->set_array(size);};
        array_ = '[' >> qi::int_[set_array] >> ']';

        type_name = type >> -reference >> *pointer >> -array_ >> qi::eps[make_attribute_setter(&listener_t::apply)];

        on_error<fail>
            (
                type_name,
                std::cout << val("Error! Expecting ")
                << boost::spirit::_4                             // what failed?
                << val(" here: \"")
                << construct<std::string>(boost::spirit::_3, boost::spirit::_2) // iterators to error-pos, end
                << val("\"")
                << std::endl
                );

        using qi::debug;
        BOOST_SPIRIT_DEBUG_NODE(builtin);
        BOOST_SPIRIT_DEBUG_NODE(type_name);
        BOOST_SPIRIT_DEBUG_NODE(qualifier);
        BOOST_SPIRIT_DEBUG_NODE(builtin_simple);
        BOOST_SPIRIT_DEBUG_NODE(sign);
        BOOST_SPIRIT_DEBUG_NODE(lengthable);
        BOOST_SPIRIT_DEBUG_NODE(signable);
        BOOST_SPIRIT_DEBUG_NODE(long_double);
        BOOST_SPIRIT_DEBUG_NODE(multitoken);
        BOOST_SPIRIT_DEBUG_NODE(builtin);
        BOOST_SPIRIT_DEBUG_NODE(type_name);
        BOOST_SPIRIT_DEBUG_NODE(pointer);
        BOOST_SPIRIT_DEBUG_NODE(reference);
        BOOST_SPIRIT_DEBUG_NODE(array_);
        BOOST_SPIRIT_DEBUG_NODE(type);

    }
};

}

#endif

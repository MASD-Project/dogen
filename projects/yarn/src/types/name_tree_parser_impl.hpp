
#include <functional>
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
#include <boost/optional.hpp>

#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/io/name_tree_io.hpp"
#include "dogen/yarn/types/parsing_error.hpp"
#include "dogen/yarn/types/name_tree_builder.hpp"

namespace {

using namespace dogen::utility::log;
static auto lg = logger_factory("yarn.name_tree_parser");

const static std::string unsupported_language = "Invalid or unsupported language: ";
const static std::string error_msg = "Failed to parse string: ";
using namespace boost::spirit;

using dogen::yarn::name_tree_builder;

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

const static std::string keyword_spec("0-9a-zA-Z_");
const static keyword_tag_type keyword = distinct_spec(char_spec(keyword_spec));

}

template<typename NameTreeBuilder>
struct name_tree_listener
{
    bool is_const    = false;
    bool is_volatile = false;
    //NOTE: Might need mutable, too. and thread_local also exists.
    //this is optional, because `char`, `signed char` and `unsigned char` are three types -> essentially a tristate bool.
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
        bool & volatile_ = pointers.empty() ? is_volatile : pointers.back().is_volatile;
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
        else if ((type_name == "long") || (type_name == "long long") || (type_name == "short"))
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
        const ::dogen::yarn::location& model_location) : ntb(top_level_modules, model_location) {}

    void apply()
    {
        //your logic goes here, i.e. put it into the name_tree_build as ye wisheth
    }

    //in case you want to check a type is correct. NOTE: that could get the location too, but that would need more template stuff; but then you could add "#line foo.cpp 42"
    bool validate_typename(const std::string & ) { return true; } 

};

//Type to be extended later on
template<typename Iterator, typename NameTreeBuilder>
struct custom_type_grammar : qi::grammar<Iterator>
{
    name_tree_listener<NameTreeBuilder> * listener;

    qi::rule<Iterator, std::string()> scope;
    qi::rule<Iterator, std::string()> id;
    qi::rule<Iterator, std::string()> type_name;


    qi::rule<Iterator> custom_type;

    std::function<void(const std::string & st, qi::unused_type, bool & pass)> make()
    {
        return [this](const std::string & st, qi::unused_type, bool & pass)
        {
            pass = listener->validate_typename(st);
            if (pass)
                listener->set_name(st);
        };
    }


    std::string scope_operator_for_language(const dogen::yarn::languages l) {
        switch (l) {
        case dogen::yarn::languages::csharp:  return ".";
        case dogen::yarn::languages::cpp:     return "::";
        case dogen::yarn::languages::upsilon: return "::";
        default: {
            const auto s(boost::lexical_cast<std::string>(l));
            BOOST_LOG_SEV(lg, error) << unsupported_language << s;
            BOOST_THROW_EXCEPTION(
                dogen::yarn::parsing_error(unsupported_language + s));
            return "";
        } }
    }
    std::string scope_str;
    custom_type_grammar(name_tree_listener<NameTreeBuilder> * listener, const dogen::yarn::languages l) 
          : custom_type_grammar::base_type(custom_type), listener(listener), scope_str(scope_operator_for_language(l))
    {
        scope = qi::string(scope_str);
        id = qi::char_("_A-Za-z") >> *qi::char_("_A-Za-z0-9");
        type_name = -qi::string("::") >> ( id % scope );

        custom_type = type_name[make()];
    }
};

template<typename Iterator, typename NameTreeBuilder>
struct grammar : qi::grammar<Iterator> {
    
    typedef name_tree_listener<NameTreeBuilder> listener_t;
    listener_t * listener;
    std::function<void(qi::unused_type, qi::unused_type, bool & pass)> make_attribute_setter(bool (listener_t::* ptr)())
    {
        return [&](qi::unused_type, qi::unused_type, bool & pass)
        {
            pass = !(listener->*ptr)();
        };
    }

    std::function<void(qi::unused_type)> make_attribute_setter(void (listener_t::* ptr)())
    {
        return [&](qi::unused_type)
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

    custom_type_grammar<Iterator, NameTreeBuilder> custom_type;

    qi::rule<Iterator> qualifier;
    qi::rule<Iterator> builtin_simple;
    qi::rule<Iterator> sign;
    qi::rule<Iterator> lengthable;
    qi::rule<Iterator> signable;
    qi::rule<Iterator> long_double; 
    qi::rule<Iterator> multitoken;
    qi::rule<Iterator> builtin;
    qi::rule<Iterator> pointer;
    qi::rule<Iterator> reference;
    qi::rule<Iterator> array_;

    qi::rule<Iterator> type;
    qi::rule<Iterator> type_name;

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
            const dogen::yarn::languages language)
                : grammar::base_type(type_name), listener(&l), custom_type{ listener , language} {
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
                << _4                             // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2) // iterators to error-pos, end
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
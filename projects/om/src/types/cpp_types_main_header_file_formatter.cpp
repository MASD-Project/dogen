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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/meta_data_reader.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/om/types/formatting_error.hpp"
#include "dogen/om/types/cpp_file_boilerplate_formatter.hpp"
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om.cpp_types_main_header_file_formatter"));

const std::string empty;
const std::string missing_context_ptr("Context pointer is null");
const std::string parent_not_found("Type is a child but parent not found");
const std::string multiple_inheritance_found(
    "Multiple inheritance is not supported");
const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);
const std::string scope_operator("::");

}

namespace dogen {
namespace om {

/**
 * @brief Provides a context in which formatting operations occur.
 *
 * All parameters passed in to the context must have a lifetime
 * greater than (or equal to) the context itself as it keeps
 * references to them.
 */
class cpp_types_main_header_file_formatter::context {
public:
    context() = delete;
    context(const context&) = delete;
    context(context&&) = delete;
    context& operator=(const context&) = delete;
    ~context() noexcept = default;

public:
    context(std::ostream& s, cpp_formatters::indenter& ind,
        cpp_formatters::utility& u) : stream_(s), indenter_(ind), utility_(u),
          first_line_is_blank_(false), overwrite_(false) { }

public:
    /**
     * @brief Stream to which the formatted output will be sent.
     */
    std::ostream& stream() { return stream_; }

    /**
     * @brief Indentation facilities.
     */
    cpp_formatters::indenter& indenter() { return indenter_; }

    /**
     * @brief Formatting utility methods.
     */
    cpp_formatters::utility& utility() { return utility_; }

    /**
     * @brief If true, add a blank line at the start.
     */
    /**@{*/
    bool first_line_is_blank() const { return first_line_is_blank_; }
    void first_line_is_blank(bool value) { first_line_is_blank_ = value; }
    /**@}*/

    /**
     * @brief If true, file will be overwritten regardless.
     */
    /**@{*/
    bool overwrite() const { return overwrite_; }
    void overwrite(bool value) { overwrite_ = value; }
    /**@}*/

private:
    std::ostream& stream_;
    cpp_formatters::indenter& indenter_;
    cpp_formatters::utility& utility_;
    bool first_line_is_blank_;
    bool overwrite_;
};

cpp_types_main_header_file_formatter::cpp_types_main_header_file_formatter()
    : doxygen_next_(
          !start_on_first_line,
          use_documentation_tool_markup,
          !documenting_previous_identifier,
          comment_styles::c_style,
          !last_line_is_blank),
      doxygen_previous_(
          start_on_first_line,
          use_documentation_tool_markup,
          documenting_previous_identifier,
          comment_styles::cpp_style,
          !last_line_is_blank) { }

std::list<std::string> cpp_types_main_header_file_formatter::
namespaces(const sml::qname& qn) const {
    std::list<std::string> r(qn.external_module_path());

    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    const auto mp(qn.module_path());
    r.insert(r.end(), mp.begin(), mp.end());

    return r;
}

std::string cpp_types_main_header_file_formatter::
cpp_qualified_name(const sml::qname& qn) const {
    std::ostringstream s;

    if (!qn.model_name().empty())
        s << qn.model_name() << scope_operator;

    bool is_first(false);
    for (const auto& p : qn.module_path()) {
        if (is_first)
            s << scope_operator;
        s << p;
    }

    s << qn.simple_name();
    return s.str();
}

void cpp_types_main_header_file_formatter::ensure_non_null_context() const {
    if (context_ != nullptr)
        return;

    BOOST_LOG_SEV(lg, error) << missing_context_ptr;
    BOOST_THROW_EXCEPTION(formatting_error(missing_context_ptr));
}

void cpp_types_main_header_file_formatter::
visit(const dogen::sml::enumeration& e) const {
    ensure_non_null_context();

    BOOST_LOG_SEV(lg, debug) << "Formatting enumeration: " << e.name();
    context_->overwrite(true);
    doxygen_next_.format(context_->stream(), e.documentation());
    context_->stream() << context_->indenter() << "enum class "
                      << e.name().simple_name() << " : unsigned int ";

    context_->utility().open_scope();
    {
        cpp_formatters::positive_indenter_scope pis(context_->indenter());
        bool is_first(true);
        std::ostringstream assignment;
        std::ostringstream comment;
        for (const auto& enumerator : e.enumerators()) {
            if (!is_first) {
                const auto c(comment.str());
                context_->stream() << assignment.str() << ",";
                if (!c.empty())
                    context_->stream() << " " << c;
                assignment.str(empty);
                comment.str(empty);
            }
            assignment << context_->indenter() << enumerator.name() << " = "
                       << enumerator.value();
            doxygen_previous_.format(comment, e.documentation());
            is_first = false;
        }

        context_->stream() << assignment.str();
        const auto c(comment.str());
        if (!c.empty())
            context_->stream() << " " << c;
    }
    context_->stream() << context_->indenter() << "};" << std::endl;
}

void cpp_types_main_header_file_formatter::
open_class(const sml::object& o) const {
    if (!o.documentation().empty())
        doxygen_next_.format(context_->stream(), o.documentation());

    context_->stream() << context_->indenter() << "class "
                      << o.name().simple_name();

    if (!o.is_parent())
        context_->stream() << " final";

    if (o.is_child()) {
        const auto i(o.relationships().find(sml::relationship_types::parents));
        if (i == o.relationships().end() || i->second.empty()) {
            BOOST_LOG_SEV(lg, error) << parent_not_found;
            BOOST_THROW_EXCEPTION(formatting_error(parent_not_found));
        }

        if (i->second.size() > 1) {
            BOOST_LOG_SEV(lg, error) << multiple_inheritance_found;
            BOOST_THROW_EXCEPTION(formatting_error(multiple_inheritance_found));
        }

        const std::string parent_simple_name(i->second.front().simple_name());
        context_->stream() << " :";
        context_->stream() << " public ";
        context_->stream() << parent_simple_name;
    }
    context_->stream() << " {" << std::endl;
    context_->first_line_is_blank(false);
}

void cpp_types_main_header_file_formatter::close_class() const {
    context_->stream() << context_->indenter() << "};" << std::endl;
}

void cpp_types_main_header_file_formatter::
explicitly_defaulted_functions(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_defaulted_functions))
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();

    const auto& sn(o.name().simple_name());
    if (reader.is_false(types::generate_explicit_default_constructor)) {
        context_->stream() << context_->indenter() << sn << "() = default;"
                          << std::endl;
    }

    context_->stream() << context_->indenter() << sn << "(const " << sn
                      << "&) = default;" << std::endl;

    if (reader.is_false(types::generate_explicit_move_constructor)) {
        context_->stream() << context_->indenter() << sn << "(" << sn
                          << "&&) = default;" << std::endl;
    }

    if (!o.is_parent() && !o.is_child()) {
        context_->stream() << context_->indenter() << "~" << sn
                          << "() = default;" << std::endl;
    }

    if (o.is_immutable()) {
        context_->stream() << context_->indenter() << sn
                          << "& operator=(const " << sn << "&) = delete;"
                          << std::endl;
    } else {
        const auto p(o.all_properties());
        if (p.empty()) {
            context_->stream() << context_->indenter() << sn
                              << "& operator=(const " << sn
                              << "&) = default;"
                              << std::endl;
        }
    }
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
default_constructor(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_explicit_default_constructor))
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    context_->stream() << context_->indenter()
                      << o.name().simple_name() << "();" << std::endl;
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
complete_constructor(const sml::object& o) const {
    {
        sml::meta_data_reader reader(o.meta_data());
        using types = sml::tags::cpp::types;
        if (reader.is_false(types::generate_complete_constructor))
            return;
    }

    const auto& props(o.all_properties());
    if (props.empty())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    if (props.size() == 1) {
        const auto p(*props.begin());
        sml::meta_data_reader reader(p.meta_data());
        using types = sml::tags::cpp::types;
        context_->stream() << context_->indenter() << "explicit "
                          << sn << "(const "
                          << reader.get(types::complete_name);

        if (reader.is_true(types::is_simple_type))
            context_->stream() << "&";

        context_->stream() << " " << p.name() << ");" << std::endl;
        context_->first_line_is_blank(true);
        return;
    }

    context_->stream() << context_->indenter() << sn << "(";
    {
        cpp_formatters::positive_indenter_scope s(context_->indenter());
        bool is_first(true);
        for (const auto p : props) {
            context_->stream() << (is_first ? "" : ",") << std::endl;

            sml::meta_data_reader reader(p.meta_data());
            using types = sml::tags::cpp::types;
            context_->stream() << context_->indenter() << "const "
                              << reader.get(types::complete_name);

            if (reader.is_true(types::is_simple_type))
                context_->stream() << "&";

            context_->stream() << " " << p.name();
            is_first = false;
        }
        context_->stream() << ");" << std::endl;
    }
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
move_constructor(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_explicit_move_constructor))
        return;

    const auto& props(o.all_properties());
    if (props.empty())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    context_->stream() << context_->indenter() << sn << "(" << sn
                      << "&& rhs);" << std::endl;
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
destructor(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_explicit_destructor))
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    if (o.is_parent()) {
        /*
         * according to MEC++, item 33, base classes should always be
         * abstract. this avoids all sorts of tricky problems with
         * assignment and swap.
         *
         * incidentally, this also fixes some strange clang errors:
         * undefined reference to `vtable.
         */
        context_->stream() << context_->indenter() << "virtual ~" << sn
                          << "() noexcept = 0;" << std::endl;
    } else if (o.is_parent()) {
        context_->stream() << context_->indenter() << "virtual ~" << sn
                          << "() noexcept { }" << std::endl;
    }
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
friends(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_friends))
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().private_access_specifier();
    const auto sn(o.name().simple_name());
    context_->stream() << context_->indenter()
                      << "template<typename Archive>" << std::endl
                      << context_->indenter()
                      << "friend void boost::serialization::save(Archive& ar"
                      << ", const " << sn << "& v, unsigned int version);"
                      << std::endl;
    context_->utility().blank_line();

    context_->stream() << context_->indenter() << "template<typename Archive>"
                      << std::endl
                      << context_->indenter()
                      << "friend void boost::serialization::load(Archive& ar"
                      << ", " << sn << "& v, unsigned int version);"
                      << std::endl;
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::simple_type_getter_and_setter(
    const std::string& owner_name, const sml::property& p) const {
    const auto doc(p.documentation());
    if (!doc.empty())
        doxygen_next_.format(context_->stream(), doc);

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_start_block(context_->stream(), doc);

    sml::meta_data_reader reader(p.meta_data());
    using types = sml::tags::cpp::types;
    const auto cn(reader.get(types::complete_name));
    context_->stream() << context_->indenter()
                      << cn << " " << p.name() << "() const;" << std::endl;

    if (!p.is_immutable()) {
        context_->stream() << context_->indenter();
        if (p.is_fluent())
            context_->stream() << owner_name << "& ";
        else
            context_->stream() << "void ";

        context_->stream() << p.name() << "(const " << cn;

        if (reader.is_true(types::is_simple_type))
            context_->stream() << "&";

        context_->stream() << " v);" << std::endl;
    }

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_end_block(context_->stream(), doc);
}

void cpp_types_main_header_file_formatter::compound_type_getter_and_setter(
    const std::string& owner_name, const sml::property& p) const {
    const auto doc(p.documentation());

    if (!doc.empty())
        doxygen_next_.format(context_->stream(), doc);

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_start_block(context_->stream(), doc);

    // const getter
    sml::meta_data_reader reader(p.meta_data());
    using types = sml::tags::cpp::types;
    const auto cn(reader.get(types::complete_name));
    context_->stream() << context_->indenter() << "const " << cn
                      << "& " << p.name() << "() const;" << std::endl;

    if (!p.is_immutable()) {
        // Popsicle immutability
        context_->stream() << context_->indenter() << "" << cn
                          << "& " << p.name() << "();" << std::endl;

        // traditional setter
        context_->stream() << context_->indenter();
        if (p.is_fluent())
            context_->stream() << owner_name << "& ";
        else
            context_->stream() << "void ";
        context_->stream() << p.name() << "(const " << cn;

        if (reader.is_true(types::is_simple_type))
            context_->stream() << "&";

        context_->stream() << " v);" << std::endl;

        // move setter
        context_->stream() << context_->indenter();
        if (p.is_fluent())
            context_->stream() << owner_name << "& ";
        else
            context_->stream() << "void ";
        context_->stream() << p.name() << "(const " << cn;

        if (reader.is_true(types::is_simple_type))
            context_->stream() << "&&";

        context_->stream() << " v);" << std::endl;
    }

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_end_block(context_->stream(), doc);
}

void cpp_types_main_header_file_formatter::
getters_and_setters(const sml::object& o) const {
    if (o.local_properties().empty())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    bool is_first(true);
    for (const auto p : o.local_properties()) {
        if (!is_first)
            context_->utility().blank_line();

        sml::meta_data_reader reader(p.meta_data());
        if (reader.is_true(sml::tags::cpp::types::is_simple_type))
            simple_type_getter_and_setter(o.name().simple_name(), p);
        else
            compound_type_getter_and_setter(o.name().simple_name(), p);
        is_first = false;
    }
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
member_variables(const sml::object& o) const {
    if (o.local_properties().empty())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    for (const auto p : o.local_properties()) {
        sml::meta_data_reader reader(p.meta_data());
        context_->stream() << context_->indenter()
                          << reader.get(sml::tags::cpp::types::complete_name)
                          << " "
                          << context_->utility().as_member_variable(p.name())
                          << ";"
                          << std::endl;
    }
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
equality(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_equality))
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    const auto sn(o.name().simple_name());
    if (o.is_parent()) {
        // equality is only public in leaf classes - MEC++-33
        context_->utility().protected_access_specifier();
        context_->stream() << context_->indenter() << "bool compare(const "
                          << sn << "& rhs) const;" << std::endl;
    } else {
        context_->utility().public_access_specifier();
        context_->stream() << context_->indenter() << "bool operator==(const "
                          << sn <<  "& rhs) const;" << std::endl;
        context_->stream() << context_->indenter() << "bool operator!=(const "
                          << sn << "& rhs) const ";
        context_->utility().open_scope();
        {
            cpp_formatters::positive_indenter_scope s(context_->indenter());
            context_->stream() << context_->indenter()
                              << "return !this->operator==(rhs);"
                              << std::endl;
        }
        context_->utility().close_scope();
    }

    if (!o.is_parent() && !o.is_child())
        return;

    context_->utility().blank_line();
    context_->utility().public_access_specifier();
    using types = sml::tags::cpp::types;
    if (o.is_parent() && !o.is_child()) {
        context_->stream() << context_->indenter()
                          << "virtual bool equals(const " << sn
                          <<  "& other) const = 0;"
                          << std::endl;
    } else if (o.is_parent()) {
        context_->stream() << context_->indenter()
                          << "virtual bool equals(const "
                          << reader.get(types::qualified_original_parent_name)
                          <<  "& other) const = 0;"
                          << std::endl;
    } else {
        context_->stream() << context_->indenter()
                          << "bool equals(const "
                          << reader.get(types::qualified_original_parent_name)
                          <<  "& other) const override;"
                          << std::endl;
    }
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
to_stream(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_to_stream))
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    if (o.is_parent()) {
        context_->stream() << context_->indenter()
                          << "virtual void to_stream("
                          << "std::ostream& s) const;"
                          << std::endl;
    } else {
        context_->stream() << context_->indenter()
                          << "void to_stream(std::ostream& s) "
                          << "const override;"
                          << std::endl;
    }
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
swap(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_swap))
        return;

    const auto props(o.all_properties());
    if ((props.empty() && !o.is_parent()) || o.is_immutable())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    // swap is only public in leaf classes - MEC++-33
    if (o.is_parent())
        context_->utility().protected_access_specifier();
    else
        context_->utility().public_access_specifier();

    const auto sn(o.name().simple_name());
    context_->stream() << context_->indenter() << "void swap("
                      << sn << "& other) noexcept;"
                      << std::endl;
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
assignment(const sml::object& o) const {
    // assignment is only available in leaf classes - MEC++-33
    const auto props(o.all_properties());
    if (props.empty() || o.is_parent() || o.is_immutable())
        return;

    const auto sn(o.name().simple_name());
    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    context_->stream() << context_->indenter() << sn << "& operator=("
                      << sn << " other);" << std::endl;
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
visitor_method(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_accept))
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    using types = sml::tags::cpp::types;
    const auto opn(reader.get(types::qualified_original_parent_name));

    if (o.is_visitable()) {
        context_->stream() << context_->indenter()
                          << "virtual void accept(const " << sn
                          << "_visitor& v) const = 0;" << std::endl;
        context_->stream() << context_->indenter() << "virtual void accept("
                          << sn << "_visitor& v) const = 0;" << std::endl;
        context_->stream() << context_->indenter()
                          << "virtual void accept(const " << sn
                          << "_visitor& v) = 0;" << std::endl;
        context_->stream() << context_->indenter() << "virtual void accept("
                          << sn << "_visitor& v) = 0;" << std::endl;
        context_->utility().blank_line();
        return;
    }

    context_->utility().public_access_specifier();
    context_->stream() << context_->indenter()
                      << "virtual void accept(const "
                      << opn << "_visitor& v) const override {"
                      << std::endl;

    {
        cpp_formatters::positive_indenter_scope s(context_->indenter());
        context_->stream() << context_->indenter() << "v.visit(*this);"
                          << std::endl;
    }
    context_->stream() << context_->indenter() << "}" << std::endl;
    context_->utility().blank_line();
    context_->stream() << context_->indenter() << "virtual void accept("
                      << opn << "_visitor& v) const override {"
                      << std::endl;

    {
        cpp_formatters::positive_indenter_scope s(context_->indenter());
        context_->stream() << context_->indenter() << "v.visit(*this);"
                          << std::endl;
    }
    context_->stream() << context_->indenter() << "}" << std::endl;
    context_->utility().blank_line();
    context_->stream() << context_->indenter()
                      << "virtual void accept(const "
                      << opn << "_visitor& v) override {" << std::endl;

    {
        cpp_formatters::positive_indenter_scope s(context_->indenter());
        context_->stream() << context_->indenter() << "v.visit(*this);"
                          << std::endl;
    }
    context_->stream() << context_->indenter() << "}" << std::endl;
    context_->utility().blank_line();
    context_->stream() << context_->indenter() << "virtual void accept("
                      << opn << "_visitor& v) override {" << std::endl;

    {
        cpp_formatters::positive_indenter_scope s(context_->indenter());
        context_->stream() << context_->indenter() << "v.visit(*this);"
                          << std::endl;
    }
    context_->stream() << context_->indenter() << "}" << std::endl;
    context_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
format(const sml::object& o) const {
    open_class(o);
    {
        cpp_formatters::positive_indenter_scope s(context_->indenter());
        explicitly_defaulted_functions(o);
        default_constructor(o);
        destructor(o);
        move_constructor(o);
        complete_constructor(o);
        friends(o);
        visitor_method(o);
        to_stream(o);
        getters_and_setters(o);
        equality(o);
        swap(o);
        assignment(o);
        member_variables(o);
    }
    close_class();
}

void cpp_types_main_header_file_formatter::
visit(const dogen::sml::object& f) const {
    ensure_non_null_context();
    context_->overwrite(false);
    format(f);
}

const std::string&
cpp_types_main_header_file_formatter::meta_data_path() const {
    return sml::tags::cpp::types::header_file::generate;
}

file cpp_types_main_header_file_formatter::
format(const sml::module& module, const annotation& a) const {

    std::ostringstream s;
    cpp_formatters::indenter ind;
    cpp_formatters::utility u(s, ind);

    const cpp_includes i = cpp_includes();
    sml::meta_data_reader reader(module.meta_data());
    const auto& fn(sml::tags::cpp::types::header_file::file_name);
    const boost::filesystem::path relative_file_path(reader.get(fn));
    const bool gp(reader.is_true(sml::tags::generate_preamble));

    cpp_file_boilerplate_formatter f(gp);
    f.format_begin(s, a, i, relative_file_path);
    const auto ns(namespaces(module.name()));

    if (!ns.empty()) {

        cpp_formatters::namespace_helper nsh(s, ns);
        u.blank_line();

        cpp_formatters::namespace_formatter nsf(s);
        doxygen_next_.format(s, module.documentation());
        nsf.format_start(module.name().simple_name());
        nsf.format_end();

        s << " ";
    } else {
        cpp_formatters::namespace_formatter nsf(s);
        doxygen_next_.format(s, module.documentation());
        nsf.format_start(module.name().simple_name());
        nsf.format_end();
    }
    u.blank_line();
    f.format_end(s, a, relative_file_path);

    file r;
    r.contents(s.str());
    r.overwrite(false);
    r.relative_path(relative_file_path);

    return r;
}

file cpp_types_main_header_file_formatter::
format(const sml::type& t, const annotation& a) const {

    std::ostringstream s;
    cpp_formatters::indenter ind;
    cpp_formatters::utility u(s, ind);
    context_ = std::shared_ptr<context>(new context(s, ind, u));

    const cpp_includes i = cpp_includes();
    sml::meta_data_reader reader(t.meta_data());
    const auto& fn(sml::tags::cpp::types::header_file::file_name);
    const boost::filesystem::path relative_file_path(reader.get(fn));
    const bool gp(reader.is_true(sml::tags::generate_preamble));
    cpp_file_boilerplate_formatter f(gp);
    f.format_begin(s, a, i, relative_file_path);
    {
        const auto ns(namespaces(t.name()));
        cpp_formatters::namespace_helper nsh(context_->stream(), ns);
        context_->utility().blank_line();
        t.accept(*this);
        context_->utility().blank_line();
    }
    context_->utility().blank_line();
    f.format_end(s, a, relative_file_path);

    file r;
    r.contents(s.str());
    r.overwrite(context_->overwrite());
    r.relative_path(relative_file_path);
    context_ = std::shared_ptr<context>();

    return r;
}

} }

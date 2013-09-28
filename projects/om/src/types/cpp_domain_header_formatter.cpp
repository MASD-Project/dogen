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
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/tag_adaptor.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/factory.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/repository.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/om/types/formatting_error.hpp"
#include "dogen/om/types/cpp_file_boilerplate_formatter.hpp"
#include "dogen/om/types/cpp_domain_header_formatter.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om_formatters.modeline_formatter"));

const std::string empty;
const std::string missing_stream_ptr("Stream pointer is null");
const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);
const std::string scope_operator("::");

}

namespace dogen {
namespace om {

cpp_domain_header_formatter::cpp_domain_header_formatter()
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

std::list<std::string> cpp_domain_header_formatter::
namespaces(const sml::qname& qn) const {
    std::list<std::string> r(qn.external_module_path());

    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    const auto mp(qn.module_path());
    r.insert(r.end(), mp.begin(), mp.end());

    return r;
}

std::string cpp_domain_header_formatter::
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

void cpp_domain_header_formatter::
visit(const dogen::sml::enumeration& e) const {
    if (context_ == nullptr) {
        BOOST_LOG_SEV(lg, error) << missing_stream_ptr;
        BOOST_THROW_EXCEPTION(formatting_error(missing_stream_ptr));
    }

    BOOST_LOG_SEV(lg, debug) << "Formatting enumeration: " << e.name();
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

void cpp_domain_header_formatter::
open_class(const sml::abstract_object& o) const {
    if (!o.documentation().empty())
        doxygen_next_.format(context_->stream(), o.documentation());

    context_->stream() << context_->indenter() << "class "
                      << o.name().simple_name();

    if (!o.is_parent())
        context_->stream() << " final";

    if (o.parent_name()) {
        context_->stream() << " :";

        context_->stream() << " public ";
        context_->stream() << o.parent_name()->simple_name();
    }
    context_->stream() << " {" << std::endl;
    context_->first_line_is_blank(false);
}

void cpp_domain_header_formatter::close_class() const {
    context_->stream() << context_->indenter() << "};" << std::endl;
}

void cpp_domain_header_formatter::
explicitly_defaulted_functions(const sml::abstract_object& o) const {
    auto adaptor(sml::make_tag_adaptor(o));
    if (!adaptor.generate_explicitly_defaulted_functions())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();

    const auto& sn(o.name().simple_name());
    if (!adaptor.requires_manual_default_constructor()) {
        context_->stream() << context_->indenter() << sn << "() = default;"
                          << std::endl;
    }

    context_->stream() << context_->indenter() << sn << "(const " << sn
                      << "&) = default;" << std::endl;

    if (!adaptor.requires_manual_move_constructor()) {
        context_->stream() << context_->indenter() << sn << "(" << sn
                          << "&&) = default;" << std::endl;
    }

    if (!o.is_parent() && !o.parent_name()) {
        context_->stream() << context_->indenter() << "~" << sn
                          << "() = default;" << std::endl;
    }

    if (o.is_immutable()) {
        context_->stream() << context_->indenter() << sn
                          << "& operator=(const " << sn << "&) = delete;"
                          << std::endl;
    } else {
        const auto p(context_->property_cache().get_all_properties(o));
        if (p.empty()) {
            context_->stream() << context_->indenter() << sn
                              << "& operator=(const " << sn
                              << "&) = default;"
                              << std::endl;
        }
    }
    context_->first_line_is_blank(true);
}

void cpp_domain_header_formatter::
default_constructor(const sml::abstract_object& o) const {
    auto adaptor(sml::make_tag_adaptor(o));
    if (!adaptor.requires_manual_default_constructor())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    context_->stream() << context_->indenter()
                      << o.name().simple_name() << "();" << std::endl;
    context_->first_line_is_blank(true);
}

void cpp_domain_header_formatter::
complete_constructor(const sml::abstract_object& o) const {
    {
        auto adaptor(sml::make_tag_adaptor(o));
        if (!adaptor.generate_complete_constructor())
            return;
    }

    const auto& props(context_->property_cache().get_all_properties(o));
    if (props.empty())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    if (props.size() == 1) {
        const auto p(*props.begin());
        auto adaptor(sml::make_tag_adaptor(p));
        context_->stream() << context_->indenter() << "explicit "
                          << sn << "(const "
                          << adaptor.complete_name();

        if (adaptor.is_simple_type())
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

            auto adaptor(sml::make_tag_adaptor(p));
            context_->stream() << context_->indenter() << "const "
                              << adaptor.complete_name();

            if (adaptor.is_simple_type())
                context_->stream() << "&";

            context_->stream() << " " << p.name();
            is_first = false;
        }
        context_->stream() << ");" << std::endl;
    }
    context_->first_line_is_blank(true);
}

void cpp_domain_header_formatter::
move_constructor(const sml::abstract_object& o) const {
    auto adaptor(sml::make_tag_adaptor(o));
    if (!adaptor.requires_manual_move_constructor())
        return;

    const auto& props(context_->property_cache().get_all_properties(o));
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

void cpp_domain_header_formatter::
destructor(const sml::abstract_object& o) const {
    if (!o.is_parent() && !o.parent_name())
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
    } else if (o.parent_name()) {
        context_->stream() << context_->indenter() << "virtual ~" << sn
                          << "() noexcept { }" << std::endl;
    }
    context_->first_line_is_blank(true);
}

void cpp_domain_header_formatter::
friends(const sml::abstract_object& o) const {
    auto adaptor(sml::make_tag_adaptor(o));
    if (!adaptor.is_boost_serialization_enabled())
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

void cpp_domain_header_formatter::simple_type_getter_and_setter(
    const std::string& owner_name, const sml::property& p) const {
    const auto doc(p.documentation());
    if (!doc.empty())
        doxygen_next_.format(context_->stream(), doc);

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_start_block(context_->stream(), doc);

    auto adaptor(sml::make_tag_adaptor(p));
    const auto cn(adaptor.complete_name());
    context_->stream() << context_->indenter()
                      << cn << " " << p.name() << "() const;" << std::endl;

    if (!p.is_immutable()) {
        context_->stream() << context_->indenter();
        if (p.is_fluent())
            context_->stream() << owner_name << "& ";
        else
            context_->stream() << "void ";

        context_->stream() << p.name() << "(const " << cn;

        if (!adaptor.is_simple_type())
            context_->stream() << "&";

        context_->stream() << " v);" << std::endl;
    }

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_end_block(context_->stream(), doc);
}

void cpp_domain_header_formatter::compound_type_getter_and_setter(
    const std::string& owner_name, const sml::property& p) const {
    const auto doc(p.documentation());

    if (!doc.empty())
        doxygen_next_.format(context_->stream(), doc);

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_start_block(context_->stream(), doc);

    // const getter
    auto adaptor(sml::make_tag_adaptor(p));
    const auto cn(adaptor.complete_name());
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

        if (!adaptor.is_simple_type())
            context_->stream() << "&";

        context_->stream() << " v);" << std::endl;

        // move setter
        context_->stream() << context_->indenter();
        if (p.is_fluent())
            context_->stream() << owner_name << "& ";
        else
            context_->stream() << "void ";
        context_->stream() << p.name() << "(const " << cn;

        if (!adaptor.is_simple_type())
            context_->stream() << "&&";

        context_->stream() << " v);" << std::endl;
    }

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_end_block(context_->stream(), doc);
}

void cpp_domain_header_formatter::
getters_and_setters(const sml::abstract_object& o) const {
    if (o.properties().empty())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    bool is_first(true);
    for (const auto p : o.properties()) {
        if (!is_first)
            context_->utility().blank_line();

        auto adaptor(sml::make_tag_adaptor(p));
        if (adaptor.is_simple_type())
            simple_type_getter_and_setter(o.name().simple_name(), p);
        else
            compound_type_getter_and_setter(o.name().simple_name(), p);
        is_first = false;
    }
    context_->first_line_is_blank(true);
}

void cpp_domain_header_formatter::
member_variables(const sml::abstract_object& o) const {
    if (o.properties().empty())
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    for (const auto p : o.properties()) {
        auto adaptor(sml::make_tag_adaptor(p));
        context_->stream() << context_->indenter()
                          << adaptor.complete_name() << " "
                          << context_->utility().as_member_variable(p.name())
                          << ";"
                          << std::endl;
    }
    context_->first_line_is_blank(true);
}

void cpp_domain_header_formatter::
equality(const sml::abstract_object& o) const {
    auto adaptor(sml::make_tag_adaptor(o));
    if (!adaptor.generate_equality())
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

    if (!o.is_parent() && !o.parent_name())
        return;

    context_->utility().blank_line();
    context_->utility().public_access_specifier();
    if (o.is_parent() && !o.parent_name()) {
        context_->stream() << context_->indenter()
                          << "virtual bool equals(const " << sn
                          <<  "& other) const = 0;"
                          << std::endl;
    } else if (o.is_parent()) {
        context_->stream() << context_->indenter()
                          << "virtual bool equals(const "
                          << adaptor.qualified_original_parent_name()
                          <<  "& other) const = 0;"
                          << std::endl;
    } else {
        context_->stream() << context_->indenter()
                          << "bool equals(const "
                          << adaptor.qualified_original_parent_name()
                          <<  "& other) const override;"
                          << std::endl;
    }
    context_->first_line_is_blank(true);
}

void cpp_domain_header_formatter::
to_stream(const sml::abstract_object& o) const {
    auto adaptor(sml::make_tag_adaptor(o));
    if (!adaptor.is_io_enabled())
        return;

    if (o.is_parent() && !o.parent_name())
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

void cpp_domain_header_formatter::
swap(const sml::abstract_object& o) const {
    auto adaptor(sml::make_tag_adaptor(o));
    if (!adaptor.generate_swap())
        return;

    const auto props(context_->property_cache().get_all_properties(o));
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

void cpp_domain_header_formatter::
assignment(const sml::abstract_object& o) const {
    // assignment is only available in leaf classes - MEC++-33
    const auto props(context_->property_cache().get_all_properties(o));
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

void cpp_domain_header_formatter::
visitor_method(const sml::abstract_object& o) const {
    auto adaptor(sml::make_tag_adaptor(o));
    if (!o.is_visitable() &&
        !(adaptor.is_original_parent_visitable() && !o.is_parent()))
        return;

    if (context_->first_line_is_blank())
        context_->utility().blank_line();

    context_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    const auto opn(adaptor.original_parent_name());

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

void cpp_domain_header_formatter::format(const sml::abstract_object& o) const {
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

void cpp_domain_header_formatter::
visit(const dogen::sml::service& s) const {
    format(s);
}

void cpp_domain_header_formatter::
visit(const dogen::sml::factory& f) const {
    format(f);
}

void cpp_domain_header_formatter::
visit(const dogen::sml::repository& r) const {
    format(r);
}

void cpp_domain_header_formatter::
visit(const dogen::sml::value_object& vo) const {
    format(vo);
}

void cpp_domain_header_formatter::
visit(const dogen::sml::keyed_entity& ke) const {
    format(ke);
}

void cpp_domain_header_formatter::
visit(const dogen::sml::entity& e) const {
    format(e);
}

void cpp_domain_header_formatter::
format(std::ostream& s, const sml::type& t, const licence& l,
    const modeline& m, const std::string& marker,
    const sml::property_cache_interface& c) const {

    cpp_formatters::indenter ind;
    cpp_formatters::utility u(s, ind);
    context_ = std::unique_ptr<context>(new context(s, c, ind, u));

    const cpp_includes i = cpp_includes();
    const boost::filesystem::path relative_file_path;
    auto adaptor(sml::make_tag_adaptor(t));
    cpp_file_boilerplate_formatter f(adaptor.generate_preamble());
    {
        const auto ns(namespaces(t.name()));
        cpp_formatters::namespace_helper nsh(context_->stream(), ns);
        context_->utility().blank_line();
        f.format_begin(s, l, m, marker, i, relative_file_path);
        t.accept(*this);
        context_->utility().blank_line();
    }
    context_->utility().blank_line();
    f.format_end(s, m, relative_file_path);
    context_ = std::unique_ptr<context>();
}

} }

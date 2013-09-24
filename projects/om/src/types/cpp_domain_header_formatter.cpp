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
}

void cpp_domain_header_formatter::close_class() const {
    context_->stream() << context_->indenter() << "};" << std::endl;
}

void cpp_domain_header_formatter::
compiler_generated_constuctors(const sml::abstract_object& /*o*/) const {
    // context_->utility().public_access_specifier();

    // const auto sn(o.name().simple_name());
    // if (!ci.requires_manual_default_constructor())
    //     context_->stream() << context_->indenter() << sn << "() = default;"
    //                       << std::endl;

    // context_->stream() << context_->indenter() << sn << "(const " << sn
    //                   << "&) = default;" << std::endl;

    // if (!ci.requires_manual_move_constructor()) {
    //     context_->stream() << context_->indenter() << sn << "(" << sn
    //                       << "&&) = default;" << std::endl;
    // }

    // if (!o.is_parent() && o.parent_name()) {
    //     context_->stream() << context_->indenter() << "~" << sn
    //                       << "() = default;" << std::endl;
    // }

    // if (o.is_immutable()) {
    //     context_->stream() << context_->indenter() << sn << "& operator=(const "
    //                       << sn << "&) = delete;" << std::endl;
    // } else if (ci.all_properties().empty()) {
    //     context_->stream() << context_->indenter()
    //                       << sn << "& operator=(const " << sn << "&) = default;"
    //                       << std::endl;
    // }
    // context_->utility().blank_line();
}

void cpp_domain_header_formatter::
default_constructor(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
move_constructor(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
complete_constructor(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
destructor(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
friends(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
getters_and_setters(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
member_variables(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
equality(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
to_stream(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
swap_and_assignment(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::
visitor_method(const sml::abstract_object& /*o*/) const {
}

void cpp_domain_header_formatter::format(const sml::abstract_object& o) const {
    open_class(o);
    {
        cpp_formatters::positive_indenter_scope s(context_->indenter());
        compiler_generated_constuctors(o);
        default_constructor(o);
        destructor(o);
        move_constructor(o);
        // if (!disable_complete_constructor_)
        complete_constructor(o);
        friends(o);
        visitor_method(o);
        // if (!disable_io_)
        to_stream(o);
        getters_and_setters(o);
        equality(o);
        swap_and_assignment(o);
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
    const sml::property_cache_interface& cache) const {

    cpp_formatters::indenter ind;
    cpp_formatters::utility u(s, ind);
    context_ = std::unique_ptr<context>(new context(s, cache, ind, u));

    const cpp_includes i = cpp_includes();
    const boost::filesystem::path relative_file_path;
    cpp_file_boilerplate_formatter f;
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

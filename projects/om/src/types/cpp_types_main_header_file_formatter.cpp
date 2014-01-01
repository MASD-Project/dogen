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
const std::string missing_helper_ptr("Helper pointer is null");
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
 * @brief Provides a set of utility functions to help with
 * formatting.
 *
 * All parameters passed in to the helper must have a lifetime
 * greater than (or equal to) the helper itself as it keeps
 * references to them.
 */
class cpp_types_main_header_file_formatter::helper : private sml::type_visitor {
public:
    helper() = delete;
    helper(const helper&) = delete;
    helper(helper&&) = delete;
    helper& operator=(const helper&) = delete;

private:
    static bool is_true(const boost::property_tree::ptree& meta_data,
        const std::string& key) {
        sml::meta_data_reader reader(meta_data);
        return reader.is_true(key);
    }

public:
    ~helper() noexcept { }

    helper(const sml::model& m, const boost::property_tree::ptree& meta_data,
        const annotation& a)
        : model_(m), utility_(stream_, indenter_), first_line_is_blank_(false),
          boilerplate_(is_true(meta_data, sml::tags::generate_preamble),
              is_true(meta_data,
                  sml::tags::cpp::types::header_file::generate_header_guards)),
          annotation_(a) {

        sml::meta_data_reader reader(meta_data);
        using types = sml::tags::cpp::types;
        const auto& fn(types::header_file::file_name);
        relative_file_path_ = reader.get(fn);
    }

private:
    using sml::type_visitor::visit;
    void visit(const sml::object& o) override;

public:
    /**
     * @brief Stream to which the formatted output will be sent.
     */
    std::ostringstream& stream() { return stream_; }

    /**
     * @brief Indentation facilities.
     */
    cpp_formatters::indenter& indenter() { return indenter_; }

    /**
     * @brief Formatting utility methods.
     */
    cpp_formatters::utility& utility() { return utility_; }

    /**
     * @brief Relative path of the element being formatted.
     */
    boost::filesystem::path relative_file_path() { return relative_file_path_; }

    /**
     * @brief If true, add a blank line at the start.
     */
    /**@{*/
    bool first_line_is_blank() const { return first_line_is_blank_; }
    void first_line_is_blank(bool value) { first_line_is_blank_ = value; }
    /**@}*/

public:
    /**
     * @brief Computes the include files for this header file.
     */
    void compute_includes(const sml::type& t) { t.accept(*this); }

    /**
     * @brief Uses the boilerplate formatter to format the start of
     * the boilerplate.
     */
    void format_begin() {
        boilerplate_.format_begin(stream_, annotation_, includes_,
            relative_file_path_);
    }

    /**
     * @brief Uses the boilerplate formatter to format the end of
     * the boilerplate.
     */
    void format_end() {
        boilerplate_.format_end(stream_, annotation_, relative_file_path_);
    }

private:
    const sml::model& model_;
    std::ostringstream stream_;
    cpp_formatters::indenter indenter_;
    cpp_formatters::utility utility_;
    bool first_line_is_blank_;
    cpp_includes includes_;
    cpp_file_boilerplate_formatter boilerplate_;
    const annotation annotation_;
    boost::filesystem::path relative_file_path_;
};

void cpp_types_main_header_file_formatter::helper::
visit(const sml::object& o) {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_true(sml::tags::cpp::serialization::boost::enabled)) {
        const auto fn(reader.get(
                sml::tags::cpp::serialization::boost::header_file::file_name));
        includes_.user().push_back(fn);
    }
}

cpp_types_main_header_file_formatter::cpp_types_main_header_file_formatter(
    const sml::model& model, const boost::filesystem::path& include_directory)
    : model_(model), include_directory_(include_directory),
      doxygen_next_(
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

void cpp_types_main_header_file_formatter::ensure_non_null_helper() const {
    if (helper_ != nullptr)
        return;

    BOOST_LOG_SEV(lg, error) << missing_helper_ptr;
    BOOST_THROW_EXCEPTION(formatting_error(missing_helper_ptr));
}

file cpp_types_main_header_file_formatter::
build_file(const boost::property_tree::ptree& meta_data) const {
    ensure_non_null_helper();
    file r;
    sml::meta_data_reader reader(meta_data);
    r.contents(helper_->stream().str());
    r.relative_path(helper_->relative_file_path());
    r.absolute_path(include_directory_ / helper_->relative_file_path());
    r.overwrite(reader.is_true(sml::tags::cpp::types::header_file::overwrite));
    return r;
}

void cpp_types_main_header_file_formatter::
external_equality(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_equality) ||
        !o.is_parent())
        return;

    const auto n(reader.get(sml::tags::cpp::types::qualified_name));
    helper_->stream() << helper_->indenter()
                      << "inline bool operator==(const "
                      << n << "& lhs, const " << n << "& rhs) ";
    helper_->utility().open_scope();
    {
        cpp_formatters::positive_indenter_scope s(helper_->indenter());
        helper_->stream() << helper_->indenter()
                          << "return lhs.equals(rhs);" << std::endl;
    }
    helper_->utility().close_scope();
    helper_->utility().blank_line();
}

void cpp_types_main_header_file_formatter::
external_swap(const sml::object& o) const {
    // swap overload is only available in leaf classes - MEC++-33
    if (o.all_properties().empty() || o.is_parent() || o.is_immutable())
        return;

    // there is a presumption here that swap is the very first
    // function after the user namespaces have been closed.
    helper_->utility().blank_line(2);
    const auto std_ns(std::list<std::string> { "std" });
    cpp_formatters::namespace_helper ns(helper_->stream(), std_ns);
    helper_->utility().blank_line();

    helper_->stream() << helper_->indenter() << "template<>" << std::endl
                      << helper_->indenter() << "inline void swap("
                      << std::endl;

    {
        cpp_formatters::positive_indenter_scope s(helper_->indenter());
        helper_->stream() << helper_->indenter();

        sml::meta_data_reader reader(o.meta_data());
        const auto n(reader.get(sml::tags::cpp::types::qualified_name));
        helper_->stream() << n << "& lhs," << std::endl;

        helper_->stream() << helper_->indenter();
        helper_->stream() << n << "& rhs) ";

        helper_->utility().open_scope();
        helper_->stream() << helper_->indenter() << "lhs.swap(rhs);"
                          << std::endl;
    }
    helper_->utility().close_scope();
    helper_->utility().blank_line();
}

void cpp_types_main_header_file_formatter::
external_inserter(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (!reader.is_true(sml::tags::cpp::io::enabled) ||
        !reader.is_true(sml::tags::cpp::io::enable_integrated_io))
        return;

    helper_->stream() << helper_->indenter()
                      << "std::ostream& operator<<(std::ostream& s, "
                      << "const " << o.name().simple_name() << "& v);"
                      << std::endl;
    helper_->utility().blank_line();
}

void cpp_types_main_header_file_formatter::
open_class(const sml::object& o) const {
    if (!o.documentation().empty())
        doxygen_next_.format(helper_->stream(), o.documentation());

    helper_->stream() << helper_->indenter() << "class "
                      << o.name().simple_name();

    if (!o.is_parent())
        helper_->stream() << " final";

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
        helper_->stream() << " :";
        helper_->stream() << " public ";
        helper_->stream() << parent_simple_name;
    }
    helper_->stream() << " {" << std::endl;
    helper_->first_line_is_blank(false);
}

void cpp_types_main_header_file_formatter::close_class() const {
    helper_->stream() << helper_->indenter() << "};" << std::endl;
}

void cpp_types_main_header_file_formatter::
explicitly_defaulted_functions(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_defaulted_functions))
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().public_access_specifier();

    const auto& sn(o.name().simple_name());
    if (reader.is_false(types::generate_explicit_default_constructor)) {
        helper_->stream() << helper_->indenter() << sn << "() = default;"
                          << std::endl;
    }

    helper_->stream() << helper_->indenter() << sn << "(const " << sn
                      << "&) = default;" << std::endl;

    if (reader.is_false(types::generate_explicit_move_constructor)) {
        helper_->stream() << helper_->indenter() << sn << "(" << sn
                          << "&&) = default;" << std::endl;
    }

    if (!o.is_parent() && !o.is_child()) {
        helper_->stream() << helper_->indenter() << "~" << sn
                          << "() = default;" << std::endl;
    }

    if (o.is_immutable()) {
        helper_->stream() << helper_->indenter() << sn
                          << "& operator=(const " << sn << "&) = delete;"
                          << std::endl;
    } else {
        const auto p(o.all_properties());
        if (p.empty()) {
            helper_->stream() << helper_->indenter() << sn
                              << "& operator=(const " << sn
                              << "&) = default;"
                              << std::endl;
        }
    }
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
default_constructor(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_explicit_default_constructor))
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().public_access_specifier();
    helper_->stream() << helper_->indenter()
                      << o.name().simple_name() << "();" << std::endl;
    helper_->first_line_is_blank(true);
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

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    if (props.size() == 1) {
        const auto p(*props.begin());
        sml::meta_data_reader reader(p.meta_data());
        using types = sml::tags::cpp::types;
        helper_->stream() << helper_->indenter() << "explicit "
                          << sn << "(const "
                          << reader.get(types::complete_name);

        if (!reader.is_true(types::is_simple_type))
            helper_->stream() << "&";

        helper_->stream() << " " << p.name() << ");" << std::endl;
        helper_->first_line_is_blank(true);
        return;
    }

    helper_->stream() << helper_->indenter() << sn << "(";
    {
        cpp_formatters::positive_indenter_scope s(helper_->indenter());
        bool is_first(true);
        for (const auto p : props) {
            helper_->stream() << (is_first ? "" : ",") << std::endl;

            sml::meta_data_reader reader(p.meta_data());
            using types = sml::tags::cpp::types;
            helper_->stream() << helper_->indenter() << "const "
                              << reader.get(types::complete_name);

            if (!reader.is_true(types::is_simple_type))
                helper_->stream() << "&";

            helper_->stream() << " " << p.name();
            is_first = false;
        }
        helper_->stream() << ");" << std::endl;
    }
    helper_->first_line_is_blank(true);
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

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    helper_->stream() << helper_->indenter() << sn << "(" << sn
                      << "&& rhs);" << std::endl;
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
destructor(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_explicit_destructor))
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().public_access_specifier();
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
        helper_->stream() << helper_->indenter() << "virtual ~" << sn
                          << "() noexcept = 0;" << std::endl;
    } else if (o.is_parent()) {
        helper_->stream() << helper_->indenter() << "virtual ~" << sn
                          << "() noexcept { }" << std::endl;
    }
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
friends(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_friends))
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().private_access_specifier();
    const auto sn(o.name().simple_name());
    helper_->stream() << helper_->indenter()
                      << "template<typename Archive>" << std::endl
                      << helper_->indenter()
                      << "friend void boost::serialization::save(Archive& ar"
                      << ", const " << sn << "& v, unsigned int version);"
                      << std::endl;
    helper_->utility().blank_line();

    helper_->stream() << helper_->indenter() << "template<typename Archive>"
                      << std::endl
                      << helper_->indenter()
                      << "friend void boost::serialization::load(Archive& ar"
                      << ", " << sn << "& v, unsigned int version);"
                      << std::endl;
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::simple_type_getter_and_setter(
    const std::string& owner_name, const sml::property& p) const {
    const auto doc(p.documentation());
    if (!doc.empty())
        doxygen_next_.format(helper_->stream(), doc);

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_start_block(helper_->stream(), doc);

    sml::meta_data_reader reader(p.meta_data());
    using types = sml::tags::cpp::types;
    const auto cn(reader.get(types::complete_name));
    helper_->stream() << helper_->indenter()
                      << cn << " " << p.name() << "() const;" << std::endl;

    if (!p.is_immutable()) {
        helper_->stream() << helper_->indenter();
        if (p.is_fluent())
            helper_->stream() << owner_name << "& ";
        else
            helper_->stream() << "void ";

        helper_->stream() << p.name() << "(const " << cn;

        if (!reader.is_true(types::is_simple_type))
            helper_->stream() << "&";

        helper_->stream() << " v);" << std::endl;
    }

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_end_block(helper_->stream(), doc);
}

void cpp_types_main_header_file_formatter::compound_type_getter_and_setter(
    const std::string& owner_name, const sml::property& p) const {
    const auto doc(p.documentation());

    if (!doc.empty())
        doxygen_next_.format(helper_->stream(), doc);

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_start_block(helper_->stream(), doc);

    // const getter
    sml::meta_data_reader reader(p.meta_data());
    using types = sml::tags::cpp::types;
    const auto cn(reader.get(types::complete_name));
    helper_->stream() << helper_->indenter() << "const " << cn
                      << "& " << p.name() << "() const;" << std::endl;

    if (!p.is_immutable()) {
        // Popsicle immutability
        helper_->stream() << helper_->indenter() << "" << cn
                          << "& " << p.name() << "();" << std::endl;

        // traditional setter
        helper_->stream() << helper_->indenter();
        if (p.is_fluent())
            helper_->stream() << owner_name << "& ";
        else
            helper_->stream() << "void ";
        helper_->stream() << p.name() << "(const " << cn;

        if (!reader.is_true(types::is_simple_type))
            helper_->stream() << "&";

        helper_->stream() << " v);" << std::endl;

        // move setter
        helper_->stream() << helper_->indenter();
        if (p.is_fluent())
            helper_->stream() << owner_name << "& ";
        else
            helper_->stream() << "void ";
        helper_->stream() << p.name() << "(const " << cn;

        if (!reader.is_true(types::is_simple_type))
            helper_->stream() << "&&";

        helper_->stream() << " v);" << std::endl;
    }

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_end_block(helper_->stream(), doc);
}

void cpp_types_main_header_file_formatter::
getters_and_setters(const sml::object& o) const {
    if (o.local_properties().empty())
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().public_access_specifier();
    bool is_first(true);
    for (const auto p : o.local_properties()) {
        if (!is_first)
            helper_->utility().blank_line();

        sml::meta_data_reader reader(p.meta_data());
        if (reader.is_true(sml::tags::cpp::types::is_simple_type))
            simple_type_getter_and_setter(o.name().simple_name(), p);
        else
            compound_type_getter_and_setter(o.name().simple_name(), p);
        is_first = false;
    }
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
member_variables(const sml::object& o) const {
    if (o.local_properties().empty())
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().private_access_specifier();
    for (const auto p : o.local_properties()) {
        sml::meta_data_reader reader(p.meta_data());
        helper_->stream() << helper_->indenter()
                          << reader.get(sml::tags::cpp::types::complete_name)
                          << " "
                          << helper_->utility().as_member_variable(p.name())
                          << ";"
                          << std::endl;
    }
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
internal_equality(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_equality))
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    const auto sn(o.name().simple_name());
    if (o.is_parent()) {
        // equality is only public in leaf classes - MEC++-33
        helper_->utility().protected_access_specifier();
        helper_->stream() << helper_->indenter() << "bool compare(const "
                          << sn << "& rhs) const;" << std::endl;
    } else {
        helper_->utility().public_access_specifier();
        helper_->stream() << helper_->indenter() << "bool operator==(const "
                          << sn <<  "& rhs) const;" << std::endl;
        helper_->stream() << helper_->indenter() << "bool operator!=(const "
                          << sn << "& rhs) const ";
        helper_->utility().open_scope();
        {
            cpp_formatters::positive_indenter_scope s(helper_->indenter());
            helper_->stream() << helper_->indenter()
                              << "return !this->operator==(rhs);"
                              << std::endl;
        }
        helper_->utility().close_scope();
    }

    if (!o.is_parent() && !o.is_child())
        return;

    helper_->utility().blank_line();
    helper_->utility().public_access_specifier();
    using types = sml::tags::cpp::types;
    if (o.is_parent() && !o.is_child()) {
        helper_->stream() << helper_->indenter()
                          << "virtual bool equals(const " << sn
                          <<  "& other) const = 0;"
                          << std::endl;
    } else if (o.is_parent()) {
        helper_->stream() << helper_->indenter()
                          << "virtual bool equals(const "
                          << reader.get(types::qualified_original_parent_name)
                          <<  "& other) const = 0;"
                          << std::endl;
    } else {
        helper_->stream() << helper_->indenter()
                          << "bool equals(const "
                          << reader.get(types::qualified_original_parent_name)
                          <<  "& other) const override;"
                          << std::endl;
    }
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
to_stream(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_to_stream))
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().public_access_specifier();
    if (o.is_parent()) {
        helper_->stream() << helper_->indenter()
                          << "virtual void to_stream("
                          << "std::ostream& s) const;"
                          << std::endl;
    } else {
        helper_->stream() << helper_->indenter()
                          << "void to_stream(std::ostream& s) "
                          << "const override;"
                          << std::endl;
    }
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
internal_swap(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_swap))
        return;

    const auto props(o.all_properties());
    if ((props.empty() && !o.is_parent()) || o.is_immutable())
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    // swap is only public in leaf classes - MEC++-33
    if (o.is_parent())
        helper_->utility().protected_access_specifier();
    else
        helper_->utility().public_access_specifier();

    const auto sn(o.name().simple_name());
    helper_->stream() << helper_->indenter() << "void swap("
                      << sn << "& other) noexcept;"
                      << std::endl;
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
internal_assignment(const sml::object& o) const {
    // assignment is only available in leaf classes - MEC++-33
    const auto props(o.all_properties());
    if (props.empty() || o.is_parent() || o.is_immutable())
        return;

    const auto sn(o.name().simple_name());
    // FIXME: hack just to get zero diffs with legacy
    // if (helper_->first_line_is_blank())
    //     helper_->utility().blank_line();

    // helper_->utility().public_access_specifier();
    helper_->stream() << helper_->indenter() << sn << "& operator=("
                      << sn << " other);" << std::endl;
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
visitor_method(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_accept))
        return;

    if (helper_->first_line_is_blank())
        helper_->utility().blank_line();

    helper_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    using types = sml::tags::cpp::types;
    const auto opn(reader.get(types::qualified_original_parent_name));

    if (o.is_visitable()) {
        helper_->stream() << helper_->indenter()
                          << "virtual void accept(const " << sn
                          << "_visitor& v) const = 0;" << std::endl;
        helper_->stream() << helper_->indenter() << "virtual void accept("
                          << sn << "_visitor& v) const = 0;" << std::endl;
        helper_->stream() << helper_->indenter()
                          << "virtual void accept(const " << sn
                          << "_visitor& v) = 0;" << std::endl;
        helper_->stream() << helper_->indenter() << "virtual void accept("
                          << sn << "_visitor& v) = 0;" << std::endl;
        helper_->utility().blank_line();
        return;
    }

    helper_->utility().public_access_specifier();
    helper_->stream() << helper_->indenter()
                      << "virtual void accept(const "
                      << opn << "_visitor& v) const override {"
                      << std::endl;

    {
        cpp_formatters::positive_indenter_scope s(helper_->indenter());
        helper_->stream() << helper_->indenter() << "v.visit(*this);"
                          << std::endl;
    }
    helper_->stream() << helper_->indenter() << "}" << std::endl;
    helper_->utility().blank_line();
    helper_->stream() << helper_->indenter() << "virtual void accept("
                      << opn << "_visitor& v) const override {"
                      << std::endl;

    {
        cpp_formatters::positive_indenter_scope s(helper_->indenter());
        helper_->stream() << helper_->indenter() << "v.visit(*this);"
                          << std::endl;
    }
    helper_->stream() << helper_->indenter() << "}" << std::endl;
    helper_->utility().blank_line();
    helper_->stream() << helper_->indenter()
                      << "virtual void accept(const "
                      << opn << "_visitor& v) override {" << std::endl;

    {
        cpp_formatters::positive_indenter_scope s(helper_->indenter());
        helper_->stream() << helper_->indenter() << "v.visit(*this);"
                          << std::endl;
    }
    helper_->stream() << helper_->indenter() << "}" << std::endl;
    helper_->utility().blank_line();
    helper_->stream() << helper_->indenter() << "virtual void accept("
                      << opn << "_visitor& v) override {" << std::endl;

    {
        cpp_formatters::positive_indenter_scope s(helper_->indenter());
        helper_->stream() << helper_->indenter() << "v.visit(*this);"
                          << std::endl;
    }
    helper_->stream() << helper_->indenter() << "}" << std::endl;
    helper_->first_line_is_blank(true);
}

void cpp_types_main_header_file_formatter::
visit(const dogen::sml::enumeration& e) const {
    ensure_non_null_helper();

    BOOST_LOG_SEV(lg, debug) << "Formatting enumeration: " << e.name();
    {
        const auto ns(namespaces(e.name()));
        cpp_formatters::namespace_helper nsh(helper_->stream(), ns);
        helper_->utility().blank_line();

        doxygen_next_.format(helper_->stream(), e.documentation());
        helper_->stream() << helper_->indenter() << "enum class "
                         << e.name().simple_name() << " : unsigned int ";

        helper_->utility().open_scope();
        {
            cpp_formatters::positive_indenter_scope pis(helper_->indenter());
            bool is_first(true);
            std::ostringstream assignment;
            std::ostringstream comment;
            for (const auto& enumerator : e.enumerators()) {
                if (!is_first) {
                    const auto c(comment.str());
                    helper_->stream() << assignment.str() << ",";
                    if (!c.empty())
                        helper_->stream() << " " << c;
                    assignment.str(empty);
                    comment.str(empty);
                }
                assignment << helper_->indenter() << enumerator.name() << " = "
                           << enumerator.value();
                doxygen_previous_.format(comment, e.documentation());
                is_first = false;
            }

            helper_->stream() << assignment.str();
            const auto c(comment.str());
            if (!c.empty())
                helper_->stream() << " " << c;
        }
        helper_->stream() << helper_->indenter() << "};" << std::endl;
        helper_->utility().blank_line();
    }
}

void cpp_types_main_header_file_formatter::
visit(const dogen::sml::object& o) const {
    ensure_non_null_helper();
    {
        const auto ns(namespaces(o.name()));
        cpp_formatters::namespace_helper nsh(helper_->stream(), ns);
        helper_->utility().blank_line();
        open_class(o);
        {
            cpp_formatters::positive_indenter_scope s(helper_->indenter());
            explicitly_defaulted_functions(o);
            default_constructor(o);
            destructor(o);
            move_constructor(o);
            complete_constructor(o);
            friends(o);
            visitor_method(o);
            to_stream(o);
            getters_and_setters(o);
            internal_equality(o);
            internal_swap(o);
            internal_assignment(o);
            member_variables(o);
        }
        close_class();
        helper_->utility().blank_line();
        external_equality(o);
        external_inserter(o);
    }
    external_swap(o);
}

bool cpp_types_main_header_file_formatter::
generate(const boost::property_tree::ptree& meta_data) const {
    sml::meta_data_reader reader(meta_data);
    const auto& gen(sml::tags::cpp::types::header_file::generate);
    return reader.is_true(gen);
}

file cpp_types_main_header_file_formatter::
format(const sml::module& module, const annotation& a) const {
    helper_ = std::make_shared<helper>(model_, module.meta_data(), a);
    helper_->format_begin();
    const auto ns(namespaces(module.name()));

    if (!ns.empty()) {

        cpp_formatters::namespace_helper nsh(helper_->stream(), ns);
        helper_->utility().blank_line();

        cpp_formatters::namespace_formatter nsf(helper_->stream());
        doxygen_next_.format(helper_->stream(), module.documentation());
        nsf.format_start(module.name().simple_name());
        nsf.format_end();

        helper_->stream() << " ";
    } else {
        cpp_formatters::namespace_formatter nsf(helper_->stream());
        doxygen_next_.format(helper_->stream(), module.documentation());
        nsf.format_start(module.name().simple_name());
        nsf.format_end();
    }
    helper_->utility().blank_line();
    helper_->format_end();

    const file r(build_file(module.meta_data()));
    helper_ = std::shared_ptr<helper>();
    return r;
}

file cpp_types_main_header_file_formatter::
format(const sml::type& t, const annotation& a) const {
    helper_ = std::make_shared<helper>(model_, t.meta_data(), a);
    helper_->compute_includes(t);
    helper_->format_begin();
    t.accept(*this);
    helper_->utility().blank_line();
    helper_->format_end();

    const file r(build_file(t.meta_data()));
    helper_ = std::shared_ptr<helper>();
    return r;
}

} }

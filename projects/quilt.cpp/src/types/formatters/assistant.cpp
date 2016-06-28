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
#include <sstream>
#include <boost/pointer_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/formatters/types/comment_formatter.hpp"
#include "dogen/formatters/types/annotation_formatter.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/quilt.cpp/io/settings/helper_settings_io.hpp"
#include "dogen/quilt.cpp/types/properties/name_builder.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/io/helper_methods_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/helper_methods_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/helper_methods_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formatters.assistant"));

const std::string empty;
const std::string by_ref_text("&");
const std::string void_keyword_text("void");
const std::string final_keyword_text("final ");
const std::string namespace_separator("::");
const std::string member_variable_postfix("_");

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool documenting_previous_identifier(true);

const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");
const std::string header_guard_not_set(
    "Header guard for formatter is not set. Formatter: ");
const std::string formatter_properties_missing(
    "Could not find formatter properties for formatter: ");
const std::string unexpected_opaque_settings(
    "Unexpectd opaque settings type.");
const std::string family_not_found("Family not found: ");
const std::string qn_missing("Could not find qualified name for language.");
const std::string empty_settings("Helper properties must have settings.");
const std::string empty_family("Family cannot be empty.");
const std::string helpless_family("No registered helpers found for family: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

template<typename IdentifiableAndQualified>
inline std::pair<std::string, std::string>
get_identifiable_and_qualified(const IdentifiableAndQualified& iaq) {
    const auto i(iaq.qualified().find(yarn::languages::cpp));
    if (i == iaq.qualified().end()) {
        BOOST_LOG_SEV(lg, error) << qn_missing << yarn::languages::cpp;
        BOOST_THROW_EXCEPTION(formatting_error(qn_missing));
    }

    return std::make_pair(iaq.identifiable(), i->second);
}

assistant::assistant(const context& ctx,
    const dynamic::ownership_hierarchy& oh, const formatters::file_types ft) :
    context_(ctx),
    formatter_properties_(obtain_formatter_properties(oh.formatter_name())),
    ownership_hierarchy_(oh), file_type_(ft) {

    dogen::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);
    validate();
}

std::string assistant::
make_final_keyword_text(const properties::class_info& c) {
    return c.is_final() ? final_keyword_text : empty;
}

std::string assistant::
make_by_ref_text(const properties::property_info& p) {
    return (p.type().is_primitive() || p.type().is_enumeration()) ?
        empty : by_ref_text;
}

std::string assistant::
make_setter_return_type(const std::string& containing_type_name,
    const properties::property_info& p) {
    std::ostringstream s;
    if (p.is_fluent())
        s << containing_type_name << by_ref_text;
    else
        s << void_keyword_text;

    return s.str();
}

std::string assistant::get_qualified_name(const yarn::name& n) const {
    const auto pair(get_identifiable_and_qualified(n));
    return pair.second;
}

std::string assistant::get_qualified_name(const yarn::name_tree& nt) const {
    const auto pair(get_identifiable_and_qualified(nt));
    return pair.second;
}

void assistant::ensure_formatter_properties_are_present() const {
    if (formatter_properties_)
        return;

    const auto fn(ownership_hierarchy_.formatter_name());
    BOOST_LOG_SEV(lg, error) << formatter_properties_missing << fn;
    BOOST_THROW_EXCEPTION(formatting_error(formatter_properties_missing + fn));
}

boost::optional<properties::formatter_properties> assistant::
obtain_formatter_properties(const std::string& formatter_name) const {
    const auto& fn(formatter_name);
    const auto i(context_.element_properties().formatter_properties().find(fn));
    if (i == context_.element_properties().formatter_properties().end())
        return boost::optional<properties::formatter_properties>();
    return i->second;
}

std::string assistant::make_member_variable_name(
    const properties::property_info& p) const {
    return p.name() + member_variable_postfix;
}

std::string assistant::make_getter_setter_name(
    const properties::property_info& p) const {
    return p.name();
}

std::list<std::string> assistant::make_namespaces(const yarn::name& n) const {
    properties::name_builder b;
    return b.namespace_list(n);
}

bool assistant::
is_formatter_enabled(const std::string& formatter_name) const {
    const auto fp(obtain_formatter_properties(formatter_name));
    if (!fp) {
        BOOST_LOG_SEV(lg, error) << formatter_properties_missing
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(formatting_error(formatter_properties_missing +
                formatter_name));
    }
    return fp->enabled();
}

bool assistant::is_serialization_enabled() const {
    using formatters::serialization::traits;
    return is_formatter_enabled(traits::class_header_formatter_name());
}

bool assistant::is_io_enabled() const {
    using formatters::io::traits;
    return is_formatter_enabled(traits::class_header_formatter_name());
}

bool assistant::is_hash_enabled() const {
    using formatters::hash::traits;
    return is_formatter_enabled(traits::class_header_formatter_name());
}

bool assistant::is_test_data_enabled() const {
    using formatters::test_data::traits;
    return is_formatter_enabled(traits::class_header_formatter_name());
}

bool assistant::is_complete_constructor_disabled() const {
    return context_.bundle().aspect_settings().disable_complete_constructor();
}

bool assistant::is_xml_serialization_disabled() const {
    return context_.bundle().aspect_settings().disable_xml_serialization();
}

void assistant::validate() const {
    if (!formatter_properties_)
        return;

    const auto& fn(ownership_hierarchy_.formatter_name());
    const auto fp(*formatter_properties_);
    if (fp.file_path().empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(file_path_not_set + fn));
    }

    if (file_type_ == file_types::cpp_header) {
        if (!fp.header_guard() || fp.header_guard()->empty()) {
            BOOST_LOG_SEV(lg, error) << header_guard_not_set << fn;
            BOOST_THROW_EXCEPTION(formatting_error(header_guard_not_set + fn));
        }
    }
}

dogen::formatters::cpp::scoped_boilerplate_formatter
assistant::make_scoped_boilerplate_formatter() {
    ensure_formatter_properties_are_present();
    const auto& fp(*formatter_properties_);
    const auto gs(context_.bundle().general_settings());
    return dogen::formatters::cpp::scoped_boilerplate_formatter(
        stream(), gs, fp.inclusion_dependencies(),
        fp.header_guard() ? *fp.header_guard() : empty);
}

dogen::formatters::cpp::scoped_namespace_formatter
assistant::make_scoped_namespace_formatter(const std::list<std::string>& ns) {
    return dogen::formatters::cpp::scoped_namespace_formatter(
        stream(), ns, false/*create_anonymous_namespace*/,
        true/*add_new_line*/);
}

nested_type_formatting_assistant assistant::
make_nested_type_formatting_assistant() {
    return nested_type_formatting_assistant(stream());
}

void assistant::make_annotation_preamble(
    const boost::optional<dogen::formatters::general_settings> gs) {
    if (!gs)
        return;

    dogen::formatters::annotation_formatter af;
    af.format_preamble(stream(), dogen::formatters::comment_styles::shell_style,
        (*gs).annotation());
}

dogen::formatters::file assistant::
make_file(const bool overwrite) const {
    ensure_formatter_properties_are_present();
    return make_file(formatter_properties_->file_path(), overwrite);
}

void assistant::comment(const std::string& c) {
    if (c.empty())
        return;

    dogen::formatters::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::c_style,
        !last_line_is_blank);
    f.format(stream(), c);
}

void assistant::
comment_start_method_group(const std::string& documentation,
    const bool add_comment_blocks) {
    if (documentation.empty())
        return;

    {
        dogen::formatters::positive_indenter_scope pis(stream());
        dogen::formatters::comment_formatter f(
            !start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            dogen::formatters::comment_styles::c_style,
            !last_line_is_blank);

        f.format(stream(), documentation);
        if (add_comment_blocks) {
            f.format_doxygen_start_block(stream(), documentation);
            stream() << std::endl;
        }
    }
}

void assistant::comment_end_method_group(const std::string& documentation,
    const bool add_comment_blocks) {
    if (documentation.empty())
        return;

    {
        dogen::formatters::positive_indenter_scope pis(stream());
        dogen::formatters::comment_formatter f(
            start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            dogen::formatters::comment_styles::c_style,
            !last_line_is_blank);

        if (add_comment_blocks) {
            f.format_doxygen_end_block(stream(), documentation);
            stream() << std::endl;
        }
    }
}

std::string assistant::comment_inline(const std::string& c) const {
    if (c.empty())
        return empty;

    std::ostringstream s;
    s << " ";
    dogen::formatters::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        documenting_previous_identifier,
        dogen::formatters::comment_styles::cpp_style,
        !last_line_is_blank);

    f.format(s, c);
    return s.str();
}

std::list<std::shared_ptr<formatters::formatter_helper_interface>> assistant::
get_helpers_for_formatter(const properties::helper_properties& hp) const {
    /*
     * Helper properties must always have settings, otherwise
     * there is no point to their existence.
     */
    const auto s(hp.current().settings());
    if (!s) {
        BOOST_LOG_SEV(lg, error) << empty_settings;
        BOOST_THROW_EXCEPTION(formatting_error(empty_settings));
    }

    /*
     * Family cannot be empty as that is not a valid family.
     */
    const auto family(s->family());
    if(family.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_family;
        BOOST_THROW_EXCEPTION(formatting_error(empty_family));
    }

    /*
     * A family should have at least one helper registered, but
     * for now we are letting it through.
     * FIXME: throw.
     */
    const auto i(context_.helpers().find(family));
    if (i == context_.helpers().end()) {
        BOOST_LOG_SEV(lg, debug) << "Could not find helpers for family: "
                                 << family;
        return std::list<
            std::shared_ptr<formatters::formatter_helper_interface>
            >();
    }
    BOOST_LOG_SEV(lg, debug) << "Found helpers for family: " << family;

    /*
     * Not all formatters need help, so its fine not to have a
     * helper registered against a particular formatter.
     */
    const auto j(i->second.find(ownership_hierarchy_.formatter_name()));
    if (j == i->second.end()) {
        BOOST_LOG_SEV(lg, debug) << "Could not find helpers for formatter:"
                                 << ownership_hierarchy_.formatter_name();
        return std::list<
            std::shared_ptr<formatters::formatter_helper_interface>
            >();
    }
    BOOST_LOG_SEV(lg, debug) << "Found helpers for formatter: "
                             << ownership_hierarchy_.formatter_name();

    return j->second;
}

void assistant::add_helper_methods(const properties::class_info& c) {
    BOOST_LOG_SEV(lg, debug) << "Processing entity: " << c.name();

    using tt = formatters::types::traits;
    const auto cifn(tt::class_implementation_formatter_name());
    const auto fn(ownership_hierarchy_.formatter_name());
    const bool is_types_class_implementation(fn == cifn);
    const bool in_inheritance(c.is_parent() || !c.parents().empty());
    const bool requires_io(is_io_enabled() && in_inheritance);

    if (is_types_class_implementation && requires_io) {
        BOOST_LOG_SEV(lg, debug) << "Creating io helper methods in types.";
        io::helper_methods_formatter f(c.properties());
        f.format(stream());
    } else
        BOOST_LOG_SEV(lg, debug) << "Helper methods for types io not required."
                                 << " is types class implementation: '"
                                 << is_types_class_implementation
                                 << "' requires io: '" << requires_io << "'";

    using iot = formatters::io::traits;
    const auto io_ci_fn(iot::class_implementation_formatter_name());
    const bool is_io_class_implementation(fn == io_ci_fn);
    if (is_io_class_implementation && !in_inheritance) {
        BOOST_LOG_SEV(lg, debug) << "Creating io helper methods.";
        io::helper_methods_formatter f(c.properties());
        f.format(stream());
    } else
        BOOST_LOG_SEV(lg, debug) << "Helper methods for io not required."
                                 << " is io class implementation: '"
                                 << is_io_class_implementation << "'";

    using ht = formatters::hash::traits;
    const auto h_ci_fn(ht::class_implementation_formatter_name());
    const bool is_hash_class_implementation(fn == h_ci_fn);
    const bool requires_hash(is_hash_enabled());

    if (is_hash_class_implementation && requires_hash) {
        BOOST_LOG_SEV(lg, debug) << "Creating hash helper methods.";
        hash::helper_methods_formatter f(c.properties());
        f.format(stream());
    } else {
        BOOST_LOG_SEV(lg, debug) << "Hash helper methods not required."
                                 << " is hash class implementation: '"
                                 << is_hash_class_implementation << "'";
    }

    using tdt = formatters::test_data::traits;
    const auto td_ci_fn(tdt::class_implementation_formatter_name());
    const bool is_test_data_class_implementation(fn == td_ci_fn);
    const bool requires_test_data(is_test_data_enabled());

    if (is_test_data_class_implementation && requires_test_data) {
        BOOST_LOG_SEV(lg, debug) << "Creating test data helper methods.";
        test_data::helper_methods_formatter f(c.name(), c.properties());
        f.format(stream());
    } else {
        BOOST_LOG_SEV(lg, debug) << "Test data helper methods not required."
                                 << " is test data class implementation: '"
                                 << is_test_data_class_implementation << "' ";
    }
}

void assistant::add_helper_methods(const bool in_inheritance) {
    if (context_.element_properties().helper_properties().empty()) {
        // FIXME: supply target name as an argument and print its ID
        // FIXME: here. This needs to wait until we start using yarn
        // FIXME: types on all formatters.
        BOOST_LOG_SEV(lg, debug) << "No helper methods for: ";
    }

    for (const auto& hp : context_.element_properties().helper_properties()) {
        const auto helpers(get_helpers_for_formatter(hp));

        /*
         * Check to see if the helper is enabled, given the system's
         * current configuration. If enabled, format it.
         */
        for (const auto& h : helpers) {
            if (!h->is_enabled(*this, in_inheritance)) {
                BOOST_LOG_SEV(lg, debug) << "Helper is not enabled.";
                continue;
            }
            h->format(*this, hp);
        }
    }
}

std::string assistant::streaming_for_type(
    const properties::helper_descriptor& /*hp*/,
    const std::string& /*s*/) const {

    std::string r;
    return r;
}


bool assistant::requires_hashing_helper_method(
    const properties::nested_type_info& t) const {
    return nested_type_formatting_assistant::
        requires_hashing_helper_method(t);
}

boost::shared_ptr<settings::odb_settings> assistant::
get_odb_settings(const std::unordered_map<std::string,
    boost::shared_ptr<quilt::cpp::settings::opaque_settings>
    >& os) const {
    const auto fn(odb::traits::class_header_formatter_name());
    const auto i(os.find(fn));
    if (i == os.end())
        return boost::shared_ptr<settings::odb_settings>();

    auto r(boost::dynamic_pointer_cast<settings::odb_settings>(i->second));
    if (!r) {
        BOOST_LOG_SEV(lg, error) << unexpected_opaque_settings;
        BOOST_THROW_EXCEPTION(formatting_error(unexpected_opaque_settings));
    }
    return r;
}

boost::shared_ptr<settings::odb_settings>
assistant::get_odb_settings() const {
    const auto& os(context_.bundle().opaque_settings());
    return get_odb_settings(os);
}

boost::shared_ptr<settings::odb_settings> assistant::
get_odb_settings(const std::string& property_id) const {

    const auto& osfp(context_.bundle().opaque_settings_for_property());
    const auto i(osfp.find(property_id));
    if (i == osfp.end())
        return boost::shared_ptr<settings::odb_settings>();

    const auto& os(i->second);
    return get_odb_settings(os);
}

std::ostream& assistant::stream() {
    return filtering_stream_;
}

dogen::formatters::file assistant::make_file(
    const boost::filesystem::path& full_path, const bool overwrite) const {
    dogen::formatters::file r;
    r.content(stream_.str());
    r.path(full_path);
    r.overwrite(overwrite);
    return r;
}

} } } }

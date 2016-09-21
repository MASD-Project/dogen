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
#include "dogen/formatters/types/decoration_formatter.hpp"
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/quilt.cpp/io/annotations/streaming_annotations_io.hpp"
#include "dogen/quilt.cpp/io/annotations/helper_annotations_io.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_properties_io.hpp"
#include "dogen/quilt.cpp/types/formattables/name_builder.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
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
const std::string underscore("_");

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
const std::string facet_directory_missing(
    "Facet directory is missing for facet: ");
const std::string unexpected_opaque_annotations(
    "Unexpectd opaque annotations type.");
const std::string family_not_found("Family not found: ");
const std::string no_helpers_for_family("No helpers found for family: ");
const std::string qn_missing("Could not find qualified name for language.");
const std::string empty_annotations("Helper properties must have annotations.");
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
    const dynamic::ownership_hierarchy& oh, const formatters::file_types ft,
    const std::string& id) :
    context_(ctx),
    formatter_properties_(obtain_formatter_properties(oh.formatter_name())),
    ownership_hierarchy_(oh), file_type_(ft) {

    BOOST_LOG_SEV(lg, debug) << "Processing element: " << id
                             << " using: " << oh.formatter_name();

    dogen::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);
    validate();
}

std::string assistant::
make_final_keyword_text(const yarn::object& o) {
    return o.is_final() ? final_keyword_text : empty;
}

std::string assistant::
make_by_ref_text(const yarn::attribute& attr) {
    return attr.parsed_type().is_current_simple_type() ? empty : by_ref_text;
}

std::string assistant::
make_setter_return_type(const std::string& containing_type_name,
    const yarn::attribute& attr) {
    std::ostringstream s;
    if (attr.is_fluent())
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

std::string assistant::get_identifiable_model_name(const yarn::name& n) const {
    using boost::algorithm::join;
    return join(n.location().model_modules(), underscore);
}

std::string assistant::get_product_name(const yarn::name& n) const {
    if (n.location().external_modules().empty())
        return empty;

    return n.location().external_modules().front();
}

void assistant::ensure_formatter_properties_are_present() const {
    if (formatter_properties_)
        return;

    const auto fn(ownership_hierarchy_.formatter_name());
    BOOST_LOG_SEV(lg, error) << formatter_properties_missing << fn;
    BOOST_THROW_EXCEPTION(formatting_error(formatter_properties_missing + fn));
}

boost::optional<formattables::formatter_properties> assistant::
obtain_formatter_properties(const std::string& formatter_name) const {
    const auto& fn(formatter_name);
    const auto i(context_.element_properties().formatter_properties().find(fn));
    if (i == context_.element_properties().formatter_properties().end())
        return boost::optional<formattables::formatter_properties>();
    return i->second;
}

std::string assistant::
make_member_variable_name(const yarn::attribute& attr) const {
    return attr.name().simple() + member_variable_postfix;
}

std::string assistant::
make_getter_setter_name(const yarn::attribute& attr) const {
    return attr.name().simple();
}

std::list<std::string> assistant::make_namespaces(const yarn::name& n) const {
    formattables::name_builder b;
    return b.namespace_list(n);
}

bool assistant::
is_formatter_enabled(const std::string& formatter_name) const {
    ensure_formatter_properties_are_present();
    const auto fp(*formatter_properties_);
    const auto i(fp.enabled_formatters().find(formatter_name));
    return i != fp.enabled_formatters().end();
}

std::string assistant::
get_facet_directory_for_facet(const std::string& facet_name) const {
    ensure_formatter_properties_are_present();
    const auto& fdff(formatter_properties_->facet_directory_for_facet());
    const auto i(fdff.find(facet_name));
    if (i == fdff.end()) {
        BOOST_LOG_SEV(lg, error) << facet_directory_missing << facet_name;
        BOOST_THROW_EXCEPTION(
            formatting_error(facet_directory_missing + facet_name));
    }
    return i->second;
}

std::string assistant::get_odb_facet_directory() const {
    using formatters::odb::traits;
    return get_facet_directory_for_facet(traits::facet_name());
}

bool assistant::requires_manual_default_constructor() const {
    const auto& ap(context_.element_properties().aspect_properties());
    return ap.requires_manual_default_constructor();
}

bool assistant::requires_manual_move_constructor() const {
    const auto& ap(context_.element_properties().aspect_properties());
    return ap.requires_manual_move_constructor();
}

bool assistant::requires_stream_manipulators() const {
    const auto& ap(context_.element_properties().aspect_properties());
    return ap.requires_stream_manipulators();
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

bool assistant::is_odb_enabled() const {
    using formatters::odb::traits;
    return is_formatter_enabled(traits::class_header_formatter_name());
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
    const auto dc(context_.element_properties().decoration_configuration());
    return dogen::formatters::cpp::scoped_boilerplate_formatter(
        stream(), dc, fp.inclusion_dependencies(),
        fp.header_guard() ? *(fp.header_guard()) : empty);
}

dogen::formatters::cpp::scoped_namespace_formatter
assistant::make_scoped_namespace_formatter(const std::list<std::string>& ns) {
    return dogen::formatters::cpp::scoped_namespace_formatter(
        stream(), ns, false/*create_anonymous_namespace*/,
        true/*add_new_line*/);
}

void assistant::make_decoration_preamble() {
    const auto dc(context_.element_properties().decoration_configuration());
    make_decoration_preamble(dc);
}

void assistant::make_decoration_preamble(
    const boost::optional<dogen::formatters::decoration_configuration> dc) {
    if (!dc)
        return;

    dogen::formatters::decoration_formatter af;
    const auto comment_style(dogen::formatters::comment_styles::shell_style);
    af.format_preamble(stream(), comment_style, *dc);
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

std::list<std::shared_ptr<formatters::helper_formatter_interface>>
assistant::get_helpers(const formattables::helper_properties& hp) const {
    const auto s(hp.current().helper_annotations());

    /*
     * A family must have at least one helper registered. This is a
     * good way to detect spurious families in data files.
     */
    const auto fam(s.family());
    const auto i(context_.helpers().find(fam));
    if (i == context_.helpers().end()) {
        BOOST_LOG_SEV(lg, error) << no_helpers_for_family << fam;
        BOOST_THROW_EXCEPTION(formatting_error(no_helpers_for_family + fam));
    }
    BOOST_LOG_SEV(lg, debug) << "Found helpers for family: " << fam;

    /*
     * Not all formatters need help, so its fine not to have a
     * helper registered against a particular formatter.
     */
    const auto j(i->second.find(ownership_hierarchy_.formatter_name()));
    if (j != i->second.end()) {
        BOOST_LOG_SEV(lg, debug) << "Found helpers for formatter: "
                                 << ownership_hierarchy_.formatter_name();
        return j->second;
    }

    BOOST_LOG_SEV(lg, debug) << "Could not find helpers for formatter:"
                             << ownership_hierarchy_.formatter_name();
    return std::list<std::shared_ptr<formatters::helper_formatter_interface>>();
}

bool assistant::is_io() const {
    const auto fn(ownership_hierarchy_.facet_name());
    return formatters::io::traits::facet_name()  == fn;
}

bool assistant::
is_streaming_enabled(const formattables::helper_properties& hp) const {
    /*
     * If the IO facet is globally disabled, we don't need streaming.
     */
    if (!is_io_enabled())
        return false;

    /*
     * If we are in the IO facet, and we are not in an inheritance
     * relationship we need streaming.
     */
    if (is_io() && !hp.in_inheritance_relationship())
        return true;

    /*
     * If we are in the types class implementation and we are in an
     * inheritance relationship, we'll need streaming.
     */
    using tt = formatters::types::traits;
    const auto cifn(tt::class_implementation_formatter_name());
    const auto fn(ownership_hierarchy_.formatter_name());
    bool in_types_class_implementation(fn == cifn);
    return in_types_class_implementation && hp.in_inheritance_relationship();
}

void assistant::add_helper_methods() {
    if (context_.element_properties().helper_properties().empty()) {
        // FIXME: supply target name as an argument and print its ID
        // FIXME: here. This needs to wait until we start using yarn
        // FIXME: types on all formatters.
        BOOST_LOG_SEV(lg, debug) << "No helper methods for: ";
    }

    for (const auto& hp : context_.element_properties().helper_properties()) {
        BOOST_LOG_SEV(lg, debug) << "Helper properties: " << hp;
        const auto helpers(get_helpers(hp));

        /*
         * Check to see if the helper is enabled, given the system's
         * current configuration. If enabled, format it.
         */
        for (const auto& h : helpers) {
            if (!h->is_enabled(*this, hp)) {
                BOOST_LOG_SEV(lg, debug) << "Helper is not enabled." << h->id();
                continue;
            }

            BOOST_LOG_SEV(lg, debug) << "Formatting with helper: " << h->id();
            h->format(*this, hp);
        }
    }
}

std::string assistant::streaming_for_type(
    const annotations::streaming_annotations& ss, const std::string& s) const {

    std::ostringstream stream;
    dogen::formatters::utility_formatter uf(stream);
    BOOST_LOG_SEV(lg, debug) << "Annotations for streaming for type: " << ss;
    if (ss.remove_unprintable_characters())
        uf.insert_streamed("tidy_up_string(" + s + ")");
    else if (!ss.string_conversion_method().empty()) {
        // FIXME: hack!
        std::string s1(s);
        const auto i(s1.find('*'));
        if (i != std::string::npos)
            s1 = "(" + s + ")";
        uf.insert_streamed(s1 + "." + ss.string_conversion_method());
    } else if (ss.requires_quoting())
        uf.insert_streamed(s);
    else
        uf.insert(s);

    return stream.str();
}

std::string assistant::streaming_for_type(const yarn::name& n,
    const std::string& s) const {

    const auto ssbid(context_.streaming_annotations_repository().by_id());
    const auto i(ssbid.find(n.id()));
    if (i == ssbid.end())
        return s;

    return streaming_for_type(i->second, s);
}

std::string assistant::
streaming_for_type(const formattables::helper_descriptor& hd,
    const std::string& s) const {

    const auto ss(hd.streaming_annotations());
    if (!ss)
        return s;

    return streaming_for_type(*ss, s);
}

bool assistant::
requires_hashing_helper_method(const yarn::attribute& attr) const {
    for (const auto& hp : context_.element_properties().helper_properties()) {
        const auto ident(attr.parsed_type().identifiable());
        const auto& desc(hp.current());
        if (ident != desc.name_tree_identifiable())
            continue;

        if (desc.requires_hashing_helper())
            return true;
    }
    return false;
}

boost::shared_ptr<annotations::odb_annotations> assistant::
get_odb_annotations(const std::unordered_map<std::string,
    boost::shared_ptr<quilt::cpp::annotations::opaque_annotations>
    >& os) const {
    const auto fn(odb::traits::class_header_formatter_name());
    const auto i(os.find(fn));
    if (i == os.end())
        return boost::shared_ptr<annotations::odb_annotations>();

    auto r(boost::dynamic_pointer_cast<annotations::odb_annotations>(i->second));
    if (!r) {
        BOOST_LOG_SEV(lg, error) << unexpected_opaque_annotations;
        BOOST_THROW_EXCEPTION(formatting_error(unexpected_opaque_annotations));
    }
    return r;
}

boost::shared_ptr<annotations::odb_annotations>
assistant::get_odb_annotations() const {
    const auto& os(context_.element_annotations().opaque_annotations());
    return get_odb_annotations(os);
}

boost::shared_ptr<annotations::odb_annotations> assistant::
get_odb_annotations(const std::string& property_id) const {

    const auto& es(context_.element_annotations());
    const auto& osfp(es.opaque_annotations_for_property());
    const auto i(osfp.find(property_id));
    if (i == osfp.end())
        return boost::shared_ptr<annotations::odb_annotations>();

    const auto& os(i->second);
    return get_odb_annotations(os);
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

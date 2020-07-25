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
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/formatters/indent_filter.hpp"
#include "dogen.utility/types/formatters/comment_formatter.hpp"
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.logical/types/helpers/name_flattener.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.physical/hash/entities/element_archetype_hash.hpp"
#include "dogen.text/types/formatters/boilerplate_properties.hpp"
#include "dogen.text.cpp/io/formattables/streaming_properties_io.hpp"
#include "dogen.text.cpp/io/formattables/helper_properties_io.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/lexical_cast/traits.hpp"
#include "dogen.text.cpp/types/transforms/odb/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/tests/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.transforms.assistant"));

const std::string empty;
const std::string by_ref_text("&");
const std::string void_keyword_text("void");
const std::string final_keyword_text("final ");
const std::string override_keyword_text(" override");
const std::string noexcept_keyword_text(" noexcept");
const std::string namespace_separator("::");
const std::string member_variable_postfix("_");
const std::string underscore("_");
const std::string dot(".");

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool documenting_previous_identifier(true);

const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");
const std::string header_guard_not_set(
    "Header guard for formatter is not set. Formatter: ");
const std::string artefact_properties_missing(
    "Could not find formatter configuration for formatter: ");
const std::string facet_properties_missing(
    "Could not find facet configuration for formatter: ");
const std::string facet_directory_missing(
    "Facet directory is missing for facet: ");
const std::string element_not_found("Element not found: ");
const std::string no_helpers_for_family("No helpers found for family: ");
const std::string helpless_family("No registered helpers found for family: ");

}

namespace dogen::text::cpp::transforms {

assistant::assistant(const context& ctx, const logical::entities::element& e,
    const physical::entities::meta_name& pmn, const bool requires_header_guard,
    physical::entities::artefact& a)
    : element_(e), context_(ctx), artefact_(a),
      artefact_properties_(
        obtain_artefact_properties(element_.name().qualified().dot(),
            pmn.qualified())),
      physical_meta_name_(pmn), requires_header_guard_(requires_header_guard) {

    BOOST_LOG_SEV(lg, debug) << "Processing element: "
                             << element_.name().qualified().dot()
                             << " for archetype: "
                             << physical_meta_name_.qualified();

    utility::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);

    validate();
}

void assistant::validate() const {
    const auto& fn(physical_meta_name_.qualified());
    const auto& fp(artefact_properties_);
    if (fp.file_path().empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(file_path_not_set + fn));
    }

    if (!requires_header_guard_)
        return;

    if (fp.header_guard().empty()) {
        BOOST_LOG_SEV(lg, error) << header_guard_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(header_guard_not_set + fn));
    }
}

std::string assistant::
make_final_keyword_text(const logical::entities::structural::object& o) const {
    if (is_cpp_standard_98())
        return empty;

    return o.is_final() ? final_keyword_text : empty;
}

std::string assistant::make_override_keyword_text() const {
    if (is_cpp_standard_98())
        return empty;

    return override_keyword_text;
}

std::string assistant::make_noexcept_keyword_text() const {
    if (is_cpp_standard_98())
        return empty;

    return noexcept_keyword_text;
}

std::string
assistant::make_by_ref_text(const logical::entities::attribute& attr) {
    return attr.parsed_type().is_current_simple_type() ? empty : by_ref_text;
}

std::string assistant::
make_setter_return_type(const std::string& containing_type_name,
    const logical::entities::attribute& attr) {

    std::ostringstream s;
    if (attr.is_fluent())
        s << containing_type_name << by_ref_text;
    else
        s << void_keyword_text;

    return s.str();
}

std::string
assistant::get_qualified_name(const logical::entities::name& n) const {
    return n.qualified().colon();
}

std::string
assistant::get_qualified_name(const logical::entities::name_tree& nt) const {
    return nt.qualified().colon();
}

std::string
assistant::get_qualified_namespace(const logical::entities::name& n) const {
    const auto& l(n.location());
    auto ns(l.external_modules());
    for (const auto& m : l.model_modules())
        ns.push_back(m);

    for (const auto& m : l.internal_modules())
        ns.push_back(m);

    using boost::algorithm::join;
    const auto r(join(n.location().model_modules(), namespace_separator));
    return r;
}

std::string assistant::
get_identifiable_model_name(const logical::entities::name& n) const {
    using boost::algorithm::join;
    return join(n.location().model_modules(), underscore);
}

std::string assistant::
get_dot_separated_model_name(const logical::entities::name& n) const {
    using boost::algorithm::join;
    return join(n.location().model_modules(), dot);
}

std::string
assistant::get_product_name(const logical::entities::name& n) const {
    if (n.location().external_modules().empty())
        return empty;

    return n.location().external_modules().front();
}

const formattables::element_properties& assistant::obtain_element_properties(
    const std::string& element_id) const {

    if (element_id == element_.name().qualified().dot())
        return context_.element_properties();

    const auto& formattables(context_.model().formattables());
    const auto i(formattables.find(element_id));
    if (i == formattables.end()) {
        BOOST_LOG_SEV(lg, error) << element_not_found << element_id;
        BOOST_THROW_EXCEPTION(formatting_error(element_not_found + element_id));
    }
    return i->second.element_properties();
}

const formattables::artefact_properties& assistant::obtain_artefact_properties(
    const std::string& element_id, const std::string& archetype) const {

    const auto& eprops(obtain_element_properties(element_id));
    const auto i(eprops.artefact_properties().find(archetype));
    if (i == eprops.artefact_properties().end()) {
        BOOST_LOG_SEV(lg, error) << artefact_properties_missing
                                 << archetype;
        BOOST_THROW_EXCEPTION(
            formatting_error(artefact_properties_missing + archetype));
    }
    return i->second;
}

formattables::facet_properties assistant::
obtain_facet_properties(const std::string& facet_name) const {
    const auto& fct_props(context_.model().facet_properties());
    const auto i(fct_props.find(facet_name));
    if (i == fct_props.end()) {
        BOOST_LOG_SEV(lg, error) << facet_properties_missing
                                 << facet_name;
        BOOST_THROW_EXCEPTION(formatting_error(facet_properties_missing +
                facet_name));
    }
    return i->second;
}

std::list<std::string>
assistant::make_namespaces(const logical::entities::name& n,
    const bool detect_model_name) const {
    logical::helpers::name_flattener nf(detect_model_name);
    return nf.flatten(n);
}

bool assistant::is_archetype_enabled(const std::string& archetype) const {
    physical::entities::element_archetype
        ea(element_.name().qualified().dot(), archetype);
    const auto& eafe(context_.enabled_archetype_for_element());
    const auto i(eafe.find(ea));
    const bool is_disabled(i == eafe.end());
    return !is_disabled;
}

bool assistant::is_facet_enabled(const std::string& facet) const {
    const auto& fct_props(obtain_facet_properties(facet));
    return fct_props.enabled();
}

std::string assistant::
get_facet_directory_for_facet(const std::string& facet_name) const {
    const auto& fct_props(obtain_facet_properties(facet_name));
    if (fct_props.directory().empty()) {
        BOOST_LOG_SEV(lg, error) << facet_directory_missing << facet_name;
        BOOST_THROW_EXCEPTION(
            formatting_error(facet_directory_missing + facet_name));
    }
    return fct_props.directory();
}

bool assistant::is_cpp_standard_98() const {
    using formattables::cpp_standards;
    return context_.model().cpp_standard() == cpp_standards::cpp_98;
}

bool assistant::is_cpp_standard_17() const {
    using formattables::cpp_standards;
    return context_.model().cpp_standard() == cpp_standards::cpp_17;
}

bool assistant::supports_defaulted_functions() const {
    return !is_cpp_standard_98();
}

bool assistant::requires_nested_namespaces() const {
    return is_cpp_standard_17();
}

bool assistant::requires_manual_default_constructor() const {
    const auto& ap(context_.element_properties().aspect_properties());

    /*
     * In C++ 98 we must always create a default constructor because
     * we cannot make use of the defaulted functions.
     */
    return is_cpp_standard_98() || ap.requires_manual_default_constructor();
}

bool assistant::supports_move_operator() const {
    return !is_cpp_standard_98();
}

bool assistant::requires_manual_move_constructor() const {
    const auto& ap(context_.element_properties().aspect_properties());

    /*
     * C++ 98 does not support move constructors.
     */
    return !is_cpp_standard_98() && ap.requires_manual_move_constructor();
}

bool assistant::requires_stream_manipulators() const {
    const auto& ap(context_.element_properties().aspect_properties());
    return ap.requires_stream_manipulators();
}

bool assistant::is_serialization_enabled() const {
    using transforms::serialization::traits;
    return is_archetype_enabled(traits::canonical_archetype());
}

bool assistant::is_io_enabled() const {
    using transforms::io::traits;
    return is_archetype_enabled(traits::canonical_archetype());
}

bool assistant::is_lexical_cast_enabled() const {
    using transforms::lexical_cast::traits;
    return is_archetype_enabled(traits::canonical_archetype());
}

bool assistant::is_odb_facet_enabled() const {
    using transforms::odb::traits;
    return is_facet_enabled(traits::facet_qn());
}

bool assistant::is_tests_enabled() const {
    using transforms::tests::traits;
    return is_facet_enabled(traits::facet_qn());
}

bool assistant::is_hash_enabled() const {
    using transforms::hash::traits;
    return is_archetype_enabled(traits::canonical_archetype());
}

bool assistant::is_test_data_enabled() const {
    using transforms::test_data::traits;
    return is_facet_enabled(traits::facet_qn());
}

text::formatters::scoped_boilerplate_formatter assistant::
make_scoped_boilerplate_formatter(const logical::entities::element& e,
    const logical::entities::technical_space ts) {
    text::formatters::boilerplate_properties bp;

    const auto& art_props(artefact_properties_);
    bp.dependencies(art_props.inclusion_dependencies());
    bp.header_guard(art_props.header_guard());
    bp.technical_space(ts);
    const auto i(e.decoration().find(ts));
    if (i != e.decoration().end() && i->second) {
        const auto dec(*i->second);
        bp.preamble(dec.preamble());
        bp.postamble(dec.postamble());
    }
    bp.generate_preamble(true);
    bp.generate_header_guards(true);

    using text::formatters::scoped_boilerplate_formatter;
    return scoped_boilerplate_formatter(stream(), bp);
}

text::formatters::scoped_namespace_formatter
assistant::make_scoped_namespace_formatter(const std::list<std::string>& ns) {
    return text::formatters::scoped_namespace_formatter(
        stream(), logical::entities::technical_space::cpp,
        ns, true/*add_new_line*/, requires_nested_namespaces());
}

void assistant::make_decoration_preamble(const logical::entities::element& e,
    const logical::entities::technical_space ts) {

    const auto i(e.decoration().find(ts));
    if (i != e.decoration().end() && i->second) {
        const auto dec(*i->second);
        stream() << dec.preamble();
    }
}

void assistant::comment(const std::string& c) {
    if (c.empty())
        return;

    utility::formatters::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        utility::formatters::comment_style::c_style,
        !last_line_is_blank);
    f.format(stream(), c);
}

void assistant::
comment_start_method_group(const std::string& documentation,
    const bool add_comment_blocks) {
    if (documentation.empty())
        return;

    {
        utility::formatters::positive_indenter_scope pis(stream());
        utility::formatters::comment_formatter f(
            !start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            utility::formatters::comment_style::c_style,
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
        utility::formatters::positive_indenter_scope pis(stream());
        utility::formatters::comment_formatter f(
            start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            utility::formatters::comment_style::c_style,
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
    utility::formatters::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        documenting_previous_identifier,
        utility::formatters::comment_style::cpp_style,
        !last_line_is_blank);

    f.format(s, c);
    return s.str();
}

std::list<std::shared_ptr<transforms::helper_transform>>
assistant::get_helpers(const formattables::helper_properties& hp) const {
    /*
     * A family must have at least one helper registered. This is a
     * good way to detect spurious families in data files.
     */
    const auto fam(hp.current().family());
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
    const auto j(i->second.find(physical_meta_name_.qualified()));
    if (j != i->second.end()) {
        BOOST_LOG_SEV(lg, debug) << "Found helpers for formatter: "
                                 << physical_meta_name_.qualified();
        return j->second;
    }

    BOOST_LOG_SEV(lg, debug) << "Could not find helpers for formatter:"
                             << physical_meta_name_.qualified();
    return std::list<std::shared_ptr<transforms::helper_transform>>();
}

bool assistant::is_io() const {
    const auto fn(physical_meta_name_.location().facet());
    return transforms::io::traits::facet_sn()  == fn;
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
    using tt = transforms::types::traits;
    const auto cifn(tt::class_implementation_archetype_qn());
    const auto arch(physical_meta_name_.qualified());
    bool in_types_class_implementation(arch == cifn);
    return in_types_class_implementation && hp.in_inheritance_relationship();
}

void assistant::add_helper_methods(const std::string& element_id) {
    BOOST_LOG_SEV(lg, debug) << "Generating helper methods. Element: "
                             << element_id;

    if (context_.element_properties().helper_properties().empty())
        BOOST_LOG_SEV(lg, debug) << "No helper methods found.";

    const auto& eprops(context_.element_properties());
    for (const auto& hlp_props : eprops.helper_properties()) {
        BOOST_LOG_SEV(lg, debug) << "Helper configuration: " << hlp_props;
        const auto helpers(get_helpers(hlp_props));

        /*
         * Check to see if the helper is enabled, given the system's
         * current configuration. If enabled, format it.
         */
        for (const auto& hlp : helpers) {
            const auto id(hlp->id());
            if (!hlp->is_enabled(*this, hlp_props)) {
                BOOST_LOG_SEV(lg, debug) << "Helper is not enabled." << id;
                continue;
            }

            BOOST_LOG_SEV(lg, debug) << "Transforming with helper: " << id;
            hlp->apply(*this, hlp_props);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished generating helper methods.";
}

std::string assistant::
streaming_for_type(const formattables::streaming_properties& sp,
    const std::string& s) const {

    std::ostringstream stream;
    utility::formatters::utility_formatter uf(stream);
    BOOST_LOG_SEV(lg, debug) << "Streaming properties for type: " << sp;
    if (sp.remove_unprintable_characters())
        uf.insert_streamed("tidy_up_string(" + s + ")");
    else if (!sp.string_conversion_method().empty()) {
        // FIXME: hack to determine if we are being dereferenced.
        std::string s1(s);
        const auto i(s1.find('*'));
        if (i != std::string::npos)
            s1 = "(" + s + ")";
        uf.insert_streamed(s1 + "." + sp.string_conversion_method());
    } else if (sp.requires_quoting())
        uf.insert_streamed(s);
    else
        uf.insert(s);

    return stream.str();
}

std::string assistant::streaming_for_type(const logical::entities::name& n,
    const std::string& s) const {

    const auto str_propss(context_.model().streaming_properties());
    const auto i(str_propss.find(n.qualified().dot()));
    if (i == str_propss.end())
        return s;

    return streaming_for_type(i->second, s);
}

std::string assistant::
streaming_for_type(const formattables::helper_descriptor& hd,
    const std::string& s) const {

    const auto sp(hd.streaming_properties());
    if (!sp)
        return s;

    return streaming_for_type(*sp, s);
}

bool assistant::requires_hashing_helper_method(
    const logical::entities::attribute& attr) const {
    const auto& eprops(context_.element_properties());
    for (const auto& hlp_props : eprops.helper_properties()) {
        const auto ident(attr.parsed_type().qualified().identifiable());
        const auto& desc(hlp_props.current());
        if (ident != desc.name_tree_identifiable())
            continue;

        if (desc.requires_hashing_helper())
            return true;
    }
    return false;
}

std::list<logical::entities::name> assistant::
names_with_enabled_archetype(const std::string& archetype,
    const std::list<logical::entities::name> names) const {
    std::list<logical::entities::name> r;
    for (const auto& n : names) {
        const auto id(n.qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Checking enablement for name: " << id;

        physical::entities::element_archetype ea(id, archetype);
        const auto& eafe(context_.enabled_archetype_for_element());
        const auto i(eafe.find(ea));
        const bool is_disabled(i == eafe.end());
        if (is_disabled)
            continue;

        r.push_back(n);
    }
    return r;
}

const formattables::artefact_properties&
assistant::artefact_properties() const {
    return artefact_properties_;
}

std::ostream& assistant::stream() {
    return filtering_stream_;
}

void assistant::update_artefact() const {
    const auto fp(artefact_properties_.file_path());
    artefact_.name().simple(fp.filename().generic_string());
    artefact_.name().qualified(fp);
    artefact_.content(stream_.str());

    const auto& ap(artefact_.artefact_properties());
    artefact_.overwrite(ap.overwrite());

    physical::entities::operation op;
    using ot = physical::entities::operation_type;
    op.type(artefact_.overwrite() ? ot::write : ot::create_only);
    artefact_.operation(op);
}

}

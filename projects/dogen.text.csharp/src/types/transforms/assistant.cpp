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
#include <cctype>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/formatters/indent_filter.hpp"
#include "dogen.utility/types/formatters/comment_formatter.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/logical_name_flattener.hpp"
#include "dogen.text/types/formatters/boilerplate_properties.hpp"
#include "dogen.logical/io/entities/helper_properties_io.hpp"
#include "dogen.text.csharp/types/transforms/formatting_error.hpp"
#include "dogen.text/types/transforms/helper_chain.hpp"
#include "dogen.text.csharp/types/transforms/assistant.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.csharp.transforms.assistant"));

const std::string empty;
const bool start_on_first_line(true);
const std::string sealed_keyword_text("sealed ");
const std::string abstract_keyword_text("abstract ");
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool documenting_previous_identifier(true);

const std::string default_family("Default");
const std::string static_reference_equals("object");
const std::string no_helpers_for_family("No helpers found for family: ");
const std::string helpless_family("No registered helpers found for family: ");
const std::string attribute_with_no_simple_name(
    "Attribute has empty simple name.");

}

namespace dogen::text::csharp::transforms {

assistant::
assistant(const context& ctx, const logical::entities::element& e,
    const identification::entities::physical_meta_name& pmn,
    physical::entities::artefact& a) :
    element_(e), artefact_(a), context_(ctx), physical_meta_name_(pmn) {

    BOOST_LOG_SEV(lg, debug) << "Processing element: "
                             << element_.name().id()
                             << " for archetype: "
                             << physical_meta_name_.id();

    utility::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);
}

std::string assistant::get_qualified_name(
    const identification::entities::logical_name& n) const {
    return n.qualified().dot();
}

std::string assistant::get_qualified_name(
    const identification::entities::logical_name_tree& nt) const {
    return nt.qualified().dot();
}

std::string assistant::
make_inheritance_keyword_text(const logical::entities::structural::object& o) {
    if (o.is_parent())
        return abstract_keyword_text;

    return o.is_final() ? sealed_keyword_text : empty;
}

text::formatters::scoped_boilerplate_formatter assistant::
make_scoped_boilerplate_formatter(const logical::entities::element& e,
    const identification::entities::technical_space ts) {
    text::formatters::boilerplate_properties bp;

    bp.technical_space(ts);
    const auto i(e.decoration().find(ts));
    if (i != e.decoration().end() && i->second) {
        const auto dec(*i->second);
        bp.preamble(dec.preamble());
        bp.postamble(dec.postamble());
    }
    bp.generate_preamble(true);

    using text::formatters::scoped_boilerplate_formatter;
    return scoped_boilerplate_formatter(stream(), bp);

}

text::formatters::scoped_namespace_formatter
assistant::make_scoped_namespace_formatter(const std::list<std::string>& ns) {
    return text::formatters::scoped_namespace_formatter(
        stream(), identification::entities::technical_space::csharp, ns,
        true/*add_new_line*/);
}

std::list<std::string> assistant::
make_namespaces(const identification::entities::logical_name& n) const {
    identification::helpers::logical_name_flattener nf;
    return nf.flatten(n);
}

std::string
assistant::reference_equals(const logical::entities::attribute& attr) const {
    const auto& c(context_.model().logical().aspect_properties());
    const auto n(attr.parsed_type().current());
    const auto i(c.find(n.id()));

    bool requires_static_reference_equals(i == c.end() ?
        false : i->second.requires_static_reference_equals());

    if (requires_static_reference_equals)
        return static_reference_equals;

    return attr.name().simple();
}

void assistant::
comment(const std::string& c, const unsigned int identation_level) {
    if (c.empty())
        return;

    for (unsigned int i = 0; i < identation_level; ++i)
        stream() << utility::formatters::indent_in;

    utility::formatters::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        utility::formatters::comment_style::csharp_style,
        !last_line_is_blank);
    f.format(stream(), c);

    for (unsigned int i = 0; i < identation_level; ++i)
        stream() << utility::formatters::indent_out;
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
        utility::formatters::comment_style::csharp_style,
        !last_line_is_blank);

    f.format(s, c);
    return s.str();
}

std::string assistant::
make_argument_name(const logical::entities::attribute& attr) const {
    auto r(attr.name().simple());
    if (r.empty()) {
        BOOST_LOG_SEV(lg, error) << attribute_with_no_simple_name;
        BOOST_THROW_EXCEPTION(formatting_error(attribute_with_no_simple_name));
    }

    r[0] = static_cast<char>(std::tolower(r[0]));
    return r;
}

std::list<std::shared_ptr<text::transforms::helper_transform>>
assistant::get_helpers(const logical::entities::helper_properties& hp) const {
    const auto fam(hp.current().family());

    /*
     * Bit of a hack: we manually ignore the "Default" family. This is
     * a quick way to solve a mismatch between C# and C++: in C++ we
     * need a helper for all domain types, but not so in C#.
     */
    if (fam != default_family) {
        /*
         * A family must have at least one helper registered. This is a
         * good way to detect spurious families in data files.
         */
        const auto i(context_.helpers().find(fam));
        if (i == context_.helpers().end()) {
            BOOST_LOG_SEV(lg, error) << no_helpers_for_family << fam;
            BOOST_THROW_EXCEPTION(
                formatting_error(no_helpers_for_family + fam));
        }
        BOOST_LOG_SEV(lg, debug) << "Found helpers for family: " << fam;

        /*
         * Not all formatters need help, so its fine not to have a
         * helper registered against a particular formatter.
         */
        const auto j(i->second.find(physical_meta_name_.id()));
        if (j != i->second.end()) {
            BOOST_LOG_SEV(lg, debug) << "Found helpers for formatter: "
                                     << physical_meta_name_.id();
            return j->second;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Could not find helpers for formatter:"
                             << physical_meta_name_.id();
    return std::list<std::shared_ptr<text::transforms::helper_transform>>();
}

boost::optional<logical::entities::assistant_properties> assistant::
get_assistant_properties(const logical::entities::attribute& attr) const {
    const auto& ap(context_.model().logical().assistant_properties());
    const auto i(ap.find(attr.parsed_type().current().id()));
    if (i == ap.end())
        return boost::optional<logical::entities::assistant_properties>();

    return i->second;
}

void assistant::add_helper_methods(const std::string& /*element_id*/) {
    dogen::text::transforms::helper_chain::model_ =
        &context_.model().physical();
    dogen::text::transforms::helper_chain::apply(stream(),
        context_.model().logical(), element_, artefact_);

    // BOOST_LOG_SEV(lg, debug) << "Generating helper methods. Element: "
    //                          << element_id;

    // if (element_.helper_properties().empty())
    //     BOOST_LOG_SEV(lg, debug) << "No helper methods found.";

    // bool has_helpers(false);
    // for (const auto& hlp_props : element_.helper_properties()) {
    //     BOOST_LOG_SEV(lg, debug) << "Helper configuration: " << hlp_props;
    //     const auto helpers(get_helpers(hlp_props));

    //     for (const auto& hlp : helpers) {
    //         if (!has_helpers) {
    //             has_helpers = true;
    //             stream() << "        #region Helpers" << std::endl;
    //         }

    //         BOOST_LOG_SEV(lg, debug) << "Formatting with helper: " << hlp->id();
    //         hlp->apply(stream(), context_.model().logical(), hlp_props);
    //     }
    // }

    // if (has_helpers) {
    //     stream() << "        #endregion" << std::endl << std::endl;
    //     has_helpers = false;
    // }

    // BOOST_LOG_SEV(lg, debug) << "Finished generating helper methods.";
}

std::ostream& assistant::stream() {
    return filtering_stream_;
}

void assistant::update_artefact() {
    artefact_.content(stream_.str());

    const auto fp(artefact_.path_properties().file_path());
    artefact_.file_path(fp);

    const auto arch(physical_meta_name_.id());

    physical::entities::operation op;
    using ot = physical::entities::operation_type;
    const bool overwrite(artefact_.enablement_properties().overwrite());
    op.type(overwrite ? ot::write : ot::create_only);
    artefact_.operation(op);
}

}

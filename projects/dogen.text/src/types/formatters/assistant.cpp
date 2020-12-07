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
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/formatters/indent_filter.hpp"
#include "dogen.identification/types/entities/technical_space_version.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/entities/logical_name_tree.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.text/types/formatters/formatting_error.hpp"
#include "dogen.text/types/formatters/assistant.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.formatters.assistant"));

const std::string empty;
const std::string by_ref_text("&");
const std::string void_keyword_text("void");
const std::string final_keyword_text("final ");
const std::string override_keyword_text(" override");
const std::string noexcept_keyword_text(" noexcept");
const std::string namespace_separator("::");
const std::string underscore("_");
const std::string dot(".");

const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");
const std::string header_guard_not_set(
    "Header guard for formatter is not set. Formatter: ");
const std::string facet_properties_missing(
    "Could not find facet configuration for formatter: ");
const std::string facet_directory_missing(
    "Facet directory is missing for facet: ");

}

namespace dogen::text::formatters {

using physical::entities::artefact;
using identification::entities::logical_name;
using identification::entities::logical_name_tree;
using identification::entities::technical_space_version;

assistant::assistant(const text::entities::model& lps,
    const logical::entities::element& e, artefact& a,
    const bool requires_header_guard)
    : element_(e), lps_(lps), artefact_(a),
      requires_header_guard_(requires_header_guard) {

    BOOST_LOG_SEV(lg, debug) << "Processing element: "
                             << element_.name().qualified().dot()
                             << " for archetype: "
                             << a.meta_name().id();

    utility::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);

    validate();
}

void assistant::validate() const {
    const auto& pmn(artefact_.meta_name().id());
    const auto& pp(artefact_.path_properties());
    const auto fp(pp.file_path());
    if (fp.empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << pmn;
        BOOST_THROW_EXCEPTION(
            formatting_error(file_path_not_set + pmn.value()));
    }

    if (!requires_header_guard_)
        return;

    const auto& hg(pp.header_guard());
    if (hg.empty()) {
        BOOST_LOG_SEV(lg, error) << header_guard_not_set << pmn;
        BOOST_THROW_EXCEPTION(
            formatting_error(header_guard_not_set + pmn.value()));
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
assistant::get_qualified_name(const logical_name& n) const {
    return n.qualified().colon();
}

std::string
assistant::get_qualified_name(const logical_name_tree& nt) const {
    return nt.qualified().colon();
}

std::string
assistant::get_qualified_namespace(const logical_name& n) const {
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
get_identifiable_model_name(const logical_name& n) const {
    using boost::algorithm::join;
    return join(n.location().model_modules(), underscore);
}

std::string assistant::
get_dot_separated_model_name(const logical_name& n) const {
    using boost::algorithm::join;
    return join(n.location().model_modules(), dot);
}

std::string
assistant::get_product_name(const logical_name& n) const {
    if (n.location().external_modules().empty())
        return empty;

    return n.location().external_modules().front();
}

physical::entities::facet_properties assistant::obtain_facet_properties(
    const identification::entities::physical_meta_id& facet_name) const {
    const auto& mmp(lps_.physical().meta_model_properties());
    const auto& fct_props(mmp.facet_properties());
    const auto i(fct_props.find(facet_name));
    if (i == fct_props.end()) {
        BOOST_LOG_SEV(lg, error) << facet_properties_missing
                                 << facet_name;
        BOOST_THROW_EXCEPTION(formatting_error(facet_properties_missing +
                facet_name.value()));
    }
    return i->second;
}

bool assistant::is_archetype_enabled(
    const identification::entities::physical_meta_id& archetype) const {
    identification::entities::logical_id lid(element_.name().qualified().dot());
    identification::entities::logical_meta_physical_id ea(lid, archetype);
    const auto& mmp(lps_.physical().meta_model_properties());
    const auto& eafe(mmp.enabled_archetype_for_element());
    const auto i(eafe.find(ea));
    const bool is_disabled(i == eafe.end());
    return !is_disabled;
}

bool assistant::is_facet_enabled(
    const identification::entities::physical_meta_id& facet) const {
    const auto& fct_props(obtain_facet_properties(facet));
    return fct_props.enabled();
}

std::string assistant::get_facet_directory_for_facet(
    const identification::entities::physical_meta_id& facet_name) const {
    const auto& fct_props(obtain_facet_properties(facet_name));
    if (fct_props.directory_name().empty()) {
        BOOST_LOG_SEV(lg, error) << facet_directory_missing << facet_name;
        BOOST_THROW_EXCEPTION(
            formatting_error(facet_directory_missing + facet_name.value()));
    }
    return fct_props.directory_name();
}

bool assistant::is_cpp_standard_98() const {
    const auto tsv(lps_.logical().technical_space_version());
    return tsv == technical_space_version::cpp_98;
}

bool assistant::is_cpp_standard_17() const {
    const auto tsv(lps_.logical().technical_space_version());
    return tsv == technical_space_version::cpp_17;
}

bool assistant::supports_defaulted_functions() const {
    return !is_cpp_standard_98();
}

bool assistant::requires_nested_namespaces() const {
    return is_cpp_standard_17();
}

bool assistant::requires_manual_default_constructor() const {
    /*
     * We are only interested in objects or primitives; all other
     * element types do not need aspect properties.
     */
    using logical::entities::structural::object;
    const auto optr(dynamic_cast<const object*>(&element_));
    using logical::entities::structural::primitive;
    const auto pptr(dynamic_cast<const primitive*>(&element_));

    if (optr != nullptr) {
        return optr->technical_space_properties().
            requires_manual_default_constructor();
    } else if (pptr != nullptr) {
        return pptr->technical_space_properties().
            requires_manual_default_constructor();
    }
    return false;
}

bool assistant::supports_move_operator() const {
    return !is_cpp_standard_98();
}


}

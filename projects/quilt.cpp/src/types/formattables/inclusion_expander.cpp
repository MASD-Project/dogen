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
#include <typeindex>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/annotations/types/field_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.inclusion_directives_repository_factory"));

const char angle_bracket('<');
const std::string double_quote("\"");
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

const std::string duplicate_element_name("Duplicate delement name: ");
const std::string missing_formatter_name("Formatter name not found: ");
const std::string empty_include_directive("Include directive is empty.");
const std::string formatter_not_found_for_type(
    "Formatter not found for type: ");
const std::string empty_formatter_name("Formatter name is empty.");

bool include_directive_comparer(
    const std::string& lhs, const std::string& rhs) {

    if (lhs.empty() || rhs.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_include_directive;
        using dogen::quilt::cpp::formattables::expansion_error;
        BOOST_THROW_EXCEPTION(expansion_error(empty_include_directive));
    }

    const bool lhs_has_angle_brackets(lhs[0] == angle_bracket);
    const bool rhs_has_angle_brackets(rhs[0] == angle_bracket);

    if (lhs_has_angle_brackets && !rhs_has_angle_brackets)
        return true;

    if (!lhs_has_angle_brackets && rhs_has_angle_brackets)
        return false;

    if (lhs_has_angle_brackets && rhs_has_angle_brackets) {
        const auto npos(std::string::npos);
        const bool lhs_is_boost(lhs.find_first_of(boost_name) != npos);
        const bool rhs_is_boost(rhs.find_first_of(boost_name) != npos);
        if (!lhs_is_boost && rhs_is_boost)
            return false;

        if (lhs_is_boost && !rhs_is_boost)
            return true;

        // FIXME: hacks for headers that must be last
        const bool lhs_is_gregorian(
            lhs.find_first_of(boost_serialization_gregorian) != npos);
        const bool rhs_is_gregorian(
            rhs.find_first_of(boost_serialization_gregorian) != npos);
        if (lhs_is_gregorian && !rhs_is_gregorian)
            return true;

        if (!lhs_is_gregorian && rhs_is_gregorian)
            return false;
    }

    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();

    return lhs < rhs;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::ostream& operator<<(std::ostream& s,
    const inclusion_expander::formattater_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "inclusion_expander::formatters_type_group\"" << ", "
      << "\"inclusion_directive\": " << v.inclusion_directive << ", "
      << "\"inclusion_directive\": " << v.inclusion_directive
      << " }";

    return s;
}

std::ostream& operator<<(std::ostream& s,
    const inclusion_expander::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "inclusion_expander::type_group\"" << ", "
      << "\"inclusion_required\": " << v.inclusion_required << ", "
      << "\"formattaters_type_group\": "
      << v.formattaters_type_group
      << " }";

    return s;
}

inclusion_expander::type_group inclusion_expander::
make_type_group(const annotations::type_repository& atrp,
    const formatters::container& fc) const {
    BOOST_LOG_SEV(lg, debug) << "Creating field definitions.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    const auto ir(traits::cpp::inclusion_required());
    r.inclusion_required = s.select_type_by_name(ir);

    for (const auto f : fc.file_formatters()) {
        const auto& oh(f->ownership_hierarchy());
        const auto fmtn(oh.formatter_name());

        using formatters::inclusion_support_types;
        static const auto ns(inclusion_support_types::not_supported);
        if (f->inclusion_support_type() == ns) {
            BOOST_LOG_SEV(lg, debug) << "Skipping formatter: " << fmtn;
            continue;
        }

        formattater_type_group ftg;
        const auto& id(traits::inclusion_directive());
        ftg.inclusion_directive = s.select_type_by_name(fmtn, id);

        // note: redefinition by design as scopes are different.
        const auto& ir(traits::inclusion_required());
        ftg.inclusion_required = s.select_type_by_name(fmtn, ir);
        r.formattaters_type_group[fmtn] = ftg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created field definitions. Result: " << r;
    return r;
}

bool inclusion_expander::make_top_level_inclusion_required(
    const type_group& tg, const annotations::annotation& o) const {
    const annotations::type_selector s(o);
    return s.get_boolean_content_or_default(tg.inclusion_required);
}

inclusion_directive_configuration
inclusion_expander::make_inclusion_directive_configuration(
    const type_group& tg,const std::string& formatter_name,
    const annotations::annotation& o) const {

    if (formatter_name.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_formatter_name;
        BOOST_THROW_EXCEPTION(expansion_error(empty_formatter_name));
    }

    const auto i(tg.formattaters_type_group.find(formatter_name));
    if (i == tg.formattaters_type_group.end()) {
        BOOST_LOG_SEV(lg, error) << missing_formatter_name;
        BOOST_THROW_EXCEPTION(expansion_error(missing_formatter_name));
    }

    const auto& ft(i->second);
    const annotations::type_selector s(o);
    inclusion_directive_configuration r;

    const auto& ir(ft.inclusion_required);
    r.inclusion_required(s.get_boolean_content_or_default(ir));

    const auto id(ft.inclusion_directive);
    if (s.has_field(id))
        r.inclusion_directive(s.get_text_content(id));

    return r;
}

inclusion_expander::formatter_list_type
inclusion_expander::
remove_non_includible_formatters(const formatter_list_type& formatters) const {
    formatter_list_type r;
    using formatters::inclusion_support_types;
    static const auto ns(inclusion_support_types::not_supported);
    for (const auto& f : formatters) {
        if (f->inclusion_support_type() != ns)
            r.push_front(f);
    }
    return r;
}

std::unordered_map<std::type_index, inclusion_expander::formatter_list_type>
inclusion_expander::includible_formatters_by_type_index(
    const formatters::container& fc) const {

    std::unordered_map<std::type_index, formatter_list_type> r;
    for (const auto& pair : fc.file_formatters_by_type_index()) {
        const auto& ti(pair.first);
        const auto& fmts(pair.second);
        r[ti] = remove_non_includible_formatters(fmts);
    }
    return r;
}

std::string inclusion_expander::
to_inclusion_directive(const boost::filesystem::path& p) const {
    std::ostringstream ss;
    ss << double_quote << p.generic_string() << double_quote;
    return ss.str();
}

void inclusion_expander::insert_inclusion_directive(const std::string& id,
    const std::string& formatter_name, const std::string& directive,
    inclusion_directives_container_type& idc) const {

    if (directive.empty()) {
        std::ostringstream s;
        s << empty_include_directive << formatter_name << " for type: " << id;

        const auto msg(s.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(expansion_error(msg));
    }

    const auto fn_dir(std::make_pair(formatter_name, directive));
    const auto inserted(idc[id].insert(fn_dir).second);
    if (inserted)
        return;

    BOOST_LOG_SEV(lg, error) << duplicate_element_name << id;
    BOOST_THROW_EXCEPTION(expansion_error(duplicate_element_name + id));
}

void inclusion_expander::compute_inclusion_directives(
    const type_group& tg, const yarn::element& e,
    const formatter_list_type& formatters, const locator& l,
    inclusion_directives_container_type& idc) const {

    const auto& n(e.name());
    const auto id(n.id());

    /*
     * First we extract the data required to generated include
     * directives for this element. Note that we generate this setting
     * for _all elements_ even if the user did not specify any
     * meta-data (we do so via defaults).
     *
     * The question we are asking is: "does this element require any
     * inclusion directives at all, across all facets?". Not all
     * elements do; for example bool, int and so on don't require any
     * inclusions at all across all facets. If the user did not
     * override this, we default it to true because normally elements
     * require inclusion.
     */
    const auto& o(e.annotation());
    const bool required(make_top_level_inclusion_required(tg, o));
    if (!required) {
        BOOST_LOG_SEV(lg, debug) << "Inclusion not required for element.";
        return;
    }

    /*
     * Now we start working at the formatter level.
     */
    for (const auto& fmt : formatters) {
        const auto fmtn(fmt->ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatter: " << fmtn;

        /*
         * Does the type require an inclusion directive for this
         * specific formatter? Some types require inclusion directives
         * for some formatters, but not for others. For example, we
         * may need an include for serialising a std::list, but in
         * test data we make use of helpers and thus do not require an
         * include.
         *
         * Again, we default this to true.
         */
        const auto id_cfg(make_inclusion_directive_configuration(tg, fmtn, o));
        if (!id_cfg.inclusion_required()) {
            BOOST_LOG_SEV(lg, debug) << "Inclusion directive not required "
                                     << " for formatter: " << fmtn;
            continue;
        }

        /*
         * Does the configuration provide a "hard-coded" inclusion
         * directive?  That is, the type had an hard-coded incantation
         * for its include. This is the case for system models such as
         * boost, std etc where we can't compute the inclusion
         * directive.
         */
        std::string directive;
        if (!id_cfg.inclusion_directive().empty())
            directive = id_cfg.inclusion_directive();
        else {
            /*
             * Finally, we have no alternative but to compute the
             * inclusion directive.
             */
            const auto path(fmt->inclusion_path(l, n));
            directive = to_inclusion_directive(path);
        }

        BOOST_LOG_SEV(lg, debug) << "Inclusion directive: " << directive;
        insert_inclusion_directive(id, fmtn, directive, idc);
    }
}

inclusion_expander::inclusion_directives_container_type inclusion_expander::
compute_inclusion_directives(const type_group& tg,
    const formatters::container& fc, const locator& l,
    const std::unordered_map<std::string, formattable>& formattables) const {

    inclusion_directives_container_type r;

    /*
     * First we must make sure we only have formatters which generate
     * files that can be included via an include directive. Filter out
     * all of those that do not, and bucket them all by type index.
     */
    const auto ffti(includible_formatters_by_type_index(fc));

    /*
     * Now, for all formattables and their associated element
     * segments, find the formatters that support the element segment
     * and compute the inclusion directive for it.
     */
    for (const auto& pair : formattables) {
        const auto& formattable(pair.second);

        for (const auto& segment : formattable.all_segments()) {
            const auto& e(*segment);
            const auto id(e.name().id());
            const auto ti(std::type_index(typeid(e)));

            const auto i(ffti.find(ti));
            if (i == ffti.end() || i->second.empty()) {
                BOOST_LOG_SEV(lg, debug) << formatter_not_found_for_type << id;
                continue;
            }

            compute_inclusion_directives(tg, e, i->second, l, r);
        }
    }
    return r;
}

inclusion_expander::element_inclusion_dependencies_type
inclusion_expander::compute_inclusion_dependencies(
    const formatters::container& fc,
    const inclusion_dependencies_builder_factory& idf,
    const yarn::element& e) const {

    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Creating inclusion dependencies for: " << id;

    element_inclusion_dependencies_type r;

    /*
     * First we must obtain all formatters for the type of element we
     * are building includes for. They may or may not exist in the
     * formatters' collection - for example, we do not have any
     * formatters for concepts at present. If so, we're done.
     *
     * Note also that we must query the formatters by type index
     * rather than use the formatter configuration container
     * directly. This is due to element segmentation, as we may have
     * more than one element associated with an id. To generate the
     * inclusion dependencies we must make sure we pick the pair of
     * element and the formatters that support it.
     */
    const auto ti(std::type_index(typeid(e)));
    const auto i(fc.file_formatters_by_type_index().find(ti));
    if (i == fc.file_formatters_by_type_index().end()) {
        BOOST_LOG_SEV(lg, debug) << "No formatters for type: " << ti.name();
        return r;
    }

    for (const auto fmt : i->second) {
        const auto fmtn(fmt->ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Providing for: " << fmtn;

        /*
         * Obtain the formatter's list of inclusion dependencies. If
         * none, we're done.
         */
        auto deps(fmt->inclusion_dependencies(idf, e));
        if (deps.empty())
            continue;

        /*
         * Ensure the dependencies are sorted according to a well
         * defined order and all duplicates are removed. Duplicates
         * arise because an element may refer to another element more
         * than once (e.g. list of T as well as vector of T).
         */
        deps.sort(include_directive_comparer);
        deps.unique();

        /*
         * Now slot in the results, ensuring our formatter name is
         * unique.
         * Now slot in the results. We have guaranteed in the
         * registrar that the formatter name is unique, so no need to
         * check.
         * remove this check.
         */
        r[fmtn] = deps;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies for: "
                             << id << ". Result: " << r;

    return r;
}

void inclusion_expander::populate_inclusion_dependencies(
    const formatters::container& fc,
    const inclusion_directives_container_type& idc,
    std::unordered_map<std::string, formattable>& formattables) const {

    BOOST_LOG_SEV(lg, debug) << "Creating inclusion dependencies "
                             << "for all formattables. ";
    inclusion_dependencies_builder_factory idf(idc, formattables);
    for (auto& pair : formattables) {
        const auto id(pair.first);
        auto& formattable(pair.second);

        /*
         * We need to compute the inclusion dependencies for each
         * segment of this element. By definition, the segments all
         * share the same element id so we can obtain a reference for
         * our container up front and populate it for each segment.
         */
        auto& eprops(formattable.element_properties());
        auto& fmt_props(eprops.formatter_properties());
        for (const auto& ptr : formattable.all_segments()) {
            const auto& e(*ptr);

            /*
             * We do not need to compute inclusion dependencies for
             * elements that are not part of the target model. However, we
             * do need them around for inclusion directives.
             */
            if (e.generation_type() == yarn::generation_types::no_generation)
                continue;

            /*
             * Compute the dependencies for this segment of the
             * element. If it does not have any dependencies, we
             * haven't got any work to do.
             */
            const auto deps(compute_inclusion_dependencies(fc, idf, e));
            if (deps.empty())
                continue;

            /*
             * Copy across all of the dependencies for the element,
             * across all supported formatters (that have inclusion
             * dependencies). Note that this caters of the
             * multi-segment elements, merging them all into a single
             * set of dependencies.
             */
            for (const auto& dep_pair : deps) {
                /*
                 * First we need to obtain the configuration for this
                 * formatter. It must have been initialised by the
                 * transformer.
                 */
                const auto fmtn(dep_pair.first);
                const auto i(fmt_props.find(fmtn));
                if (i == fmt_props.end()) {
                    BOOST_LOG_SEV(lg, error) << missing_formatter_name << fmtn;
                    BOOST_THROW_EXCEPTION(
                        expansion_error(missing_formatter_name + fmtn));
                }
                i->second.inclusion_dependencies(dep_pair.second);
            }
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies "
                             << "for all formattables. ";
}

void inclusion_expander::expand(const annotations::type_repository& atrp,
    const formatters::container& fc, const locator& l, model& fm) const {

    const auto tg(make_type_group(atrp, fc));
    const auto idc(compute_inclusion_directives(tg, fc, l, fm.formattables()));
    populate_inclusion_dependencies(fc, idc, fm.formattables());
}

} } } }

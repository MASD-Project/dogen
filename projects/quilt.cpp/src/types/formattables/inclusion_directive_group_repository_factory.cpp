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
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directive_group.hpp"
#include "dogen/quilt.cpp/io/formattables/inclusion_directive_group_io.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directive_group_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.inclusion_directives_repository_factory"));

const std::string double_quote("\"");
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

const std::string duplicate_element_name("Duplicate delement name: ");
const std::string missing_archetype("Archetype not found: ");
const std::string empty_primary_directive(
    "Primary include directive is empty.");
const std::string formatter_not_found_for_type(
    "Formatter not found for type: ");
const std::string empty_archetype("Formatter name is empty.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::ostream& operator<<(std::ostream& s,
    const inclusion_directive_group_repository_factory::
    formattater_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "inclusion_directive_group_repository_factory::formatters_type_group\""
      << ", "
      << "\"primary_inclusion_directive\": "
      << v.primary_inclusion_directive << ", "
      << "\"secondary_inclusion_directive\": "
      << v.secondary_inclusion_directive << ", "
      << "\"inclusion_required\": " << v.inclusion_required
      << " }";

    return s;
}

std::ostream& operator<<(std::ostream& s,
    const inclusion_directive_group_repository_factory::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "inclusion_directive_group_repository_factory::type_group\"" << ", "
      << "\"inclusion_required\": " << v.inclusion_required << ", "
      << "\"formattaters_type_groups\": "
      << v.formattaters_type_groups
      << " }";

    return s;
}

inclusion_directive_group_repository_factory::type_group
inclusion_directive_group_repository_factory::make_type_group(
    const annotations::type_repository& atrp,
    const formatters::repository& frp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    const auto ir(traits::cpp::inclusion_required());
    r.inclusion_required = s.select_type_by_name(ir);

    for (const auto f : frp.stock_artefact_formatters()) {
        const auto& al(f->archetype_location());
        const auto arch(al.archetype());

        using formatters::inclusion_support_types;
        static const auto ns(inclusion_support_types::not_supported);
        if (f->inclusion_support_type() == ns) {
            BOOST_LOG_SEV(lg, debug) << "Skipping archetype: " << arch;
            continue;
        }

        formattater_type_group ftg;
        const auto& pid(traits::primary_inclusion_directive());
        ftg.primary_inclusion_directive = s.select_type_by_name(arch, pid);

        const auto& sid(traits::secondary_inclusion_directive());
        ftg.secondary_inclusion_directive = s.select_type_by_name(arch, sid);

        // note: redefinition of "ir" by design as scopes are different.
        const auto& ir(traits::inclusion_required());
        ftg.inclusion_required = s.select_type_by_name(arch, ir);
        r.formattaters_type_groups[arch] = ftg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result: " << r;
    return r;
}

bool inclusion_directive_group_repository_factory::
make_top_level_inclusion_required(
    const type_group& tg, const annotations::annotation& a) const {
    const annotations::entry_selector s(a);
    return s.get_boolean_content_or_default(tg.inclusion_required);
}

inclusion_directive_configuration inclusion_directive_group_repository_factory::
make_inclusion_directive_configuration(
    const type_group& tg,const std::string& archetype,
    const annotations::annotation& a) const {

    if (archetype.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_archetype;
        BOOST_THROW_EXCEPTION(expansion_error(empty_archetype));
    }

    const auto i(tg.formattaters_type_groups.find(archetype));
    if (i == tg.formattaters_type_groups.end()) {
        BOOST_LOG_SEV(lg, error) << missing_archetype;
        BOOST_THROW_EXCEPTION(expansion_error(missing_archetype));
    }

    const auto& ft(i->second);
    const annotations::entry_selector s(a);
    inclusion_directive_configuration r;

    const auto& ir(ft.inclusion_required);
    r.inclusion_required(s.get_boolean_content_or_default(ir));

    const auto pid(ft.primary_inclusion_directive);
    if (s.has_entry(pid))
        r.primary_directive(s.get_text_content(pid));

    const auto sid(ft.secondary_inclusion_directive);
    if (s.has_entry(sid))
        r.secondary_directives(s.get_text_collection_content(sid));

    return r;
}

std::string inclusion_directive_group_repository_factory::
to_inclusion_directive(const boost::filesystem::path& p) const {
    std::ostringstream ss;
    ss << double_quote << p.generic_string() << double_quote;
    return ss.str();
}

inclusion_directive_group_repository_factory::artefact_formatters_type
inclusion_directive_group_repository_factory::remove_non_includible_formatters(
    const artefact_formatters_type& formatters) const {

    artefact_formatters_type r;
    using formatters::inclusion_support_types;
    static const auto ns(inclusion_support_types::not_supported);
    for (const auto& fmt : formatters) {
        if (fmt->inclusion_support_type() != ns)
            r.push_front(fmt);
    }
    return r;
}

inclusion_directive_group_repository_factory::
artefact_formatters_by_type_index_type
inclusion_directive_group_repository_factory::
includible_formatters_by_type_index(const formatters::repository& frp) const {

    artefact_formatters_by_type_index_type r;
    for (const auto& pair : frp.stock_artefact_formatters_by_type_index()) {
        const auto& ti(pair.first);
        const auto& fmts(pair.second);
        r[ti] = remove_non_includible_formatters(fmts);
    }
    return r;
}

void inclusion_directive_group_repository_factory::
insert_inclusion_directive(const std::string& id, const std::string& archetype,
    const inclusion_directive_group& idg,
    inclusion_directive_group_repository& idgrp) const {

    if (idg.primary_directive().empty()) {
        std::ostringstream s;
        s << empty_primary_directive << archetype << " for type: " << id;

        const auto msg(s.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(expansion_error(msg));
    }

    const auto pair(std::make_pair(archetype, idg));
    const auto inserted(idgrp.by_id()[id].insert(pair).second);
    if (inserted)
        return;

    BOOST_LOG_SEV(lg, error) << duplicate_element_name << id;
    BOOST_THROW_EXCEPTION(expansion_error(duplicate_element_name + id));
}

void inclusion_directive_group_repository_factory::
compute_inclusion_directives(const type_group& tg, const yarn::element& e,
    const artefact_formatters_type& formatters, const locator& l,
    inclusion_directive_group_repository& idgrp) const {

    const auto& n(e.name());
    const auto id(n.id());
    BOOST_LOG_SEV(lg, debug) << "Started computing inclusion directives for: "
                             << id;

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
    const auto& a(e.annotation());
    const bool required(make_top_level_inclusion_required(tg, a));
    if (!required) {
        BOOST_LOG_SEV(lg, trace) << "Inclusion not required for element.";
        return;
    } else
        BOOST_LOG_SEV(lg, trace) << "Inclusion directive required for element.";

    /*
     * Now we start working at the formatter level.
     */
    for (const auto& fmt : formatters) {
        const auto arch(fmt->archetype_location().archetype());
        BOOST_LOG_SEV(lg, trace) << "Archetype: " << arch;

        /*
         * Does the archetype require an inclusion directive for this
         * specific formatter? Some elements require inclusion
         * directives for some archetypes, but not for others. For
         * example, we may need an include for serialising a
         * std::list, but in test data we make use of helpers and thus
         * not require an include.
         *
         * Again, we default this flag to true.
         */
        const auto id_cfg(make_inclusion_directive_configuration(tg, arch, a));
        if (!id_cfg.inclusion_required()) {
            BOOST_LOG_SEV(lg, trace) << "Inclusion directive not required "
                                     << " for archetype.";
            continue;
        } else
            BOOST_LOG_SEV(lg, trace) << "Inclusion directive required "
                                     << " for archetype.";

        /*
         * Does the configuration provide a "hard-coded" inclusion
         * directive?  That is, the archetype has an hard-coded
         * incantation for its include. This is the case for proxy
         * models such as boost, std etc where we can't compute the
         * inclusion directive.
         */
        inclusion_directive_group idg;
        if (!id_cfg.primary_directive().empty()) {
            idg.primary_directive(id_cfg.primary_directive());
            BOOST_LOG_SEV(lg, trace) << "Read primary directive from "
                                     << "configuration: "
                                     << id_cfg.primary_directive();
        } else {
            /*
             * Finally, we have no alternative but to compute the
             * inclusion directive according to a well-defined
             * heuristic.
             */
            const auto path(fmt->inclusion_path(l, n));
            idg.primary_directive(to_inclusion_directive(path));
            BOOST_LOG_SEV(lg, trace) << "Computed primary directive: "
                                     << idg.primary_directive();
        }

        insert_inclusion_directive(id, arch, idg, idgrp);
        BOOST_LOG_SEV(lg, trace) << "Inserting inclusion directive group: "
                                 << idg;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished computing inclusion directives.";
}

inclusion_directive_group_repository
inclusion_directive_group_repository_factory::make(const type_group& tg,
    const artefact_formatters_by_type_index_type& afti, const locator& l,
    const std::unordered_map<std::string, formattable>& formattables) const {

    /*
     * For all formattables and their associated element segments,
     * find the formatters that support the element segment and
     * then compute the inclusion directive group for it.
     */
    inclusion_directive_group_repository r;
    for (const auto& pair : formattables) {
        const auto& formattable(pair.second);

        for (const auto& segment : formattable.all_segments()) {
            const auto& e(*segment);
            const auto id(e.name().id());
            const auto ti(std::type_index(typeid(e)));

            const auto i(afti.find(ti));
            if (i == afti.end() || i->second.empty()) {
                BOOST_LOG_SEV(lg, debug) << formatter_not_found_for_type << id;
                continue;
            }

            compute_inclusion_directives(tg, e, i->second, l, r);
        }
    }
    return r;
}

inclusion_directive_group_repository
inclusion_directive_group_repository_factory::
make(const annotations::type_repository& atrp,
    const formatters::repository& frp, const locator& l,
    const std::unordered_map<std::string, formattable>& formattables) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating inclusion dependencies "
                             << "group repository.";

    /*
     * First we must make sure we only have formatters which generate
     * files that can be included via an include directive. Filter out
     * all of those that do not, and bucket them all by type index.
     */
    const auto afti(includible_formatters_by_type_index(frp));
    const auto tg(make_type_group(atrp, frp));
    return make(tg, afti, l, formattables);

    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies "
                             << "group repository.";
}

} } } }

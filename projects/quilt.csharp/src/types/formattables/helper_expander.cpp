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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/quilt.csharp/io/formattables/helper_configuration_io.hpp"
#include "dogen/quilt.csharp/types/formatters/helper_formatter_interface.hpp"
#include "dogen/quilt.csharp/types/formattables/helper_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.csharp.formattables.helper_expander"));

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

class helper_properties_generator : public yarn::element_visitor {
public:
    helper_properties_generator(const helper_configuration& cfg,
        const helper_expander::facets_for_family_type& fff);

private:
    std::list<helper_properties>
    compute_helper_properties(const helper_configuration& cfg,
        const helper_expander::facets_for_family_type& fff,
        const bool in_inheritance_relationship,
        const std::list<yarn::attribute>& attrs) const;

public:
    /*
     * We are only interested in yarn objects; all other element
     * types do not need helpers.
     */
    using yarn::element_visitor::visit;
    void visit(const yarn::object& o);

public:
    const std::list<formattables::helper_properties>& result() const;

private:
    const helper_configuration& helper_configuration_;
    const helper_expander::facets_for_family_type& facets_for_family_;
    std::list<formattables::helper_properties> result_;
};

helper_properties_generator::
helper_properties_generator(const helper_configuration& cfg,
    const helper_expander::facets_for_family_type& fff)
    : helper_configuration_(cfg), facets_for_family_(fff) {}

void helper_properties_generator::visit(const yarn::object& o) {
    const auto& fff(facets_for_family_);
    const auto& cfg(helper_configuration_);
    const auto& attrs(o.local_attributes());
    const auto iir(o.in_inheritance_relationship());
    result_ = compute_helper_properties(cfg, fff, iir, attrs);
}

const std::list<formattables::helper_properties>&
helper_properties_generator::result() const {
    return result_;
}

std::list<helper_properties> helper_properties_generator::
compute_helper_properties(const helper_configuration& /*cfg*/,
    const helper_expander::facets_for_family_type& /*fff*/,
    const bool /*in_inheritance_relationship*/,
    const std::list<yarn::attribute>& /*attrs*/) const {
    std::list<helper_properties> r;
    return r;
}

helper_expander::type_group helper_expander::
make_type_group(const annotations::type_repository& atrp) const {
    const annotations::type_repository_selector s(atrp);
    const auto hf(traits::csharp::helper::family());
    type_group r;
    r.family = s.select_type_by_name(hf);
    return r;
}

helper_configuration helper_expander::
make_configuration(const type_group& tg, const model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started making the configuration.";
    helper_configuration r;

    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& e(*formattable.element());
        const annotations::entry_selector s(e.annotation());
        const auto fam(s.get_text_content_or_default(tg.family));
        r.helper_families()[id] = fam;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished making the configuration. Result:"
                             << r;
    return r;
}

helper_expander::facets_for_family_type
helper_expander::facets_for_family(const formatters::repository& frp) const {
    BOOST_LOG_SEV(lg, debug) << "Started making facets for family.";

    /*
     * Unpack the helper formatter container to generate a mapping of
     * helper family to facet. The container has helpers by family, by
     * owning file formatter.
     */
    facets_for_family_type r;
    for (const auto& families_pair : frp.helper_formatters())
        for (const auto& file_formatter_pair : families_pair.second)
            for (const auto& hf : file_formatter_pair.second)
                for (const auto& f : hf->owning_facets())
                    r[hf->family()].insert(f);

    BOOST_LOG_SEV(lg, debug) << "Finished making facets for family. Result: "
                             << r;
    return r;
}

void helper_expander::populate_helper_properties(
    const helper_configuration& cfg, const formatters::repository& frp,
    std::unordered_map<std::string, formattable>& formattables) const {

    const auto fff(facets_for_family(frp));
    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& eprops(formattable.element_properties());

        /*
         * We only want to process the master segment; the extensions
         * can be ignored.
         */
        auto& e(*formattable.element());

        /*
         * We only need to generate helpers for the target
         * model. However, we can't perform this after reduction
         * because the helper properties must be build prior to
         * reduction or else we will not get helpers for referenced
         * models.
         */
        if (e.origin_type() != yarn::origin_types::target)
            continue;

        /*
         * Update the helper properties, if any exist.
         */
        helper_properties_generator g(cfg, fff);
        e.accept(g);
        eprops.helper_properties(g.result());
    }
}

void helper_expander::expand(const annotations::type_repository& atrp,
    const formatters::repository& /*frp*/, model& fm) const {
    const auto tg(make_type_group(atrp));
    /*const auto cfg(*/make_configuration(tg, fm)/*)*/;
    // populate_helper_properties(cfg, frp, fm.formattables());
}

} } } }

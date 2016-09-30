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
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/opaque_configuration_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.helper_expander"));

const std::string duplicate_name("Duplicate name: ");
const std::string missing_formatter("Formatter not found: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

annotations::opaque_annotations_builder opaque_configuration_expander::
create_opaque_annotations_builder(const dynamic::repository& drp) const {
    annotations::opaque_annotations_builder r(drp);
    return r;
}

void opaque_configuration_expander::populate_opaque_configuration(
    const annotations::opaque_annotations_builder& b, const yarn::element& e,
    formatter_configurations_type& fmt_cfgs) const {

    /*
     * First we generate the opaque configuration for the element,
     * across all formatters that have such configuration.
     */
    const auto annotations(b.build(e.extensions()));

    /*
     * We now loop through the generated opaque configurations and
     * look for the corresponding formatter configuration. It must
     * exist. Once located, we slot in the opaque configuration.
     */
    for (const auto& pair : annotations) {
        const auto fmtn(pair.first);
        const auto i(fmt_cfgs.find(fmtn));
        if (i == fmt_cfgs.end()) {
            BOOST_LOG_SEV(lg, error) << missing_formatter << fmtn;
            BOOST_THROW_EXCEPTION(expansion_error(missing_formatter + fmtn));
        }

        auto& fmt_cfg(i->second);
        const auto& annotation(pair.second);
        fmt_cfg.opaque_configuration().top_level(annotation);
    }

    /*
     * Yarn objects have an additional level of opaque configuration:
     * properties. If we're not one of these, we're done.
     */
    const auto ptr(dynamic_cast<const yarn::object*>(&e));
    if (ptr == nullptr)
        return;

    /*
     * We need to keep track of the annotations for each property by
     * formatter. They come out of the builder the wrong-way round (by
     * property by formatter).
     */
    std::unordered_map<
        std::string,
        std::unordered_map<std::string,
                           boost::shared_ptr<annotations::opaque_annotations>>
        > annotations_by_formatter;

    /*
     * Now loop through all attributes and collect the opaque
     * annotations by formatter name, by attribute name.
     */
    for (const auto& attr : ptr->all_attributes()) {
        const auto annotations(b.build(attr.extensions()));
        for (const auto& pair : annotations) {
            const auto fmtn(pair.first);
            const auto& annotation(pair.second);
            const auto attr_pair(std::make_pair(attr.name().id(), annotation));

            auto& fmt_ann(annotations_by_formatter[fmtn]);
            const auto inserted(fmt_ann.insert(attr_pair).second);
            if (!inserted) {
                const auto id(attr.name().id());
                BOOST_LOG_SEV(lg, error) << duplicate_name << id;
                BOOST_THROW_EXCEPTION(expansion_error(duplicate_name + id));
            }
        }
    }

    /*
     * Finally loop the temporary container and for each entry, find
     * the corresponding formatter; slot the opaque configurations by
     * property there.
     */
    for (const auto& pair : annotations_by_formatter) {
        const auto fmtn(pair.first);
        const auto i(fmt_cfgs.find(fmtn));
        if (i == fmt_cfgs.end()) {
            BOOST_LOG_SEV(lg, error) << missing_formatter << fmtn;
            BOOST_THROW_EXCEPTION(expansion_error(missing_formatter + fmtn));
        }

        auto& fmt_cfg(i->second);
        auto& opq_cfg(fmt_cfg.opaque_configuration());
        opq_cfg.property_level(pair.second);
    }
}

void opaque_configuration_expander::populate_opaque_configuration(
    const annotations::opaque_annotations_builder& b,
    std::unordered_map<std::string, formattable>& formattables) const {

    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& fmtt_cfgs(formattable.configuration().formatter_configuration());

        /*
         * We only want to process the master segment; the
         * extensions can be ignored.
         */
        auto& segment(*formattable.master_segment());
        populate_opaque_configuration(b, segment, fmtt_cfgs);
    }
}

void opaque_configuration_expander::expand(const dynamic::repository& drp,
    std::unordered_map<std::string, formattable>& formattables) const {

    const auto b(create_opaque_annotations_builder(drp));
    populate_opaque_configuration(b, formattables);
}

} } } }

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
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/optional_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/io/meta_model/model_io.hpp"
#include "dogen/yarn/io/meta_model/element_archetype_io.hpp"
#include "dogen/yarn/io/meta_model/backend_properties_io.hpp"
#include "dogen/yarn/io/meta_model/facet_properties_io.hpp"
#include "dogen/yarn/io/meta_model/archetype_properties_io.hpp"
#include "dogen/yarn/types/helpers/scoped_transform_probing.hpp"
#include "dogen/yarn/types/transforms/archetype_location_properties_transform.hpp"

namespace {

const std::string transform_id(
    "yarn.transforms.archetype_location_properties_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen {
namespace yarn {
namespace transforms {

inline std::ostream& operator<<(std::ostream& s,
    const archetype_location_properties_transform::backend_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform::"
      << "archetype_location_properties_transform::backend_type_group\"" << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"directory\": " << v.directory
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s,
    const archetype_location_properties_transform::facet_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform::"
      << "archetype_location_properties_transform::facet_type_group\"" << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"overwrite\": " << v.overwrite << ", "
      << "\"directory\": " << v.directory << ", "
      << "\"postfix\": " << v.postfix
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s,
    const archetype_location_properties_transform::archetype_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform::"
      << "archetype_location_properties_transform::archetype_type_group\""
      << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"overwrite\": " << v.overwrite << ", "
      << "\"postfix\": " << v.postfix
      << " }";

    return s;
}

std::unordered_map<std::string,
                   archetype_location_properties_transform::backend_type_group>
archetype_location_properties_transform::
make_backend_type_group(const annotations::type_repository& atrp,
    const annotations::archetype_location_repository& alrp) {
    std::unordered_map<std::string, backend_type_group> r;

    const annotations::type_repository_selector s(atrp);
    for (const auto& pair : alrp.facet_names_by_backend_name()) {
        const auto& backend(pair.first);
        backend_type_group btg;
        const auto ebl(traits::enabled());
        btg.enabled = s.select_type_by_name(backend, ebl);

        const auto dir(traits::directory());
        btg.directory = s.select_type_by_name(backend, dir);

        r.insert(std::make_pair(backend, btg));
    }
    return r;
}

std::unordered_map<std::string,
                   archetype_location_properties_transform::facet_type_group>
archetype_location_properties_transform::
make_facet_type_group(const annotations::type_repository& atrp,
    const annotations::archetype_location_repository& alrp) {
    std::unordered_map<std::string, facet_type_group> r;

    const annotations::type_repository_selector s(atrp);
    for (const auto& pair : alrp.facet_names_by_backend_name()) {
        for (const auto& fct : pair.second) {
            facet_type_group ftg;
            const auto ebl(traits::enabled());
            ftg.enabled = s.select_type_by_name(fct, ebl);

            const auto ow(traits::overwrite());
            ftg.overwrite = s.select_type_by_name(fct, ow);

            ftg.directory = s.try_type_field_by_name(fct, traits::directory());
            ftg.postfix = s.try_type_field_by_name(fct, traits::postfix());

            r.insert(std::make_pair(fct, ftg));
        }
    }
    return r;
}

std::unordered_map<
    std::string,
    archetype_location_properties_transform::archetype_type_group>
archetype_location_properties_transform::
make_archetype_type_group(const annotations::type_repository& atrp,
    const annotations::archetype_location_repository& alrp) {
    std::unordered_map<std::string, archetype_type_group> r;

    const annotations::type_repository_selector s(atrp);
    for (const auto& al : alrp.archetype_locations()) {
        archetype_type_group atg;
        const auto ebl(traits::enabled());
        atg.enabled = s.select_type_by_name(al.archetype(), ebl);

        const auto ow(traits::overwrite());
        atg.overwrite = s.select_type_by_name(al.archetype(), ow);

        const auto postfix(traits::postfix());
        atg.postfix = s.select_type_by_name(al.archetype(), postfix);

        r.insert(std::make_pair(al.archetype(), atg));
    }
    return r;
}

std::unordered_map<std::string, meta_model::backend_properties>
archetype_location_properties_transform::obtain_backend_properties(
    const std::unordered_map<std::string, backend_type_group>& tgs,
    const annotations::annotation& ra) {

    BOOST_LOG_SEV(lg, debug) << "Creating backend properties.";

    std::unordered_map<std::string, meta_model::backend_properties> r;
    const annotations::entry_selector s(ra);
    for (const auto& pair : tgs) {
        const auto& backend(pair.first);
        const auto& tg(pair.second);

        meta_model::backend_properties bp;
        bp.enabled(s.get_boolean_content_or_default(tg.enabled));
        bp.directory(s.get_text_content_or_default(tg.directory));

        r[backend] = bp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created backend properties. Result: " << r;
    return r;
}

std::unordered_map<std::string, meta_model::facet_properties>
archetype_location_properties_transform::obtain_facet_properties(
    const std::unordered_map<std::string, facet_type_group>& tgs,
    const annotations::annotation& ra) {

    BOOST_LOG_SEV(lg, debug) << "Creating facet properties.";

    std::unordered_map<std::string, meta_model::facet_properties> r;
    const annotations::entry_selector s(ra);
    for (const auto& pair : tgs) {
        const auto& facet(pair.first);
        const auto& tg(pair.second);

        meta_model::facet_properties fp;
        fp.enabled(s.get_boolean_content_or_default(tg.enabled));
        fp.overwrite(s.get_boolean_content_or_default(tg.overwrite));
        if (tg.directory)
            fp.directory(s.get_text_content_or_default(*tg.directory));

        if (tg.postfix)
            fp.postfix(s.get_text_content_or_default(*tg.postfix));

        r[facet] = fp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created facet properties. Result: " << r;
    return r;
}

std::unordered_map<std::string, meta_model::archetype_properties>
archetype_location_properties_transform::obtain_archetype_properties(
    const std::unordered_map<std::string, archetype_type_group>& tgs,
    const annotations::annotation& ra) {

    BOOST_LOG_SEV(lg, debug) << "Creating archetype properties.";

    std::unordered_map<std::string, meta_model::archetype_properties> r;
    const annotations::entry_selector s(ra);
    for (const auto& pair : tgs) {
        const auto& archetype(pair.first);
        const auto& tg(pair.second);

        meta_model::archetype_properties ap;
        ap.enabled(s.get_boolean_content_or_default(tg.enabled));
        if (s.has_entry(tg.overwrite))
            ap.overwrite(s.get_boolean_content(tg.overwrite));

        ap.postfix(s.get_text_content_or_default(tg.postfix));

        r[archetype] = ap;
    }

    BOOST_LOG_SEV(lg, debug) << "Created archetype properties. Result: " << r;
    return r;
}

void archetype_location_properties_transform::
transform(const context& ctx, meta_model::model& m) {
    helpers::scoped_transform_probing stp(lg,
        "archetype location properties transform",
        transform_id, m.name().id(), ctx.prober(), m);

    const auto& atrp(ctx.type_repository());
    const auto& alrp(ctx.archetype_location_repository());
    const auto btg(make_backend_type_group(atrp, alrp));
    const auto ftg(make_facet_type_group(atrp, alrp));
    const auto atg(make_archetype_type_group(atrp, alrp));

    const auto& ra(m.root_module()->annotation());
    meta_model::archetype_location_properties alp;
    alp.backend_properties(obtain_backend_properties(btg, ra));
    alp.facet_properties(obtain_facet_properties(ftg, ra));
    alp.archetype_properties(obtain_archetype_properties(atg, ra));
    m.archetype_location_properties(alp);
}

} } }

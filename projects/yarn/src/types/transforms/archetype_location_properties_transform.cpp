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
#include "dogen/yarn/io/meta_model/local_archetype_location_properties_io.hpp"
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

inline std::ostream& operator<<(std::ostream& s, const
    archetype_location_properties_transform::global_archetype_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform::"
      << "archetype_location_properties_transform::global_archetype_type_group\""
      << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"overwrite\": " << v.overwrite << ", "
      << "\"postfix\": " << v.postfix
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s, const
    archetype_location_properties_transform::local_archetype_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform::"
      << "archetype_location_properties_transform::local_archetype_type_group\""
      << ", "
      << "\"facet_enabled\": " << v.facet_enabled << ", "
      << "\"archetype_enabled\": " << v.archetype_enabled << ", "
      << "\"facet_overwrite\": " << v.facet_overwrite << ", "
      << "\"archetype_overwrite\": " << v.archetype_overwrite
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
    archetype_location_properties_transform::global_archetype_type_group>
archetype_location_properties_transform::
make_global_archetype_type_group(const annotations::type_repository& atrp,
    const annotations::archetype_location_repository& alrp) {
    std::unordered_map<std::string, global_archetype_type_group> r;

    const annotations::type_repository_selector s(atrp);
    for (const auto& al : alrp.archetype_locations()) {
        global_archetype_type_group gatg;
        const auto ebl(traits::enabled());
        gatg.enabled = s.select_type_by_name(al.archetype(), ebl);

        const auto ow(traits::overwrite());
        gatg.overwrite = s.select_type_by_name(al.archetype(), ow);

        const auto postfix(traits::postfix());
        gatg.postfix = s.select_type_by_name(al.archetype(), postfix);

        r.insert(std::make_pair(al.archetype(), gatg));
    }
    return r;
}


std::unordered_map<
    std::string,
    archetype_location_properties_transform::local_archetype_type_group>
archetype_location_properties_transform::
make_local_archetype_type_group(const annotations::type_repository& atrp,
    const annotations::archetype_location_repository& alrp) {
    std::unordered_map<std::string, local_archetype_type_group> r;

    const annotations::type_repository_selector s(atrp);
    for (const auto& al : alrp.archetype_locations()) {
        local_archetype_type_group latg;
        const auto ebl(traits::enabled());
        latg.facet_enabled = s.select_type_by_name(al.facet(), ebl);
        latg.archetype_enabled = s.select_type_by_name(al.archetype(), ebl);

        const auto ow(traits::overwrite());
        latg.facet_overwrite = s.select_type_by_name(al.facet(), ow);
        latg.archetype_overwrite = s.select_type_by_name(al.archetype(), ow);

        r.insert(std::make_pair(al.archetype(), latg));
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
    const std::unordered_map<std::string, global_archetype_type_group>& tgs,
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
populate_global_archetype_location_properties(
    const annotations::type_repository& atrp,
    const annotations::archetype_location_repository& alrp,
    meta_model::model& m) {

    const auto btg(make_backend_type_group(atrp, alrp));
    const auto ftg(make_facet_type_group(atrp, alrp));
    const auto atg(make_global_archetype_type_group(atrp, alrp));

    const auto& ra(m.root_module()->annotation());
    auto& galp(m.global_archetype_location_properties());
    galp.backend_properties(obtain_backend_properties(btg, ra));
    galp.facet_properties(obtain_facet_properties(ftg, ra));
    galp.archetype_properties(obtain_archetype_properties(atg, ra));
}

std::unordered_map<std::string,
                          meta_model::local_archetype_location_properties>
archetype_location_properties_transform::
obtain_local_archetype_location_properties(
    const std::unordered_map<std::string, local_archetype_type_group>& tgs,
    const annotations::annotation& a) {

    BOOST_LOG_SEV(lg, debug) << "Creating local archetype location properties.";

    std::unordered_map<std::string,
                       meta_model::local_archetype_location_properties> r;
    const annotations::entry_selector s(a);
    for (const auto& pair : tgs) {
        const auto& archetype(pair.first);
        const auto& tg(pair.second);

        meta_model::local_archetype_location_properties lalp;
        if (s.has_entry(tg.facet_enabled)) {
            lalp.facet_enabled(
                s.get_boolean_content_or_default(tg.facet_enabled));
        }

        if (s.has_entry(tg.archetype_enabled)) {
            lalp.archetype_enabled(
                s.get_boolean_content_or_default(tg.archetype_enabled));
        }

        if (s.has_entry(tg.facet_overwrite))
            lalp.facet_overwrite(s.get_boolean_content(tg.facet_overwrite));

        if (s.has_entry(tg.archetype_overwrite)) {
            lalp.archetype_overwrite(
                s.get_boolean_content(tg.archetype_overwrite));
        }

        r[archetype] = lalp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created local archetype location properties."
                             << "Result: " << r;
    return r;
}

void archetype_location_properties_transform::
populate_local_archetype_location_properties(
    const annotations::type_repository& atrp,
    const annotations::archetype_location_repository& alrp,
    meta_model::model& m) {

    const auto tgs(make_local_archetype_type_group(atrp, alrp));
    for (auto ptr : m.elements()) {
        auto& e(*ptr);
        e.archetype_location_properties(
            obtain_local_archetype_location_properties(tgs, e.annotation()));
    }
}

void archetype_location_properties_transform::
transform(const context& ctx, meta_model::model& m) {
    helpers::scoped_transform_probing stp(lg,
        "archetype location properties transform",
        transform_id, m.name().id(), ctx.prober(), m);

    const auto& atrp(ctx.type_repository());
    const auto& alrp(ctx.archetype_location_repository());
    populate_global_archetype_location_properties(atrp, alrp, m);
    populate_local_archetype_location_properties(atrp, alrp, m);
}

} } }

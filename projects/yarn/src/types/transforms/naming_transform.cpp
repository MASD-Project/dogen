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
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/io/meta_model/name_io.hpp"
#include "dogen/yarn/io/meta_model/location_io.hpp"
#include "dogen/yarn/io/meta_model/exomodel_io.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/helpers/location_builder.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/naming_transform.hpp"

namespace {

const std::string id("yarn.transforms.naming_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

const std::string missing_model_modules("Must supply model modules.");

}

namespace dogen {
namespace yarn {
namespace transforms {

std::ostream&
operator<<(std::ostream& s, const naming_transform::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"yarn::naming_transform::"
      << "type_group\"" << ", "
      << "\"external_modules\": " << v.external_modules << ", "
      << "\"model_modules\": " << v.model_modules
      << " }";
    return s;
}

naming_transform::type_group
naming_transform::make_type_group(const annotations::type_repository& atrp) {
    type_group r;

    const annotations::type_repository_selector rs(atrp);

    const auto& em(traits::external_modules());
    r.external_modules = rs.select_type_by_name(em);

    const auto& mm(traits::model_modules());
    r.model_modules = rs.select_type_by_name(mm);

    return r;
}

naming_configuration naming_transform::make_naming_configuration(
    const type_group& tg, const annotations::annotation& a) {

    const annotations::entry_selector s(a);
    if (!s.has_entry(tg.model_modules)) {
        BOOST_LOG_SEV(lg, error) << missing_model_modules;
        BOOST_THROW_EXCEPTION(transformation_error(missing_model_modules));
    }

    naming_configuration r;
    r.model_modules(s.get_text_content(tg.model_modules));

    if (s.has_entry(tg.external_modules))
        r.external_modules(s.get_text_content(tg.external_modules));

    return r;
}

meta_model::location
naming_transform::create_location(const naming_configuration& cfg) {
    helpers::location_builder b;
    b.external_modules(cfg.external_modules());
    b.model_modules(cfg.model_modules());

    const auto r(b.build());
    BOOST_LOG_SEV(lg, debug) << "Computed location: " << r;
    return r;
}

void naming_transform::process_element(const meta_model::location& l,
    meta_model::element& e) {
    helpers::name_builder b;
    b.simple_name(e.name().simple());

    /*
     * Types placed in the global module must not have any of the
     * location properties set.
     */
    if (!e.in_global_module()) {
        b.external_modules(l.external_modules());
        b.model_modules(l.model_modules());
        b.internal_modules(e.name().location().internal_modules());
    }
    e.name(b.build());
}

void naming_transform::process_attributes(const meta_model::location& l,
    std::list<meta_model::attribute>& attrs) {
    for (auto& attr : attrs) {
        helpers::name_builder b;
        b.simple_name(attr.name().simple());
        b.external_modules(l.external_modules());
        b.model_modules(l.model_modules());
        b.internal_modules(attr.name().location().internal_modules());
        attr.name(b.build());
    }
}

void naming_transform::process(const meta_model::location& l,
    meta_model::element& e) {
    process_element(l, e);
}

void naming_transform::process(const meta_model::location& l,
    meta_model::object_template& ot) {
    process_element(l, ot);
}

void naming_transform::process(const meta_model::location& l,
    meta_model::object& o) {
    process_element(l, o);
}

void naming_transform::
update_names(const meta_model::location& l, meta_model::exomodel& em) {
    process(l, em.modules());
    process(l, em.object_templates());
    process(l, em.builtins());
    process(l, em.enumerations());
    process(l, em.primitives());
    process(l, em.objects());
    process(l, em.exceptions());
}

meta_model::name
naming_transform::compute_model_name(const meta_model::location& l) {
    helpers::name_builder b(true/*model_name_mode*/);
    b.external_modules(l.external_modules());
    b.model_modules(l.model_modules());

    const auto r(b.build());
    BOOST_LOG_SEV(lg, debug) << "Computed model name: " << r;
    return r;
}

void naming_transform::
transform(const context& ctx, meta_model::exomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Started naming transform. Model: "
                             << em.name().id();

    ctx.prober().start_transform(id, em.name().id(), em);

    const auto& ra(em.root_module().second->annotation());
    const auto tg(make_type_group(ctx.type_repository()));
    const auto cfg(make_naming_configuration(tg, ra));
    const auto l(create_location(cfg));
    em.name(compute_model_name(l));
    em.root_module().second->name(em.name());
    update_names(l, em);

    ctx.prober().end_transform(em);
    BOOST_LOG_SEV(lg, debug) << "Finished naming transform.";
}

} } }

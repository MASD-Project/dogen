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
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
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
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/io/meta_model/static_stereotypes_io.hpp"
#include "dogen/yarn/io/helpers/stereotypes_conversion_result_io.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/helpers/location_builder.hpp"
#include "dogen/yarn/types/helpers/stereotypes_helper.hpp"
#include "dogen/yarn/types/helpers/stereotypes_helper.hpp"
#include "dogen/yarn/types/helpers/scoped_transform_probing.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/exomodel_to_endomodel_transform.hpp"

namespace {

const std::string transform_id(
    "yarn.transforms.exomodel_to_endomodel_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_element("Element id already exists: ");
const std::string missing_model_modules("Must supply model modules.");
const std::string missing_element_type("Missing yarn element type. Element: ");
const std::string invalid_element_type(
    "Invalid or usupported yarn element type: ");
const std::string too_many_yarn_types(
    "Attempting to set the yarn type more than once.");

using dogen::yarn::meta_model::location;
const location empty_location = location();

}

namespace dogen {
namespace yarn {
namespace transforms {

template<typename Element>
inline void
insert(const boost::shared_ptr<Element>& e,
    std::unordered_map<std::string, boost::shared_ptr<Element>>& dst) {
    const auto id(e->name().id());
    bool inserted(dst.insert(std::make_pair(id, e)).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element << id;
        BOOST_THROW_EXCEPTION(transformation_error(duplicate_element + id));
    }
}

std::ostream& operator<<(std::ostream& s,
    const exomodel_to_endomodel_transform::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"yarn::exomodel_to_endomodel_transform::"
      << "type_group\"" << ", "
      << "\"external_modules\": " << v.external_modules << ", "
      << "\"model_modules\": " << v.model_modules
      << " }";
    return s;
}

exomodel_to_endomodel_transform::type_group exomodel_to_endomodel_transform::
make_type_group(const annotations::type_repository& atrp) {
    type_group r;

    const annotations::type_repository_selector rs(atrp);

    const auto& em(traits::external_modules());
    r.external_modules = rs.select_type_by_name(em);

    const auto& mm(traits::model_modules());
    r.model_modules = rs.select_type_by_name(mm);

    return r;
}

naming_configuration
exomodel_to_endomodel_transform::make_naming_configuration(
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

meta_model::location exomodel_to_endomodel_transform::
create_location(const naming_configuration& nc) {
    helpers::location_builder b;
    b.external_modules(nc.external_modules());
    b.model_modules(nc.model_modules());

    const auto r(b.build());
    BOOST_LOG_SEV(lg, debug) << "Computed location: " << r;
    return r;
}

meta_model::static_stereotypes exomodel_to_endomodel_transform::
compute_element_type(const std::list<meta_model::static_stereotypes>& st,
    const std::string& fallback_element_type) {

    /*
     * Extract the element type information from the supplied static
     * stereotypes. If we have exactly one, we're go to go.
     */
    yarn::helpers::stereotypes_helper h;
    const auto et(h.extract_element_types(st));
    if (et.size() == 1)
        return et.front();

    /*
     * If we've got more than one element type, there is a user error
     * so bomb out.
     */
    if (et.size() > 1) {
        BOOST_LOG_SEV(lg, warn) << too_many_yarn_types;
        BOOST_THROW_EXCEPTION(transformation_error(too_many_yarn_types));
    }

    /*
     * If no yarn element type came up, attempt to use the fallback
     * stereotype suggested by the frontend. If none was suggested
     * just return invalid.
     */
    if (fallback_element_type.empty()) {
        using meta_model::static_stereotypes;
        return meta_model::static_stereotypes::invalid;
    }

    return h.from_string(fallback_element_type);
}

void exomodel_to_endomodel_transform::
process_element(const helpers::adapter& ad, const meta_model::location& l,
    const meta_model::exoelement& ee, meta_model::endomodel& em) {

    helpers::stereotypes_helper h;
    const auto scr(h.from_string(ee.stereotypes()));
    const auto& st(scr.static_stereotypes());
    const auto et(compute_element_type(st, ee.fallback_element_type()));

    using meta_model::static_stereotypes;
    switch (et) {
    case static_stereotypes::object:
        insert(ad.to_object(l, scr, ee), em.objects());
        break;
    case static_stereotypes::object_template:
        insert(ad.to_object_template(l, scr, ee), em.object_templates());
        break;
    case static_stereotypes::exception:
        insert(ad.to_exception(l, scr, ee), em.exceptions());
        break;
    case static_stereotypes::primitive:
        insert(ad.to_primitive(l, scr, ee), em.primitives());
        break;
    case static_stereotypes::enumeration:
        insert(ad.to_enumeration(l, scr, ee), em.enumerations());
        break;
    case static_stereotypes::module:
        insert(ad.to_module(false/*is_root_module*/, l, scr, ee), em.modules());
        break;
    case static_stereotypes::builtin:
        insert(ad.to_builtin(l, scr, ee), em.builtins());
        break;
    default: {
        const auto s(boost::lexical_cast<std::string>(et));
        BOOST_LOG_SEV(lg, error) << invalid_element_type << s;;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_element_type + s));
    } }
}

meta_model::endomodel exomodel_to_endomodel_transform::
transform(const context& ctx, const meta_model::exomodel& em) {
    helpers::scoped_transform_probing stp(lg, "exomodel to endomodel transform",
        transform_id, "FIXME"/*em.name().id()*/, ctx.prober(), em);

    helpers::stereotypes_helper h;
    const auto scr(h.from_string(em.stereotypes()));
    const auto& f(ctx.annotation_factory());
    const auto scope(annotations::scope_types::root_module);
    const auto ra(f.make(em.tagged_values(), scope, scr.dynamic_stereotypes()));
    const auto tg(make_type_group(ctx.type_repository()));
    const auto nc(make_naming_configuration(tg, ra));
    const auto model_location(create_location(nc));

    meta_model::endomodel r;
    helpers::name_builder b(true/*model_name_mode*/);
    b.external_modules(model_location.external_modules());
    b.model_modules(model_location.model_modules());
    r.name(b.build());
    BOOST_LOG_SEV(lg, debug) << "Computed model name: " << r.name();

    const helpers::adapter ad(ctx.annotation_factory());
    for (const auto& ee : em.elements()) {
        const auto l(ee.in_global_module() ? empty_location : model_location);
        process_element(ad, l, ee, r);
    }

    /*
     * FIXME: For now, we must inject the root module into the element
     * collection manually. This is not ideal - we should probably
     * just process it from the root_module member variable - but this
     * will be mopped up during the formattables clean up.
     */
    r.root_module(boost::make_shared<meta_model::module>());
    r.root_module()->name(r.name());
    r.root_module()->annotation(ra);
    r.root_module()->documentation(em.documentation());
    insert(r.root_module(), r.modules());

    return r;
}

} } }

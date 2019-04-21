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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.variability/io/type_io.hpp"
#include "masd.dogen.variability/types/annotation_factory.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/io/meta_model/name_io.hpp"
#include "masd.dogen.coding/io/meta_model/location_io.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/io/meta_model/static_stereotypes_io.hpp"
#include "masd.dogen.coding/types/helpers/name_builder.hpp"
#include "masd.dogen.coding/types/helpers/location_builder.hpp"
#include "masd.dogen.orchestration/io/helpers/stereotypes_conversion_result_io.hpp"
#include "masd.dogen.orchestration/types/helpers/stereotypes_helper.hpp"
#include "masd.dogen.orchestration/types/transforms/context.hpp"
#include "masd.dogen.orchestration/types/transforms/transform_exception.hpp"
#include "masd.dogen.orchestration/types/transforms/injection_model_to_coding_model_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.injection_model_to_coding_model_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string cpp_technical_space("cpp");
const std::string csharp_technical_space("csharp");
const std::string agnostic_technical_space("agnostic");

const std::string duplicate_element("Element id already exists: ");
const std::string missing_model_modules("Must supply model modules.");
const std::string missing_element_type("Missing masd element type. Element: ");
const std::string invalid_element_type(
    "Invalid or usupported masd element type: ");
const std::string too_many_element_types(
    "Attempting to set the masd type more than once.");
const std::string unsupported_technical_space(
    "Technical space is not supported: ");

using masd::dogen::coding::meta_model::location;
const location empty_location = location();

}

namespace masd::dogen::orchestration::transforms {

template<typename Element>
inline void
insert(const boost::shared_ptr<Element>& e,
    std::unordered_map<std::string, boost::shared_ptr<Element>>& dst) {
    const auto id(e->name().qualified().dot());
    bool inserted(dst.insert(std::make_pair(id, e)).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element << id;
        BOOST_THROW_EXCEPTION(transform_exception(duplicate_element + id));
    }
}

std::ostream& operator<<(std::ostream& s,
    const injection_model_to_coding_model_transform::type_group& v) {
    s << " { "
      << "\"__type__\": "
      << "\"coding::injection_model_to_coding_model_transform::"
      << "type_group\"" << ", "
      << "\"external_modules\": " << v.external_modules << ", "
      << "\"model_modules\": " << v.model_modules
      << " }";
    return s;
}

coding::meta_model::technical_space to_technical_space(const std::string& s) {
    using coding::meta_model::technical_space;
    if (s == cpp_technical_space)
        return technical_space::cpp;
    else if (s == csharp_technical_space)
        return technical_space::csharp;
    else if (s == agnostic_technical_space)
        return technical_space::agnostic;

    BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
    BOOST_THROW_EXCEPTION(transform_exception(unsupported_technical_space + s));
}


injection_model_to_coding_model_transform::type_group
injection_model_to_coding_model_transform::
make_type_group(const variability::type_repository& atrp) {
    type_group r;

    const variability::type_repository_selector rs(atrp);

    const auto& em(coding::traits::external_modules());
    r.external_modules = rs.select_type_by_name(em);

    const auto& mm(coding::traits::model_modules());
    r.model_modules = rs.select_type_by_name(mm);

    return r;
}

naming_configuration
injection_model_to_coding_model_transform::make_naming_configuration(
    const type_group& tg, const variability::annotation& a) {

    const variability::entry_selector s(a);
    if (!s.has_entry(tg.model_modules)) {
        BOOST_LOG_SEV(lg, error) << missing_model_modules;
        BOOST_THROW_EXCEPTION(transform_exception(missing_model_modules));
    }

    naming_configuration r;
    r.model_modules(s.get_text_content(tg.model_modules));

    if (s.has_entry(tg.external_modules))
        r.external_modules(s.get_text_content(tg.external_modules));

    return r;
}

coding::meta_model::location injection_model_to_coding_model_transform::
create_location(const naming_configuration& nc) {
    coding::helpers::location_builder b;
    b.external_modules(nc.external_modules());
    b.model_modules(nc.model_modules());

    const auto r(b.build());
    BOOST_LOG_SEV(lg, debug) << "Computed location: " << r;
    return r;
}

coding::meta_model::static_stereotypes
injection_model_to_coding_model_transform::
compute_element_type(
    const std::list<coding::meta_model::static_stereotypes>& st,
    const std::string& fallback_element_type) {

    /*
     * Extract the element type information from the supplied static
     * stereotypes. If we have exactly one, we're go to go.
     */
    helpers::stereotypes_helper h;
    const auto et(h.extract_element_types(st));
    if (et.size() == 1)
        return et.front();

    /*
     * If we've got more than one element type, there is a user error
     * so bomb out.
     */
    if (et.size() > 1) {
        BOOST_LOG_SEV(lg, warn) << too_many_element_types;
        BOOST_THROW_EXCEPTION(transform_exception(too_many_element_types));
    }

    /*
     * If no masd element type came up, attempt to use the fallback
     * stereotype suggested by the frontend. If none was suggested
     * just return invalid.
     */
    if (fallback_element_type.empty())
        return coding::meta_model::static_stereotypes::invalid;

    return h.from_string(fallback_element_type);
}

void injection_model_to_coding_model_transform::
process_element(const helpers::adapter& ad,
    const coding::meta_model::location& l,
    const injection::meta_model::element& e, coding::meta_model::model& m) {

    helpers::stereotypes_helper h;
    const auto scr(h.from_string(e.stereotypes()));
    const auto& st(scr.static_stereotypes());
    const auto et(compute_element_type(st, e.fallback_element_type()));

    using coding::meta_model::static_stereotypes;
    switch (et) {
    case static_stereotypes::object:
        insert(ad.to_object(l, scr, e), m.objects());
        break;
    case static_stereotypes::object_template:
        insert(ad.to_object_template(l, scr, e), m.object_templates());
        break;
    case static_stereotypes::exception:
        insert(ad.to_exception(l, scr, e), m.exceptions());
        break;
    case static_stereotypes::primitive:
        insert(ad.to_primitive(l, scr, e), m.primitives());
        break;
    case static_stereotypes::enumeration:
        insert(ad.to_enumeration(l, scr, e), m.enumerations());
        break;
    case static_stereotypes::module:
        insert(ad.to_module(l, scr, e), m.modules());
        break;
    case static_stereotypes::builtin:
        insert(ad.to_builtin(l, scr, e), m.builtins());
        break;
    case static_stereotypes::modeline_group:
        insert(ad.to_modeline_group(l, scr, e), m.modeline_groups());
        break;
    case static_stereotypes::modeline:
        insert(ad.to_modeline(l, scr, e), m.modelines());
        break;
    case static_stereotypes::generation_marker:
        insert(ad.to_generation_marker(l, scr, e), m.generation_markers());
        break;
    case static_stereotypes::licence:
        insert(ad.to_licence(l, scr, e), m.licences());
        break;
    case static_stereotypes::variability_profile_template:
        insert(ad.to_variability_profile_template(l, scr, e),
            m.variability_profile_templates());
        break;
    default: {
        const auto s(boost::lexical_cast<std::string>(et));
        BOOST_LOG_SEV(lg, error) << invalid_element_type << s;;
        BOOST_THROW_EXCEPTION(transform_exception(invalid_element_type + s));
    } }
}

coding::meta_model::model injection_model_to_coding_model_transform::
apply(const context& ctx, const injection::meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "injection model to coding model transform", transform_id, m.name(),
        *ctx.coding_context().tracer(), m);

    helpers::stereotypes_helper h;
    const auto scr(h.from_string(m.stereotypes()));
    const auto& f(*ctx.coding_context().annotation_factory());
    const auto scope(variability::scope_types::root_module);
    const auto ra(f.make(m.tagged_values(), scope));

    const auto& atrp(*ctx.coding_context().type_repository());
    const auto tg(make_type_group(atrp));
    const auto nc(make_naming_configuration(tg, ra));
    const auto model_location(create_location(nc));

    coding::meta_model::model r;
    coding::helpers::name_builder b(true/*model_name_mode*/);
    b.external_modules(model_location.external_modules());
    b.model_modules(model_location.model_modules());
    r.name(b.build());
    BOOST_LOG_SEV(lg, debug) << "Computed model name: " << r.name();

    r.input_technical_space(to_technical_space(m.input_technical_space()));
    const helpers::adapter ad;
    for (const auto& e : m.elements()) {
        const auto l(e.in_global_module() ? empty_location : model_location);
        process_element(ad, l, e, r);
    }

    r.root_module(boost::make_shared<coding::meta_model::module>());
    r.root_module()->name(r.name());
    r.root_module()->annotation(ra);
    r.root_module()->dynamic_stereotypes(scr.dynamic_stereotypes());
    r.root_module()->documentation(m.documentation());
    insert(r.root_module(), r.modules());

    stp.end_transform(r);
    return r;
}

}

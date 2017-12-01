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
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/helpers/location_builder.hpp"
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

}

namespace dogen {
namespace yarn {
namespace transforms {

namespace {

class naming_helper {
private:
    void process_element(const meta_model::location& l,
        meta_model::element& e) const;

    // void process_attributes(const meta_model::location& l,
    //     std::list<meta_model::attribute>& attrs) const;

public:
    void process(const meta_model::location& l, meta_model::element& e) const;
    void process(const meta_model::location& l, meta_model::object& o) const;
    void process(const meta_model::location& l,
        meta_model::object_template& ot) const;

public:
    meta_model::name compute_model_name(const meta_model::location& l) const;

private:
    naming_configuration configuration_;
};


void naming_helper::process_element(const meta_model::location& l,
    meta_model::element& e) const {
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

/*
void naming_helper::process_attributes(const meta_model::location& l,
    std::list<meta_model::attribute>& attrs) const {
    for (auto& attr : attrs) {
        helpers::name_builder b;
        b.simple_name(attr.name().simple());
        b.external_modules(l.external_modules());
        b.model_modules(l.model_modules());
        b.internal_modules(attr.name().location().internal_modules());
        attr.name(b.build());
    }
}
*/
void naming_helper::
process(const meta_model::location& l, meta_model::element& e) const {
    process_element(l, e);
}

void naming_helper::
process(const meta_model::location& l, meta_model::object_template& ot) const {
    process_element(l, ot);
}

void naming_helper::
process(const meta_model::location& l, meta_model::object& o) const {
    process_element(l, o);
}

meta_model::name
naming_helper::compute_model_name(const meta_model::location& l) const {
    helpers::name_builder b(true/*model_name_mode*/);
    b.external_modules(l.external_modules());
    b.model_modules(l.model_modules());

    const auto r(b.build());
    BOOST_LOG_SEV(lg, debug) << "Computed model name: " << r;
    return r;
}

}

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

template<typename Element>
inline std::unordered_map<std::string, boost::shared_ptr<Element>>
to_element_map(const naming_helper& helper, const meta_model::location& l,
    const std::list<std::pair<annotations::scribble_group,
    boost::shared_ptr<Element>>>& elements) {
    std::unordered_map<std::string, boost::shared_ptr<Element>> r;
    for (const auto& pair : elements) {
        auto e(pair.second);
        helper.process(l, *e);
        insert(e, r);
    }

    return r;
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

naming_configuration exomodel_to_endomodel_transform::make_naming_configuration(
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

meta_model::endomodel exomodel_to_endomodel_transform::
transform(const context& ctx, const meta_model::exomodel& em) {
    helpers::scoped_transform_probing stp(lg, "exomodel to endomodel transform",
        transform_id, em.name().id(), ctx.prober(), em);

    const auto& ra(em.root_module().second->annotation());
    const auto tg(make_type_group(ctx.type_repository()));
    const auto nc(make_naming_configuration(tg, ra));
    const auto l(create_location(nc));

    /*
     * Compute the model name and update the root module name with it.
     */
    naming_helper h;
    meta_model::endomodel r;
    r.name(h.compute_model_name(l));
    r.root_module(em.root_module().second);
    r.root_module()->name(r.name());

    /*
     * Now update all elements and copy them across to the endomodel.
     */
    r.modules(to_element_map(h, l, em.modules()));
    r.object_templates(to_element_map(h, l, em.object_templates()));
    r.builtins(to_element_map(h, l, em.builtins()));
    r.enumerations(to_element_map(h, l, em.enumerations()));
    r.primitives(to_element_map(h, l, em.primitives()));
    r.objects(to_element_map(h, l, em.objects()));
    r.exceptions(to_element_map(h, l, em.exceptions()));

    /*
     * FIXME: For now, we must inject the root module into the element
     * collection manually. This is not ideal - we should probably
     * just process it from the root_module member variable - but this
     * will be mopped up during the formattables clean up.
     */
    insert(r.root_module(), r.modules());

    stp.end_transform(r);
    return r;
}

} } }

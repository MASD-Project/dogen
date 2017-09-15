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
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/io/meta_model/exomodel_io.hpp"
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/exomodel_to_endomodel_transform.hpp"

namespace {

const std::string id("yarn.transforms.exomodel_to_endomodel_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

const std::string duplicate_element("Element id already exists: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

template<typename Element>
inline void
insert(const std::pair<annotations::scribble_group, boost::shared_ptr<Element>>&
    pair, std::unordered_map<std::string, boost::shared_ptr<Element>>& dst) {

    const auto e(pair.second);
    const auto id(e->name().id());
    bool inserted(dst.insert(std::make_pair(id, e)).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element << id;
        BOOST_THROW_EXCEPTION(transformation_error(duplicate_element + id));
    }
}

template<typename Element>
inline std::unordered_map<std::string, boost::shared_ptr<Element>>
to_element_map(const std::list<std::pair<annotations::scribble_group,
    boost::shared_ptr<Element>>>& elements) {
    std::unordered_map<std::string, boost::shared_ptr<Element>> r;
    for (const auto pair : elements)
        insert(pair, r);

    return r;
}

meta_model::endomodel exomodel_to_endomodel_transform::
transform(const context& ctx, const meta_model::exomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Started exomodel to endomodel transform."
                             << " Model: " << em.name().id();
    ctx.prober().start_transform(id, em.name().id(), em);

    meta_model::endomodel r;
    r.name(em.name());
    r.modules(to_element_map(em.modules()));
    r.object_templates(to_element_map(em.object_templates()));
    r.builtins(to_element_map(em.builtins()));
    r.enumerations(to_element_map(em.enumerations()));
    r.primitives(to_element_map(em.primitives()));
    r.objects(to_element_map(em.objects()));
    r.exceptions(to_element_map(em.exceptions()));

    /*
     * FIXME: For now, we must inject the root module into the element
     * collection manually. This is not ideal - we should probably
     * just process it from the root_module member variable - but this
     * will be mopped up during the formattables clean up.
     */
    insert(em.root_module(), r.modules());
    r.root_module(em.root_module().second);

    ctx.prober().end_transform(r);
    BOOST_LOG_SEV(lg, debug) << "Finished exomodel to endomodel transform.";
    return r;
}

} } }

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
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/elements_traversal.hpp"
#include "dogen/yarn/types/meta_model/exomodel.hpp"
#include "dogen/yarn/types/meta_model/endomodel.hpp"
#include "dogen/yarn/types/helpers/meta_name_factory.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/meta_naming_transform.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.meta_naming_transform"));

}

namespace dogen {
namespace yarn {
namespace transforms {

using helpers::meta_name_factory;

class updater {
public:
    void operator()(meta_model::element&) {
        /*
         * Element ignored on purpose; we cannot update non-yarn
         * meta-model elements.
         */
    }

    void operator()(meta_model::module& m) {
        static const auto n(meta_name_factory::make_module_name());
        m.meta_name(n);
    }

    void operator()(meta_model::concept& c) {
        static const auto n(meta_name_factory::make_concept_name());
        c.meta_name(n);
    }

    void operator()(meta_model::builtin& b) {
        static const auto n(meta_name_factory::make_builtin_name());
        b.meta_name(n);
    }

    void operator()(meta_model::enumeration& e) {
        static const auto n(meta_name_factory::make_enumeration_name());
        e.meta_name(n);
    }

    void operator()(meta_model::primitive& p) {
        static const auto n(meta_name_factory::make_primitive_name());
        p.meta_name(n);
    }

    void operator()(meta_model::object& o) {
        static const auto n(meta_name_factory::make_object_name());
        o.meta_name(n);
    }

    void operator()(meta_model::exception& e) {
        static const auto n(meta_name_factory::make_exception_name());
        e.meta_name(n);
    }

    void operator()(meta_model::visitor& v) {
        static const auto n(meta_name_factory::make_visitor_name());
        v.meta_name(n);
    }
};

void meta_naming_transform::transform(meta_model::exomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Starting meta-naming transform for model: "
                             << em.name().id();

    em.meta_name(meta_name_factory::make_exomodel_name());

    updater u;
    for (const auto& pair : em.modules())
        u(*pair.second);

    for (const auto& pair : em.concepts())
        u(*pair.second);

    for (const auto& pair : em.builtins())
        u(*pair.second);

    for (const auto& pair : em.enumerations())
        u(*pair.second);

    for (const auto& pair : em.primitives())
        u(*pair.second);

    for (const auto& pair : em.objects())
        u(*pair.second);

    for (const auto& pair : em.exceptions())
        u(*pair.second);

    u(*em.root_module().second);

    BOOST_LOG_SEV(lg, debug) << "Finished meta-naming transform.";

}

void meta_naming_transform::transform(meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Starting meta-naming transform for model: "
                             << im.name().id();

    im.meta_name(meta_name_factory::make_endomodel_name());

    /*
     * We are setting include_injected_elements to false by design as
     * we cannot known the correct meta-names for those types - even
     * if the types were in the model, which they aren't yet since we
     * are in the pre-processing chain. But you get the idea.
     */
    updater u;
    meta_model::elements_traversal(im, u);

    BOOST_LOG_SEV(lg, debug) << "Finished meta-naming transform.";
}

} } }

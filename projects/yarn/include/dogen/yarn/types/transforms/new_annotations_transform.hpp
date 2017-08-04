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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_NEW_ANNOTATIONS_TRANSFORM_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_NEW_ANNOTATIONS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include "dogen/annotations/types/annotation_group.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/transforms/context_fwd.hpp"
#include "dogen/yarn/types/meta_model/exogenous_model.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class new_annotations_transform final {
private:
    static annotations::annotation_group
    obtain_annotation_group(const context& ctx, annotations::scribble_group sg,
        const meta_model::element& e);

private:
    static void process_attributes(const annotations::annotation_group& ag,
        std::list<meta_model::attribute>& attrs);

private:
    static void process(const annotations::annotation_group& ag,
        meta_model::element& e);
    static void process(const annotations::annotation_group& sg,
        meta_model::concept& c);
    static void process(const annotations::annotation_group& sg,
        meta_model::object& o);

    template<typename Element>
    static void process(const context& ctx,
        std::list<std::pair<annotations::scribble_group,
        boost::shared_ptr<Element>>>& elements) {
        for (auto& pair : elements) {
            const auto& sg(pair.first);
            auto& e(*pair.second);
            const auto ag(obtain_annotation_group(ctx, sg, e));
            process(ag, e);
        }
    }

public:
    static void transform(const context& ctx, meta_model::exogenous_model& em);
};

} } }

#endif

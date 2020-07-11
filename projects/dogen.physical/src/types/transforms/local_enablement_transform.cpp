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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/types/entities/meta_name_indices.hpp"
#include "dogen.physical/io/entities/artefact_repository_io.hpp"
#include "dogen.physical/io/entities/facet_properties_io.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/local_enablement_transform.hpp"

namespace {

const std::string transform_id("physical.transforms.local_enablement_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string global_configuration_not_found(
    "Could not find global enablement configuration for formatter: ");
const std::string duplicate_archetype_name("Duplicate archetype name: ");
const std::string duplicate_element_archetype("Duplicate element archetype: ");
const std::string meta_name_not_found("Meta-name not found: ");

template <typename T>
struct scope_exit {
    scope_exit(T &&t) : t_{std::move(t)} {}
    ~scope_exit() { t_(); }
    T t_;
};

template <typename T>
scope_exit<T> make_scope_exit(T &&t) {
    return scope_exit<T> { std::move(t)}; }
}


namespace dogen::physical::transforms {

}

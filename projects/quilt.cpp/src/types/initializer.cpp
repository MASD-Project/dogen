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
#include "dogen/yarn/types/workflow.hpp"
#include "dogen/quilt/types/workflow.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"
#include "dogen/quilt.cpp/types/formattables/workflow.hpp"
#include "dogen/quilt.cpp/types/annotations/opaque_annotations_builder.hpp"
#include "dogen/quilt.cpp/types/annotations/initializer.hpp"
#include "dogen/quilt.cpp/types/formatters/initializer.hpp"
#include "dogen/quilt.cpp/types/fabric/initializer.hpp"
#include "dogen/quilt.cpp/types/formattables/registrar.hpp"
#include "dogen/quilt.cpp/types/workflow.hpp"
#include "dogen/quilt.cpp/types/initializer.hpp"

namespace dogen {
namespace quilt {
namespace cpp {

void initialize_providers(const formatters::registrar& fmt_rg) {
    auto& prop_rg(formattables::workflow::registrar());
    const auto c(fmt_rg.formatter_container());
    for (const auto& f : c.all_file_formatters())
        f->register_provider(prop_rg);
}

void initializer::initialize() {
    using annotations::opaque_annotations_builder;
    annotations::initializer::initialize(
        opaque_annotations_builder::registrar());
    formatters::initializer::initialize(formatters::workflow::registrar());
    initialize_providers(formatters::workflow::registrar());
    fabric::initializer::initialize(yarn::workflow::injector_registrar());
    quilt::register_backend<workflow>(quilt::workflow::registrar());
}

} } }

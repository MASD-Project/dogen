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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.org/io/entities/document_io.hpp"
#include "dogen.org/types/helpers/document_factory.hpp"
#include "dogen.org/types/transforms/string_to_document_transform.hpp"

namespace {

const std::string transform_id("org.transforms.string_to_document_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::org::transforms {

entities::document string_to_document_transform::
apply(boost::shared_ptr<tracing::tracer> tracer, const std::string& s) {
    tracing::scoped_transform_tracer stp(lg, "string to document",
        transform_id, "org_document", *tracer, s);

    const auto r(helpers::document_factory::make(s));
    stp.end_transform(r);
    return r;
}

}

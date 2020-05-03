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
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/text_to_text_chain.hpp"

namespace {

const std::string transform_id("text.transforms.text_to_text_chain");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string unsupported_technical_space(
    "Could not find transform for technical space: ");
const std::string disabled_transform(
    "Transform for requested technical space is disabled: ");

}

namespace dogen::text::transforms {

std::shared_ptr<text_to_text_transform_registrar>
text_to_text_chain::registrar_;

text_to_text_transform_registrar&
text_to_text_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<text_to_text_transform_registrar>();

    return *registrar_;
}

void text_to_text_chain::apply(const text::transforms::context& ctx,
    text::entities::model& m) {
    tracing::scoped_chain_tracer stp(lg, "text to text chain", transform_id,
        m.name().qualified().dot(), *ctx.tracer(), m);

    stp.end_chain(m);
}

}

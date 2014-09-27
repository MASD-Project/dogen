/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/dia/types/hydrator.hpp"
#include "dogen/dia_to_sml/types/workflow.hpp"
#include "dogen/frontend/types/dia_source.hpp"

using namespace dogen::utility::log;

namespace {

const std::string id("frontend.dia_source");
const std::list<std::string> extensions({ ".dia" });
auto lg(logger_factory(id));
const std::string empty;

}

namespace dogen {
namespace frontend {

std::string dia_source::id() const {
    return ::id;
}

std::list<std::string> dia_source::supported_extensions() const {
    return ::extensions;
}

sml::model dia_source::
read(const input_descriptor& id, const source_settings& ss) {
    dia::hydrator h(id.path());
    dia::diagram d(h.hydrate());

    const bool dmp(ss.disable_model_module());
    const std::string model_name(id.path().stem().string());
    const std::string name(dmp ? empty : model_name);

    dogen::dia_to_sml::workflow w;
    return w.execute(d, name, id.external_module_path(), id.is_target());
}

} }

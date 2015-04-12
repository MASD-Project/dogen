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
#include "dogen/utility/log/logger.hpp"
#include "dogen/stitch/types/formatter.hpp"

namespace {

const std::string model_name("stitch");
const std::string facet_name;
const std::string formatter_name("stitch.formatter");
const std::string group_name;

using namespace dogen::utility::log;
static logger lg(logger_factory("stitch.formatters"));

}

namespace dogen {
namespace stitch {

dynamic::schema::ownership_hierarchy formatter::ownership_hierarchy() const {
    static dynamic::schema::ownership_hierarchy
        r(model_name, facet_name, formatter_name, group_name);
    return r;
}

dogen::formatters::file formatter::format(const text_template& /*tt*/) const {
    dogen::formatters::file r;
    return r;
}

} }

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
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/stitch_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formatters.stitch_formatter"));

const std::string stitch_extension(".stitch");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

stitch_formatter::stitch_formatter(const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& af,
    const dogen::formatters::repository& frp)
    : instantiator_(atrp, af, frp) {}

bool stitch_formatter::is_header(const inclusion_support_types ist) const {
    return
        ist == inclusion_support_types::regular_support ||
        ist == inclusion_support_types::canonical_support;
}

dogen::formatters::artefact stitch_formatter::
format(const artefact_formatter_interface& stock_formatter, const context& ctx,
    const yarn::element& e) const {
    const auto al(stock_formatter.archetype_location());
    const auto needs_guard(is_header(stock_formatter.inclusion_support_type()));
    const auto id(e.name().id());

    assistant a(ctx, al, needs_guard, id);
    const auto& fp(a.artefact_properties().file_path());
    boost::filesystem::path stitch_template(fp);
    stitch_template.replace_extension(stitch_extension);

    auto r(instantiator_.instantiate(stitch_template));
    r.overwrite(a.artefact_properties().overwrite());
    return r;
}

} } } }

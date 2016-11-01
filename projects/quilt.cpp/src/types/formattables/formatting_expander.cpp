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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/formatting_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.formatting_expander"));

const std::string stock_style("stock");
const std::string wale_style("wale");
const std::string stitch_style("stitch");
const std::string stitch_wale_style("stitch_wale");

const std::string invalid_style("Formatting style is not valid:");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::ostream&
operator<<(std::ostream& s, const formatting_expander::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "formatting_expander::type_group\"" << ", "
      << "\"formatting_style\": " << v.formatting_style << ", "
      << "\"formatting_input\": " << v.formatting_input
      << " }";

    return s;
}

std::unordered_map<std::string, formatting_expander::type_group>
formatting_expander::make_type_groups(const annotations::type_repository& atrp,
    const formatters::repository& frp) const {

    BOOST_LOG_SEV(lg, debug) << "Creating type groups.";

    std::unordered_map<std::string, formatting_expander::type_group> r;
    for (const auto f : frp.stock_artefact_formatters()) {
        const auto& al(f->archetype_location());
        const auto arch(al.archetype());

        type_group tg;
        const annotations::type_repository_selector s(atrp);
        const auto fs(traits::cpp::formatting_style());
        tg.formatting_style = s.select_type_by_name(arch, fs);

        const auto fi(traits::cpp::formatting_input());
        tg.formatting_input = s.select_type_by_name(arch, fi);

        r[arch] = tg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created type groups. Result: " << r;
    return r;
}

formatting_styles
formatting_expander::to_formatting_style(const std::string& s) const {
    if (s == stock_style)
        return formatting_styles::stock;
    else if (s == wale_style)
        return formatting_styles::wale;
    else if (s == stitch_style)
        return formatting_styles::stitch;
    else if (s == stitch_wale_style)
        return formatting_styles::stitch_wale;

    BOOST_LOG_SEV(lg, error) << invalid_style << s;
    BOOST_THROW_EXCEPTION(expansion_error(invalid_style + s));
}

std::unordered_map<std::string, formatting_configuration>
formatting_expander::make_formatting_configuration(
    const std::unordered_map<std::string, type_group>& tgs,
    const annotations::annotation& a) const {
    std::unordered_map<std::string, formatting_configuration> r;

    const annotations::entry_selector s(a);
    for (const auto& pair : tgs) {
        const auto arch(pair.first);
        const auto& tg(pair.second);

        bool found(false);
        formatting_configuration cfg;
        const auto fs(tg.formatting_style);
        if (s.has_entry(fs)) {
            found = true;
            cfg.style(to_formatting_style(s.get_text_content(fs)));
        }

        const auto fi(tg.formatting_input);
        if (s.has_entry(fi)) {
            found = true;
            cfg.input(s.get_text_content(fi));
        }

        if (found)
            r[arch] = cfg;
    }
    return r;
}

void formatting_expander::expand(const annotations::type_repository& atrp,
    const formatters::repository& frp, model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started expanding formatting properties.";
    const auto tgs(make_type_groups(atrp, frp));
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        auto& formattable(pair.second);

        const auto& e(*formattable.master_segment());
        const auto cfgs(make_formatting_configuration(tgs, e.annotation()));

        auto& eprops(formattable.element_properties());
        auto& art_props(eprops.artefact_properties());

        for (auto& pair : art_props) {
            const auto arch(pair.first);
            auto& art_prop(pair.second);
            const auto i(cfgs.find(arch));
            if (i == cfgs.end()) {
                art_prop.formatting_style(formatting_styles::stock);
                continue;
            }
            const auto& cfg(i->second);
            art_prop.formatting_style(cfg.style());
            art_prop.formatting_input(cfg.input());
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finishedexpanding formatting properties.";
}

} } } }

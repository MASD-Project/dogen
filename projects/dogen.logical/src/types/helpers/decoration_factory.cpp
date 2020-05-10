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
#include <boost/lexical_cast.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/formatters/comment_style.hpp"
#include "dogen.logical/io/entities/decoration/element_properties_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/entities/decoration/licence.hpp"
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/types/helpers/building_error.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/formatters/decoration_formatter.hpp"
#include "dogen.logical/types/helpers/decoration_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("logical.helpers.decoration_factory"));

const std::string empty;
const std::string technical_space_not_found("Technical space not found: ");
const std::string licence_not_found("Licence not found: ");
const std::string modeline_group_not_found("Modeline group not found: ");
const std::string modeline_not_found("Modeline not found: ");
const std::string generation_marker_not_found("Generation marker not found: ");

}

namespace dogen::logical::helpers {

decoration_factory::
decoration_factory(const helpers::decoration_repository& drp,
    const std::string& activity_timestamp, const std::string& origin_sha1_hash)
    : decoration_repository_(drp), activity_timestamp_(activity_timestamp),
    origin_sha1_hash_(origin_sha1_hash) {}

std::string decoration_factory::
get_short_form_licence(const std::string& licence_name) const {
    if (licence_name.empty())
        return empty;

    const auto& map(decoration_repository_.licences_by_name());
    const auto i(map.find(licence_name));
    if (i == map.end()) {
        BOOST_LOG_SEV(lg, error) << licence_not_found << licence_name;
        BOOST_THROW_EXCEPTION(
            building_error(licence_not_found + licence_name));
    }
    return i->second->short_form();
}

boost::shared_ptr<entities::decoration::modeline> decoration_factory::
get_modeline(const std::string& modeline_group_name,
    const logical::entities::technical_space ts) const {

    if (modeline_group_name.empty())
        return boost::shared_ptr<entities::decoration::modeline>();

    const auto& drp(decoration_repository_);
    const auto& mg_map(drp.modelines_by_modeline_group_by_technical_space());
    const auto i(mg_map.find(modeline_group_name));
    if (i == mg_map.end()) {
        BOOST_LOG_SEV(lg, error) << modeline_group_not_found
                                 << modeline_group_name;
        BOOST_THROW_EXCEPTION(building_error(
                modeline_group_not_found + modeline_group_name));
    }

    const auto& ts_map(i->second);
    const auto j(ts_map.find(ts));
    if (j == ts_map.end()) {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << technical_space_not_found
                                 << s << " For modeline group: "
                                 << modeline_group_name;
        BOOST_THROW_EXCEPTION(building_error(technical_space_not_found + s));
    }
    return j->second;
}

boost::shared_ptr<logical::entities::decoration::generation_marker>
decoration_factory::
get_generation_marker(const std::string& generation_marker_name) const {
    if (generation_marker_name.empty())
        return boost::shared_ptr<entities::decoration::generation_marker>();

    const auto& map(decoration_repository_.generation_markers_by_name());
    const auto i(map.find(generation_marker_name));
    if (i == map.end()) {
        BOOST_LOG_SEV(lg, error) << generation_marker_not_found
                                 << generation_marker_name;
        BOOST_THROW_EXCEPTION(building_error(generation_marker_not_found
                + generation_marker_name));
    }
    return i->second;
}

boost::optional<logical::entities::decoration::element_properties>
decoration_factory::make_decoration(const std::string& licence_text,
    const boost::shared_ptr<logical::entities::decoration::modeline> ml,
    const boost::shared_ptr<
    logical::entities::decoration::generation_marker> gm,
    const std::list<std::string>& copyright_notices,
    const logical::entities::technical_space ts) const {

    /*
     * Create the preamble and postamble for the decoration, taking
     * into account the element's technical space.
     */
    using utility::formatters::comment_style;
    using logical::entities::technical_space;

    std::ostringstream preamble_stream;
    formatters::decoration_formatter df;
    if (ts == technical_space::cpp) {
        df.format_preamble(preamble_stream,
            comment_style::cpp_style/*single line*/,
            comment_style::c_style/*multi-line*/,
            licence_text, copyright_notices,
            activity_timestamp_, origin_sha1_hash_, ml, gm);
    } else if (ts == technical_space::csharp) {
        df.format_preamble(preamble_stream,
            comment_style::csharp_style, licence_text, copyright_notices,
            activity_timestamp_, origin_sha1_hash_, ml, gm);
    } else if (ts == technical_space::cmake || ts == technical_space::odb) {
        df.format_preamble(preamble_stream,
            comment_style::shell_style, licence_text,
            copyright_notices, activity_timestamp_, origin_sha1_hash_, ml, gm);
    } else if (ts == technical_space::xml) {
        df.format_preamble(preamble_stream,
            comment_style::xml_style, licence_text,
            copyright_notices, activity_timestamp_, origin_sha1_hash_, ml, gm);
    }

    std::ostringstream postamble_stream;
    if (ts == technical_space::cpp)
        df.format_postamble(postamble_stream, comment_style::c_style, ml);
    else if (ts == technical_space::csharp)
        df.format_postamble(postamble_stream, comment_style::csharp_style, ml);

    logical::entities::decoration::element_properties r;
    r.preamble(preamble_stream.str());
    r.postamble(postamble_stream.str());
    return r;
}


boost::optional<logical::entities::decoration::element_properties>
decoration_factory::make_global_decoration(
    const boost::optional<helpers::decoration_configuration> root_dc,
    const logical::entities::technical_space ts) const {
    /*
     * If there is no decoration configuration there shall be no
     * decoration either.
     */
    typedef boost::optional<
        logical::entities::decoration::element_properties> empty_decorations;
    if (!root_dc)
        return empty_decorations();

    /*
     * If the user did not specifically enable decoration in the
     * configuration, there shall be no decoration. Its somewhat
     * confusing that "enabled" is optional here. This makes no sense
     * at the global level, since not supplying the flag is the same
     * as set it to false. However, we also need to cater for the
     * local usage, where we need to be able to distinguish between
     * not supplying the flag versus supplying it and setting it to
     * false.
     */
    const auto& dc(*root_dc);
    if (!dc.enabled() || !(*dc.enabled()))
        return empty_decorations();

    /*
     * Obtain all decoration inputs and create the decoration.
     */
    const auto l(get_short_form_licence(dc.licence_name()));
    const auto ml(get_modeline(dc.modeline_group_name(), ts));
    const auto gm(get_generation_marker(dc.marker_name()));
    const auto r(make_decoration(l, ml, gm, dc.copyright_notices(), ts));

    BOOST_LOG_SEV(lg, trace) << "Created global decoration: " << r;
    return r;
}

boost::optional<logical::entities::decoration::element_properties>
decoration_factory::make_local_decoration(const boost::optional<
    logical::entities::decoration::element_properties> global_decoration,
    const boost::optional<helpers::decoration_configuration>& root_dc,
    const boost::optional<helpers::decoration_configuration> element_dc,
    const logical::entities::technical_space ts) const {
    BOOST_LOG_SEV(lg, trace) << "Creating local decoration.";

    /*
     * If there is no local decoration configuration, we just default
     * to the global one whatever it may be - i.e. it may itself not
     * exist either.
     */
    if (!element_dc) {
        BOOST_LOG_SEV(lg, trace) << "No element decoration. "
                                 << "Using global decoration.";
        return global_decoration;
    }

    /*
     * If the user specifically disabled decoration for this modeling
     * element, or if decorations are not enabled locally or globally,
     * there's nothing to do.
     */
    const auto& dc(*element_dc);
    const bool enabled_locally(dc.enabled() && *dc.enabled());
    const bool disabled_locally(dc.enabled() && !(*dc.enabled()));
    const bool enabled_globally(root_dc && root_dc->enabled() &&
        *root_dc->enabled());
    if (disabled_locally || (!enabled_locally && !enabled_globally)) {
        BOOST_LOG_SEV(lg, trace) << "Decoration not enabled. "
                                 << " enabled_locally: " << enabled_locally
                                 << " disabled_locally: " << disabled_locally
                                 << " enabled_globally: " << enabled_globally;
        return boost::optional<
            entities::decoration::element_properties>();
    }

    /*
     * If there are no local overrides, then just use the global
     * decoration. User just got confused.
     */
    if (dc.copyright_notices().empty() &&
        dc.licence_name().empty() && dc.modeline_group_name().empty() &&
        dc.marker_name().empty()) {
        BOOST_LOG_SEV(lg, trace) << "No overiddes. Using global decoration.";
        return global_decoration;
    }

    /*
     * Retrieve the local decoration inputs.
     */
    const auto ol(get_short_form_licence(dc.licence_name()));
    const auto oml(get_modeline(dc.modeline_group_name(), ts));
    const auto ogm(get_generation_marker(dc.marker_name()));

    /*
     * If we do not have a global decoration configuration, we do not
     * have to worry about overrides, just with processing local
     * decoration configuration.
     */
    if (!root_dc) {
        const auto r(make_decoration(ol, oml, ogm, dc.copyright_notices(), ts));
        BOOST_LOG_SEV(lg, trace) << "Created local decoration without "
                                 << "overrides: " << r;
        return r;
    }

    /*
     * Handle the global overrides.
     */
    const auto overriden_licence(!ol.empty() ? ol :
        get_short_form_licence(root_dc->licence_name()));
    const auto overriden_modeline(oml ? oml :
        get_modeline(root_dc->modeline_group_name(), ts));
    const auto overriden_marker(ogm ? ogm :
        get_generation_marker(root_dc->marker_name()));
    const auto overriden_copyright_notices(!dc.copyright_notices().empty() ?
        dc.copyright_notices() : root_dc->copyright_notices());
    const auto r(make_decoration(overriden_licence, overriden_modeline,
            overriden_marker, overriden_copyright_notices, ts));

    BOOST_LOG_SEV(lg, trace) << "Created local decoration with overrides: "
                             << r;
    return r;
}

}

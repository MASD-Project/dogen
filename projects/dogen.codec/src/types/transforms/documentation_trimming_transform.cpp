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
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include "dogen.codec/types/entities/comment.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/types/transforms/context.hpp"
#include "dogen.codec/types/transforms/documentation_trimming_transform.hpp"

namespace {

const std::string transform_id(
    "codec.transforms.documentation_trimming_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string stereotypes_tag("masd.codec.stereotypes");
const std::string generation_marker_value(
    "masd::decoration::generation_marker");

}

namespace dogen::codec::transforms {

void documentation_trimming_transform::trim(std::string& s) {
    /*
     * Do not use "trim" as it also removes spaces in the middle
     * of the string.
     */
    boost::algorithm::trim_left(s);
    boost::algorithm::trim_right(s);
}

void documentation_trimming_transform::
trim(entities::comment& c, const bool add_trailing_new_line) {
    auto s(c.documentation());
    BOOST_LOG_SEV(lg, trace) << "Before trimming: '" << s << "'";
    trim(s);
    if (add_trailing_new_line) {
        std::ostringstream os;
        os << s << std::endl;
        c.documentation(os.str());
    } else
        c.documentation(s);
    BOOST_LOG_SEV(lg, trace) << "After trimming: '" << c.documentation() << "'";
}

bool documentation_trimming_transform::
is_generation_marker(const entities::element& e) {
    for (const auto& st : e.stereotypes()) {
        BOOST_LOG_SEV(lg, debug) << "Processing stereotype: '"
                                 << st.value() << "'";
        if (boost::contains(st.value(), generation_marker_value))
            return true;
    }

    for (const auto& tv : e.tagged_values()) {
        BOOST_LOG_SEV(lg, debug) << "Processing: '" << tv.tag() << "'"
                                 << " value: '" << tv.value() << "'";
        if (tv.tag() == stereotypes_tag &&
            boost::contains(tv.value(), generation_marker_value))
            return true;
    }
    return false;
}

void documentation_trimming_transform::process_element(entities::element& e) {
    BOOST_LOG_SEV(lg, debug) << "Processing: " << e.name().simple();

    /*
     * The message in the generation marker will lose its end-line due
     * to trimming. However, the end-line is required to separate the
     * different components of the generation marker. So we need to
     * reintroduce the new-line manually. This is a hack to
     * accommodate for how new lines work in org-mode.
     */
    const auto add_trailing_new_line(is_generation_marker(e));
    BOOST_LOG_SEV(lg, debug) << "Add trailing new line: "
                             << add_trailing_new_line;

    if (!e.comment().documentation().empty())
        trim(e.comment(), add_trailing_new_line);
    else
        BOOST_LOG_SEV(lg, debug) << "Element documentation is empty.";

    for (auto& attr : e.attributes()) {
        BOOST_LOG_SEV(lg, debug) << "Processing attribute: "
                                 << attr.name().simple();
        if (!attr.comment().documentation().empty())
            trim(attr.comment(), add_trailing_new_line);
        else
            BOOST_LOG_SEV(lg, debug) << "Attribute documentation is empty.";
    }
}

void documentation_trimming_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "documentation trimming",
        transform_id, m.name().simple(), *ctx.tracer(), m);

    BOOST_LOG_SEV(lg, debug) << "Transforming model: " << m.name().simple();
    if (!m.comment().documentation().empty()) {
        trim(m.comment());
    } else
        BOOST_LOG_SEV(lg, debug) << "Model documentation is empty.";

    for (auto& e : m.elements())
        process_element(e);

    stp.end_transform(m);
}

}

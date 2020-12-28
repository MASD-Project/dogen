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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen.org/types/entities/block_type.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.org/io/entities/document_io.hpp"
#include "dogen.org/types/helpers/document_factory.hpp"
#include "dogen.org/types/transforms/transformation_error.hpp"
#include "dogen.org/types/transforms/document_to_string_transform.hpp"

namespace {

const std::string transform_id("org.transforms.document_to_string_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;

const std::string unexpected_tag_count("Expected 0 or 1 tags.");

}

namespace dogen::org::transforms {

void document_to_string_transform::render_drawers(std::ostream& os,
    const unsigned int level, const std::list<entities::drawer>& ds) {
    const std::string spaces([&]() {
        if (level == 0)
            return empty;
        return std::string(level + 1, ' ');
    }());

    for (const auto& d : ds) {
        if (d.contents().empty())
            return;

        os << spaces << ":PROPERTIES:" << std::endl;
        for (const auto& dc : d.contents())
            os << spaces << ":" << dc.key() << ": " << dc.value() << std::endl;
        os << spaces << ":END:" << std::endl;
    }
}

void document_to_string_transform::
render_section(std::ostream& os, const entities::section& sec) {
    if (sec.blocks().empty())
        return;

    os << std::endl;
    for (const auto& b : sec.blocks()) {
        using entities::block_type;
        const bool is_greater_block(b.type() == block_type::greater_block);
        if (is_greater_block) {
            if (b.parameters().empty())
                os << "#+begin_example";
            else {
                os << "#+begin_src";
                for (const auto& p : b.parameters())
                    os << " " << p.value();
            }
            os << std::endl;
        }

        os << b.contents() << std::endl;

        if (is_greater_block) {
            if (b.parameters().empty())
                os << "#+end_example";
            else
                os << "#+end_src";
            os << std::endl;
        }
    }
}

void document_to_string_transform::render_headline(std::ostream& os,
    const entities::headline& h) {
    const std::string stars(h.level(), '*');
    os << stars << " " << h.title();

    if (h.tags().size() > 1) {
        BOOST_LOG_SEV(lg, error) << unexpected_tag_count;
        BOOST_THROW_EXCEPTION(transformation_error(unexpected_tag_count));
    } else if (h.tags().size() == 1) {
        const auto tag(":" + h.tags().front().value() + ":");
        const auto tag_space_count(77 - tag.size() - h.title().size() - 1
            - stars.size());
        const std::string tag_spaces(tag_space_count > 0 ?
            tag_space_count : 1, ' ');
        os << tag_spaces << tag;
    }

    os << std::endl;

    render_drawers(os, h.level(), h.drawers());
    render_section(os, h.section());

    for (const auto& child : h.headlines())
        render_headline(os, child);
}

std::string
document_to_string_transform::apply(boost::shared_ptr<tracing::tracer> tracer,
    const entities::document& doc) {

    tracing::scoped_transform_tracer stp(lg, "document to string",
        transform_id, "org_document", *tracer, doc);

    std::ostringstream os;
    for (const auto& ak : doc.affiliated_keywords())
        os << "#+" << ak.key() << ": " << ak.value() << std::endl;

    render_drawers(os, 0/*level*/, doc.drawers());
    render_section(os, doc.section());

    for (const auto& child : doc.headlines())
        render_headline(os, child);

    const std::string r(os.str());
    stp.end_transform(r);
    return r;
}

}

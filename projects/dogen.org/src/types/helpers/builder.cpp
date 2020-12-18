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
#include <regex>
#include <boost/make_shared.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.org/types/helpers/node.hpp"
#include "dogen.org/io/entities/document_io.hpp"
#include "dogen.org/types/helpers/building_error.hpp"
#include "dogen.org/types/helpers/builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("org.helpers.builder"));

const std::regex headline_regex("^\\*+\\s");

}

namespace dogen::org::helpers {

using entities::block_type;

builder::builder() : block_type_(block_type::invalid),
                     root_(boost::make_shared<node>()) {
    root_->current().level(0);
    stack_.push(root_);
}

void builder::end_current_block() {
    const std::string content(stream_.str());
    stream_.str("");

    if (content.empty())
        return;

    entities::block tb;
    tb.type(block_type_);
    tb.contents(content);
    stack_.top()->current().section().blocks().push_back(tb);
}

void builder::add_line(const std::string& s) {
    BOOST_LOG_SEV(lg, debug) << "Processing line: " << s;

    if (std::regex_match(s, headline_regex)) {
        end_current_block();

        // r.headlines(parse_headline(is, line));
    } else {
        /*
         * If we don't have a specific block type, default it to
         * regular text.
         */
        if (block_type_ == block_type::invalid)
            block_type_ = block_type::text_block;

        stream_ << s;
    }
}

entities::headline builder::make_headline(boost::shared_ptr<node> n) const {
    entities::headline r(n->current());
    BOOST_LOG_SEV(lg, debug) << "Processing headline: " << r.title();

    for (const auto& child : n->children())
        r.headlines().push_back(make_headline(child));

    BOOST_LOG_SEV(lg, debug) << "Processing headline: " << r.title();

    return r;
}

entities::document builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Building document.";

    /*
     * Flush any pending content we may have.
     */
    end_current_block();

    entities::document r;
    const auto& c(root_->current());
    r.affiliated_keywords(c.affiliated_keywords());
    r.drawers(c.drawers());
    r.section(c.section());

    for (const auto& child : root_->children())
        r.headlines().push_back(make_headline(child));

    BOOST_LOG_SEV(lg, debug) << "Finished building. Result: " << r;
    return r;
}

}

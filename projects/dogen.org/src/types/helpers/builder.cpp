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
#include <boost/make_shared.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.org/types/helpers/node.hpp"
#include "dogen.org/io/entities/document_io.hpp"
#include "dogen.org/types/helpers/building_error.hpp"
#include "dogen.org/types/helpers/parser.hpp"
#include "dogen.org/types/helpers/builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("org.helpers.builder"));

const std::string unexpected_level("Headline is at an unexpected level.");
const std::string empty_stack("Stack is empty, expected content");

}

namespace dogen::org::helpers {

using entities::block_type;

builder::builder() : block_type_(block_type::invalid),
                     root_(boost::make_shared<node>()) {
    root_->current().level(0);
    stack_.push(root_);
}

void builder::ensure_stack_not_empty() const {
    if (stack_.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_stack;
        BOOST_THROW_EXCEPTION(building_error(empty_stack));
    }
}
void builder::ensure_expected_headline_level(const unsigned int expected,
    const unsigned int actual) const {

    if (expected == actual)
        return;

    std::ostringstream os;
    os << unexpected_level << "expected: " << expected
       << " but found " << actual;
    const std::string msg(os.str());
    BOOST_LOG_SEV(lg, error) << msg;
    BOOST_THROW_EXCEPTION(building_error(msg));
}

void builder::end_current_block() {
    BOOST_LOG_SEV(lg, debug) << "Ending current block.";
    const std::string content(stream_.str());
    stream_.str("");

    BOOST_LOG_SEV(lg, trace) << "Block contents: '" << content << "'";
    if (content.empty()) {
        BOOST_LOG_SEV(lg, trace) << "Block is empty, ignoring.";
        return;
    }

    /*
     * If there are contents for the current block, we need to add it
     * to the headline currently on top.
     */
    entities::block tb;
    tb.type(block_type_);
    tb.contents(content);
    stack_.top()->current().section().blocks().push_back(tb);
    block_type_ = block_type::invalid;
}

void builder::handle_headline(const entities::headline& hl) {
    /*
     * We found a headline. We need to detect if the headline is a
     * sibling or a children of the current level.
     */
    BOOST_LOG_SEV(lg, debug) << "Line is a headline. Level: " << hl.level();
    const unsigned int sz(static_cast<unsigned int>(stack_.size()));
    BOOST_LOG_SEV(lg, debug) << "Stack size: " << sz;

    /*
     * If the number of elements in the stack matches the current
     * level, that must mean the headline we're processing is a child
     * of the current headline. Let's look at the two possibilities:
     * we're either the root node or any other node.
     *
     * If we're the root node, the "actual" present level is zero, but
     * because the root also counts it becomes one. Similarly, if
     * we're any other node, then the "actual" present level is (stack
     * size - 1). Thus if the headline level is exactly the same as
     * the stack size, it must mean we are at the same level of the
     * current node and therefore are a sibling.
     */
    if (sz == hl.level()) {
        /*
         * Create the node for the new headline and update the stack.
         */
        auto child(boost::make_shared<node>());
        child->current(hl);

        auto& current(*stack_.top());
        current.children().push_back(child);
        stack_.push(child);
        return;
    }

    /*
     * If the stack is one smaller than the current headline level,
     * this means we have a sibling. We just need to go up to the
     * parent level to add the sibling and then make it the front of
     * the stack.
     */
    if (sz + 1 == hl.level()) {
        stack_.pop();
        auto& current(*stack_.top());
        auto child(boost::make_shared<node>());
        child->current(hl);
        current.children().push_back(child);
        stack_.push(child);
    }

    /*
     * Finally, the only remaining possibility is that we are now
     * going "up" in the hierarchy - that is, we are adding children
     * to one of our parent's parent. However, for this to be the
     * case, the stack size must be greater than the headline level.
     */
    if (sz < hl.level()) {
        std::ostringstream os;
        os << "unexpected stack size: " << sz
           << " Level: " << hl.level();
        const std::string msg(os.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(building_error(msg));
    }
    const auto number_of_pops(sz - hl.level());
    BOOST_LOG_SEV(lg, debug) << "Popping stack: " << number_of_pops;
    for (unsigned int i = 0; i < number_of_pops; ++i)
        stack_.pop();

    ensure_stack_not_empty();
    auto& current(*stack_.top());
    auto child(boost::make_shared<node>());
    child->current(hl);
    current.children().push_back(child);
    stack_.push(child);
}

void builder::add_line(const std::string& s) {
    ensure_stack_not_empty();
    BOOST_LOG_SEV(lg, debug) << "Processing line: '" << s << "'";

    /*
     * First we try to parse the line as if it was a headline.
     */
    const auto oh(parser::try_parse_headline(s));
    if (oh) {
        /*
         * Flush any pending content we may have.
         */
        end_current_block();

        /*
         * Handle the new incoming headline.
         */
        handle_headline(*oh);
        return;
    }

    /*
     * Next we try to parse it as an affiliated keyword.
     */
    const auto oak(parser::try_parse_affiliated_keyword(s));
    if (oak) {
        /*
         * Flush any pending content we may have.
         */
        end_current_block();

        /*
         * Add the affiliated keywords to the current node.
         */
        auto& top(*stack_.top());
        top.current().affiliated_keywords().push_back(*oak);
        return;
    }

    /*
     * Finally, if nothing else matches, it must be a text block. If
     * we don't have a specific block type, default it to regular
     * text.
     */
    if (block_type_ == block_type::invalid) {
        BOOST_LOG_SEV(lg, debug) << "Adding to block as first line.";
        block_type_ = block_type::text_block;
        stream_ << s;
    } else {
        BOOST_LOG_SEV(lg, debug) << "Adding to block.";
        stream_ << std::endl << s;
    }
}

entities::headline builder::make_headline(boost::shared_ptr<node> n) const {
    entities::headline r(n->current());
    BOOST_LOG_SEV(lg, debug) << "Processing headline: " << r.title();

    for (const auto& child : n->children())
        r.headlines().push_back(make_headline(child));

    return r;
}

entities::document builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Building document.";

    /*
     * Flush any pending content we may have.
     */
    end_current_block();

    /*
     * Create the document from the root node.
     */
    entities::document r;
    const auto& c(root_->current());
    r.affiliated_keywords(c.affiliated_keywords());
    r.drawers(c.drawers());
    r.section(c.section());

    /*
     * Now recurse through the nodes, creating the correct headline
     * structure.
     */
    for (const auto& child : root_->children())
        r.headlines().push_back(make_headline(child));

    BOOST_LOG_SEV(lg, debug) << "Finished building. Result: " << r;
    return r;
}

}

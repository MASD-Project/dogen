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
#include <boost/make_shared.hpp>
#include "dogen.org/types/entities/block_type.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.org/types/helpers/node.hpp"
#include "dogen.org/io/entities/document_io.hpp"
#include "dogen.org/types/helpers/building_error.hpp"
#include "dogen.org/types/helpers/parser.hpp"
#include "dogen.org/io/entities/block_type_io.hpp"
#include "dogen.org/types/helpers/builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("org.helpers.builder"));

const std::string unexpected_level("Headline is at an unexpected level.");
const std::string empty_stack("Stack is empty, expected content");
const std::string invalid_drawer("Drawer contains drawer: ");
const std::string empty_drawers("Expected at least one drawer.");
const std::string invalid_block("Block contains block: ");
const std::string unfinished_block("No end block found.");
const std::string empty_blocks("No blocks found.");
const std::string unexpected_block_type("Unexpected block type: ");

}

namespace dogen::org::helpers {

using entities::block_type;

builder::builder() : root_(boost::make_shared<node>()),
                     in_drawer_(false),
                     in_greater_block_(false),
                     is_first_line_(true),
                     line_number_(0) {
    root_->data().level(0);
    stack_.push(root_);
}

void builder::ensure_stack_not_empty() const {
    if (stack_.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_stack;
        BOOST_THROW_EXCEPTION(building_error(empty_stack));
    }
}

node& builder::top() const {
    ensure_stack_not_empty();
    return *stack_.top();
}

void builder::end_text_block() {
    if (in_greater_block_) {
        BOOST_LOG_SEV(lg, error) << unfinished_block;
        BOOST_THROW_EXCEPTION(building_error(unfinished_block));
    }

    BOOST_LOG_SEV(lg, debug) << "Ending current block.";
    const std::string content(stream_.str());
    stream_.str("");

    BOOST_LOG_SEV(lg, trace) << "Block contents: '" << content << "'";
    if (content.empty()) {
        BOOST_LOG_SEV(lg, trace) << "Block is empty, ignoring.";
        return;
    }

    /*
     * If there are contents for the current text block, we need to
     * add it to the headline currently on top.
     */
    entities::block tb;
    tb.type(block_type::text_block);
    tb.contents(content);
    top().data().section().blocks().push_back(tb);
    is_first_line_ = true;
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
        child->data(hl);

        top().children().push_back(child);
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
        auto child(boost::make_shared<node>());
        child->data(hl);

        top().children().push_back(child);
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
        os << "unexpected stack size: " << sz << " Level: " << hl.level();
        const std::string msg(os.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(building_error(msg));
    }

    const auto number_of_pops(sz - hl.level());
    BOOST_LOG_SEV(lg, debug) << "Popping stack: " << number_of_pops;
    for (unsigned int i = 0; i < number_of_pops; ++i)
        stack_.pop();

    auto child(boost::make_shared<node>());
    child->data(hl);

    top().children().push_back(child);
    stack_.push(child);
}

entities::headline builder::make_headline(boost::shared_ptr<node> n) const {
    entities::headline r(n->data());
    BOOST_LOG_SEV(lg, debug) << "Processing headline: " << r.title();

    for (const auto& child : n->children())
        r.headlines().push_back(make_headline(child));

    return r;
}

void builder::add_line(const std::string& s) {
    ensure_stack_not_empty();
    ++line_number_;
    BOOST_LOG_SEV(lg, debug) << "Processing line number: "
                             << line_number_ << ". Contents: "
                             << s << "'";

    /*
     * First we try to parse the line as if it was a headline.
     */
    const auto oh(parser::try_parse_headline(s, line_number_));
    if (oh) {
        /*
         * Flush any pending content we may have.
         */
        end_text_block();

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
        end_text_block();

        /*
         * Add the affiliated keywords to the current node.
         */
        top().data().affiliated_keywords().push_back(*oak);
        return;
    }

    /*
     * Handle greater blocks before drawers.
     */
    const auto ob(parser::try_parse_greater_block_start(s));
    if (ob) {
        /*
         * Blocks cannot be inside of blocks or drawers.
         */
        if (in_greater_block_ || in_drawer_) {
            BOOST_LOG_SEV(lg, error) << invalid_block << s;
            BOOST_THROW_EXCEPTION(building_error(invalid_block + s));
        }

        /*
         * Flush any pending content we may have into a text block.
         */
        end_text_block();

        /*
         * Add the block to the current node.
         */
        in_greater_block_ = true;
        top().data().section().blocks().push_back(*ob);
        BOOST_LOG_SEV(lg, debug) << "Started a new greater block.";
        return;
    }

    /*
     * If we're inside of a greater block (i.e. not a text block),
     * there are only two valid possibilities: either we are adding
     * content, or finishing it.
     */
    if (in_greater_block_) {
        /*
         * If we're working on a greater block, we expect to see it in
         * the collection.
         */
        auto& blocks(top().data().section().blocks());
        if (blocks.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_blocks;
            BOOST_THROW_EXCEPTION(building_error(empty_blocks));
        }

        /*
         * Ensure the block is of the expected type.
         */
        auto& block(blocks.back());
        if (block.type() != entities::block_type::greater_block) {
            const std::string s(boost::lexical_cast<std::string>(block.type()));
            BOOST_LOG_SEV(lg, error) << unexpected_block_type << s;
            BOOST_THROW_EXCEPTION(building_error(unexpected_block_type + s));
        }

        /*
         * Attempt to detect the end of a greater block. Note that if we do have
         * an end of block but it does not match the current block's
         * name, the parser will throw.
         */
        if (parser::is_greater_block_end(s, block.name())) {
            const std::string content(stream_.str());
            stream_.str("");
            block.contents(content);
            in_greater_block_ = false;
            is_first_line_ = true;
        } else {
            /*
             * Add content to the greater block.
             */
            if (is_first_line_) {
                BOOST_LOG_SEV(lg, debug) << "Add first line to greater block.";
                is_first_line_ = false;
                stream_ << s;
            } else {
                BOOST_LOG_SEV(lg, debug) << "Add line to greater block.";
                stream_ << std::endl << s;
            }
        }
        return;
    }

    /*
     * Now handle the drawers.
     */
    const auto od(parser::try_parse_drawer_start(s));
    if (od) {
        /*
         * Drawers cannot be inside of drawers.
         */
        if (in_drawer_) {
            BOOST_LOG_SEV(lg, error) << invalid_drawer << s;
            BOOST_THROW_EXCEPTION(building_error(invalid_drawer + s));
        }
        in_drawer_ = true;

        /*
         * Flush any pending content we may have.
         */
        end_text_block();

        /*
         * Add the drawer to the current node.
         */
        top().data().drawers().push_back(*od);
        return;
    }

    /*
     * If we're inside of a drawer, there are only two valid
     * possibilities: either we are adding content to the drawer, or
     * finishing it.
     */
    if (in_drawer_) {
        if (parser::is_drawer_end(s))
            in_drawer_ = false;
        else {
            /*
             * We expect there to be an open drawer, so find it and
             * push out contents into it.
             */
            const auto dc(parser::parse_drawer_content(s));
            auto& drawers(top().data().drawers());
            if (drawers.empty()) {
                BOOST_LOG_SEV(lg, error) << empty_drawers;
                BOOST_THROW_EXCEPTION(building_error(empty_drawers));
            }

            drawers.back().contents().push_back(dc);
        }
        return;
    }

    /*
     * Finally, if nothing else matches, it must be a text block.
     */
    if (is_first_line_) {
        BOOST_LOG_SEV(lg, debug) << "Add first line to text block.";
        stream_ << s;
        is_first_line_ = false;
    } else {
        BOOST_LOG_SEV(lg, debug) << "Add line to text to block.";
        stream_ << std::endl << s;
    }
}

void builder::add_final_new_line() {
    BOOST_LOG_SEV(lg, debug) << "Adding final new line.";
    stream_ << std::endl;
}

entities::document builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Building document.";

    /*
     * We don't expect documents to contain "half" of a drawer.
     */
    if (in_drawer_) {
        BOOST_LOG_SEV(lg, error) << invalid_drawer;
        BOOST_THROW_EXCEPTION(building_error(invalid_drawer));
    }

    /*
     * Flush any pending content we may have.
     */
    end_text_block();

    /*
     * Create the document from the root node.
     */
    entities::document r;
    const auto& c(root_->data());
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

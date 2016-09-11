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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quit.cpp.fabric.forward_declarations_factory"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class generator final {
private:
    boost::shared_ptr<forward_declarations> create(const yarn::name& n) const {
        auto r(boost::make_shared<forward_declarations>());
        r->name(n);
        r->generation_type(yarn::generation_types::full_generation);
        r->is_element_extension(true);
        return r;
    }

public:
    std::list<boost::shared_ptr<yarn::element>> result() { return result_; }

public:
    void operator()(const yarn::concept&) {}
    void operator()(const yarn::primitive&) {}
    void operator()(const yarn::module&) {}

    void operator()(const dogen::yarn::visitor& v) {
        if (v.generation_type() == yarn::generation_types::no_generation)
            return;

        result_.push_back(create(v.name()));
    }

    void operator()(const yarn::enumeration& e) {
        if (e.generation_type() == yarn::generation_types::no_generation)
            return;
        const auto fd(create(e.name()));
        fd->is_enum(true);
        fd->underlying_type(e.underlying_type());
        result_.push_back(fd);
    }

    void operator()(const yarn::object& o) {
        if (o.generation_type() == yarn::generation_types::no_generation)
            return;

        result_.push_back(create(o.name()));
    }

    void operator()(const yarn::exception& e) {
        if (e.generation_type() == yarn::generation_types::no_generation)
            return;

        const auto fd(create(e.name()));
        fd->is_exception(true);
        result_.push_back(fd);
    }

private:
    std::list<boost::shared_ptr<yarn::element>> result_;
};

std::list<boost::shared_ptr<yarn::element>> forward_declarations_factory::
build(const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating forward declarations.";

    generator g;
    yarn::elements_traversal(im, g);
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Generated forward declarations: " << r.size();
    return r;
}

} } } }

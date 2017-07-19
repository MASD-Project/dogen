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
#include "dogen/yarn/types/meta_model/elements_traversal.hpp"
#include "dogen/quilt.cpp/types/fabric/meta_name_factory.hpp"
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
    template<typename Element>
    boost::shared_ptr<forward_declarations> create(const Element& e) const {
        auto r(boost::make_shared<forward_declarations>());
        r->name(e.name());
        r->meta_name(meta_name_factory::make_name("forward_declarations"));
        r->origin_type(e.origin_type());
        r->annotation(e.annotation());
        r->is_element_extension(true);
        return r;
    }

public:
    std::list<boost::shared_ptr<yarn::meta_model::element>>
    result() { return result_; }

public:
    void operator()(yarn::meta_model::element&) { }
    void operator()(const yarn::meta_model::concept&) {}
    void operator()(const yarn::meta_model::builtin&) {}
    void operator()(const yarn::meta_model::module&) {}

    void operator()(const dogen::yarn::meta_model::visitor& v) {
        result_.push_back(create(v));
    }

    void operator()(const yarn::meta_model::enumeration& e) {
        const auto fd(create(e));
        fd->is_enum(true);
        fd->underlying_element(e.underlying_element());
        result_.push_back(fd);
    }

    void operator()(const yarn::meta_model::primitive& p) {
        result_.push_back(create(p));
    }

    void operator()(const yarn::meta_model::object& o) {
        result_.push_back(create(o));
    }

    void operator()(const yarn::meta_model::exception& e) {
        const auto fd(create(e));
        fd->is_exception(true);
        result_.push_back(fd);
    }

private:
    std::list<boost::shared_ptr<yarn::meta_model::element>> result_;
};

std::list<boost::shared_ptr<yarn::meta_model::element>>
forward_declarations_factory::
make(const yarn::meta_model::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating forward declarations.";

    generator g;
    yarn::meta_model::elements_traversal(im, g);
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Generated forward declarations: " << r.size();
    return r;
}

} } } }

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
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/quilt.cpp/types/annotations/building_error.hpp"
#include "dogen/quilt.cpp/io/annotations/aspect_annotations_repository_io.hpp"
#include "dogen/quilt.cpp/types/annotations/aspect_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/annotations/aspect_annotations_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.annotations.aspect_annotations_repository_factory"));

const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

namespace {

/**
 * @brief Generates the aspect_annotations.
 */
class generator final : public yarn::element_visitor {
public:
    explicit generator(const aspect_annotations_factory& f)
        : factory_(f) {}

private:
    void insert(const yarn::name& n, const annotations::aspect_annotations& as) {
        const auto pair(std::make_pair(n.id(), as));
        const auto res(result_.by_id().insert(pair));
        if (!res.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_name << n.id();
            BOOST_THROW_EXCEPTION(building_error(duplicate_name + n.id()));
        }
    }

private:
    void generate(const yarn::element& e) {
        const auto as(factory_.make(e.extensions()));
        if (as)
            insert(e.name(), *as);
    }

public:
    using yarn::element_visitor::visit;
    void visit(const dogen::yarn::module& m) override { generate(m); }
    void visit(const dogen::yarn::concept& c) override { generate(c); }
    void visit(const dogen::yarn::primitive& p) override { generate(p); }
    void visit(const dogen::yarn::enumeration& e) override { generate(e); }
    void visit(const dogen::yarn::object& o) override { generate(o); }
    void visit(const dogen::yarn::exception& e) override { generate(e); }
    void visit(const dogen::yarn::visitor& v) override { generate(v); }

public:
    const aspect_annotations_repository& result() const { return result_; }

private:
    const aspect_annotations_factory& factory_;
    aspect_annotations_repository result_;
};

}

aspect_annotations_repository aspect_annotations_repository_factory::
make(const dynamic::repository& rp, const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Creating aspect annotations repository.";

    const aspect_annotations_factory f(rp);
    generator g(f);
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(g);
    }
    auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Finished creating aspect annotations repository."
                             << r;
    return r;
}

} } } }

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
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/annotations/building_error.hpp"
#include "dogen/quilt.cpp/types/annotations/element_annotations_factory.hpp"
#include "dogen/quilt.cpp/io/annotations/element_annotations_repository_io.hpp"
#include "dogen/quilt.cpp/types/annotations/element_annotations_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.annotations.element_annotations_repository_factory"));

const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

namespace {

/**
 * @brief Generates the element annotations.
 */
class generator final : public fabric::element_visitor {
public:
    generator(const element_annotations_factory& f,
        const opaque_annotations_builder& osb)
        : factory_(f), opaque_annotations_builder_(osb) {}

private:
    void insert(const yarn::name& n, const annotations::element_annotations& b) {
        const auto pair(std::make_pair(n.id(), b));
        const auto res(result_.by_id().insert(pair));
        if (!res.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_name << n.id();
            BOOST_THROW_EXCEPTION(building_error(duplicate_name + n.id()));
        }
    }

private:
    void generate(const yarn::element& e) {
        if (e.generation_type() == yarn::generation_types::no_generation)
            return;

        const auto b(factory_.make(e.extensions()));
        insert(e.name(), b);
    }

    template<typename YarnStatefulNameableExtensible>
    void generate_stateful(const YarnStatefulNameableExtensible& e) {
        if (e.generation_type() == yarn::generation_types::no_generation)
            return;

        auto b(factory_.make(e.extensions()));
        for (const auto& p : e.all_attributes()) {
            const auto os(opaque_annotations_builder_.build(p.extensions()));
            const auto pair(std::make_pair(p.name().id(), os));
            const auto res(b.opaque_annotations_for_property().insert(pair));
            if (!res.second) {
                const auto id(p.name().id());
                BOOST_LOG_SEV(lg, error) << duplicate_name << id;
                BOOST_THROW_EXCEPTION(building_error(duplicate_name + id));
            }
        }
        insert(e.name(), b);
    }

public:
    using fabric::element_visitor::visit;
    void visit(const yarn::module& m) override { generate(m); }
    void visit(const yarn::concept& c) override { generate_stateful(c); }
    void visit(const yarn::primitive& p) override { generate(p); }
    void visit(const yarn::enumeration& e) override { generate(e); }
    void visit(const yarn::object& o) override { generate_stateful(o); }
    void visit(const yarn::exception& e) override { generate(e); }
    void visit(const yarn::visitor& v) override { generate(v); }
    void visit(const fabric::registrar& rg) override { generate(rg); }

public:
    const element_annotations_repository& result() const { return result_; }

private:
    const element_annotations_factory& factory_;
    const opaque_annotations_builder& opaque_annotations_builder_;
    element_annotations_repository result_;
};

}

element_annotations_repository element_annotations_repository_factory::
make(const opaque_annotations_builder& osb, const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Creating element annotations repository.";

    const element_annotations_factory f(osb);
    generator g(f, osb);
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(g);
    }
    auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Finished creating element annotations repository."
                             << r;
    return r;
}

} } } }

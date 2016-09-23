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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_factory.hpp"
#include "dogen/quilt.cpp/io/formattables/inclusion_dependencies_repository_io.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.inclusion_dependencies_repository_factory"));

const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates all inclusion dependencies.
 */
class generator final : public fabric::element_visitor {
public:
    explicit generator(const inclusion_dependencies_factory& f) : factory_(f) {}

private:
    template<typename YarnEntity>
    void generate(const YarnEntity& e, const yarn::name& n) {
        const auto id(factory_.make(e));

        // note: optional return may have be cleaner here, but however it
        // would complicate the logic in the factory.
        if (id.empty())
            return;

        auto& deps(result_.by_name());
        const auto i(deps.find(n));
        if (i != deps.end()) {
            BOOST_LOG_SEV(lg, debug) << "Original dependencies: " << i->second;
            BOOST_LOG_SEV(lg, debug) << "Id: " << id;

            // FIXME: biggest hack ever to handle forward declarations;
            // these have the same name as the main object and so we need
            // to merge them together. The formatter id's are
            // different so there are no clashes.
            for (const auto& d : id) {
                i->second[d.first] = d.second;
            }
        } else {
            const auto pair(std::make_pair(n, id));

            const auto res(deps.insert(pair));
            if (!res.second) {
                BOOST_LOG_SEV(lg, error) << duplicate_name << n.id();
                BOOST_THROW_EXCEPTION(building_error(duplicate_name + n.id()));
            }
        }
    }

private:
    /**
     * @brief Generates all of the inclusion dependencies for the
     * formatters and qualified name.
     */
    template<typename YarnEntity>
    void generate(const YarnEntity& e) {
        if (e.generation_type() == yarn::generation_types::no_generation)
            return;

        generate(e, e.name());
    }

public:
    using fabric::element_visitor::visit;
    void visit(const yarn::module& m) override { generate(m); }
    void visit(const yarn::concept& c) override { generate(c); }
    void visit(const yarn::primitive& p) override { generate(p); }
    void visit(const yarn::enumeration& e) override { generate(e); }
    void visit(const yarn::object& o) override { generate(o); }
    void visit(const yarn::exception& e) override { generate(e); }
    void visit(const yarn::visitor& v) override { generate(v); }
    void visit(const fabric::master_header& mh) override { generate(mh); }
    void visit(const fabric::registrar& rg) override { generate(rg); }
    void visit(const fabric::forward_declarations& fd) override {
        generate(fd);
    }

public:
    const inclusion_dependencies_repository& result() const { return result_; }

private:
    const inclusion_dependencies_factory& factory_;
    inclusion_dependencies_repository result_;
};

}

inclusion_dependencies_repository inclusion_dependencies_repository_factory::
make(const inclusion_dependencies_builder_factory& bf,
    const formatters::container& fc, const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating inclusion dependencies.";

    const inclusion_dependencies_factory idf(bf, fc);
    generator g(idf);
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(g);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies:"
                             << g.result();
    return g.result();
}

} } } }

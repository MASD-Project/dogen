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
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/io/formattables/aspect_properties_repository_io.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_properties_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_properties_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.aspect_properties_repository_factory"));

const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

namespace {

class generator final : public yarn::element_visitor {
public:
    explicit generator(const aspect_properties_factory& f) : factory_(f) {}

public:
    using yarn::element_visitor::visit;
    void visit(const yarn::object& o) override;

public:
    const aspect_properties_repository& result() const { return result_; }

private:
    const aspect_properties_factory& factory_;
    aspect_properties_repository result_;
};

void generator::visit(const dogen::yarn::object& o) {
    if (o.generation_type() == yarn::generation_types::no_generation)
        return;

    const auto id(o.name().id());
    BOOST_LOG_SEV(lg, debug) << "Creating aspect properties for: " << id;
    const auto ap(factory_.make(o.local_attributes()));

    const auto pair(std::make_pair(id, ap));
    auto& bid(result_.by_id());
    if (!bid.insert(pair).second) {
        BOOST_LOG_SEV(lg, error) << duplicate_name << id;
        BOOST_THROW_EXCEPTION(building_error(duplicate_name + id));
    }
    BOOST_LOG_SEV(lg, debug) << "Done creating aspect properties for: " << id;
}

}

aspect_properties_repository aspect_properties_repository_factory::make(
    const annotations::aspect_annotations_repository& asrp,
    const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating aspect properties"
                             << " repository.";

    const aspect_properties_factory f(asrp);
    generator g(f);
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(g);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating aspect properties"
                             << " repository: " << g.result();
    return g.result();
}

} } } }

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
#include <list>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/io/properties/helper_properties_repository_io.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_factory.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.properties.helper_properties_repository_factory"));

const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

namespace {

class generator final : public yarn::element_visitor {
public:
    explicit generator(const helper_properties_factory& f) : factory_(f) {}

private:
    template<typename YarnStateful>
    void generate(const YarnStateful& s) {
        if (s.generation_type() == yarn::generation_types::no_generation)
            return;

        const auto qn(s.name().id());
        BOOST_LOG_SEV(lg, debug) << "Creating helper instances for" << qn;


        const auto hi(factory_.make(s.local_attributes()));
        const auto pair(std::make_pair(qn, hi));
        auto& hibn(result_.by_id());
        const auto res(hibn.insert(pair));
        if (!res.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_name << qn;
            BOOST_THROW_EXCEPTION(building_error(duplicate_name + qn));
        }
        BOOST_LOG_SEV(lg, debug) << "Done creating helper instances for" << qn;
    }

public:
    using yarn::element_visitor::visit;
    void visit(const dogen::yarn::concept& c) { generate(c); }
    void visit(const dogen::yarn::object& o) { generate(o); }

public:
    const helper_properties_repository& result() const { return result_; }

private:
    const helper_properties_factory& factory_;
    helper_properties_repository result_;
};

}

helper_properties_repository
helper_properties_repository_factory::make(const yarn::model& m,
    const settings::helper_settings_repository& hsrp) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating helper instances.";

    const helper_properties_factory f(hsrp);
    generator g(f);
    for (const auto& pair : m.elements()) {
        const auto& e(*pair.second);
        e.accept(g);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating helper instances:"
                             << g.result();
    return g.result();
}

} } } }

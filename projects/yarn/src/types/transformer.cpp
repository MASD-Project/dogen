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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/transformation_error.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transformer"));

const std::string duplicate_qualified_name("Duplicate qualified name: ");
const std::string missing_root_module("Root module not found: ");

}

namespace dogen {
namespace yarn {

namespace {

class generator {
public:
    explicit generator(model& m) : result_(m) { }

private:
    template<typename Element>
    void generate(const Element& e) {
        const auto qn(e.name().id());
        const auto ptr(boost::make_shared<Element>(e));
        const auto r(result_.elements().insert(std::make_pair(qn, ptr)));
        if (!r.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << qn;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_qualified_name + qn));
        }
    }

public:
    void operator()(const dogen::yarn::module& m) { generate(m); }
    void operator()(const dogen::yarn::concept& c) { generate(c); }
    void operator()(const dogen::yarn::primitive& p) { generate(p); }
    void operator()(const dogen::yarn::enumeration& e) { generate(e); }
    void operator()(const dogen::yarn::object& o) { generate(o); }
    void operator()(const dogen::yarn::exception& e) { generate(e); }
    void operator()(const dogen::yarn::visitor& v) { generate(v); }

public:
    const model& result() const { return result_; }

private:
    model& result_;
};

}

model transformer::transform(const intermediate_model& m) const {
    const auto i(m.modules().find(m.name().id()));
    if (i == m.modules().end()) {
        const auto qn(m.name().id());
        BOOST_LOG_SEV(lg, error) << missing_root_module << qn;
        BOOST_THROW_EXCEPTION(transformation_error(missing_root_module + qn));
    }

    model r;
    r.name(m.name());
    r.root_module(i->second);
    r.leaves(m.leaves());
    r.references(m.references());
    r.has_generatable_types(m.has_generatable_types());

    generator g(r);
    yarn::elements_traversal(m, g);

    return r;
}

} }

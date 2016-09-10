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
    void add(boost::shared_ptr<element> e) {
        const auto id(e->name().id());
        const auto r(result_.elements().insert(std::make_pair(id, e)));
        if (!r.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_qualified_name + id));
        }
    }

    template<typename Element>
    void generate(const Element& e) { add(boost::make_shared<Element>(e)); }

public:
    void operator()(const yarn::module& m) { generate(m); }
    void operator()(const yarn::concept& c) { generate(c); }
    void operator()(const yarn::primitive& p) { generate(p); }
    void operator()(const yarn::enumeration& e) { generate(e); }
    void operator()(const yarn::object& o) { generate(o); }
    void operator()(const yarn::exception& e) { generate(e); }
    void operator()(const yarn::visitor& v) { generate(v); }

public:
    void add_injected_elements(
        const std::unordered_map<std::string, boost::shared_ptr<element>>& ie) {
        for (const auto& pair : ie)
            add(pair.second);
    }

public:
    const model& result() const { return result_; }

private:
    model& result_;
};

}

model transformer::transform(const intermediate_model& im) const {
    const auto i(im.modules().find(im.name().id()));
    if (i == im.modules().end()) {
        const auto id(im.name().id());
        BOOST_LOG_SEV(lg, error) << missing_root_module << id;
        BOOST_THROW_EXCEPTION(transformation_error(missing_root_module + id));
    }

    model r;
    r.name(im.name());
    r.root_module(i->second);
    r.has_generatable_types(im.has_generatable_types());

    generator g(r);
    yarn::elements_traversal(im, g);
    g.add_injected_elements(im.injected_elements());

    return r;
}

} }

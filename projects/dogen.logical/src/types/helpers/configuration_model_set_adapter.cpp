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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/io/entities/configuration_model_set_io.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/helpers/adaptation_exception.hpp"
#include "dogen.logical/types/helpers/configuration_model_set_adapter.hpp"

namespace {

const std::string transform_id("logical.helpers.configuration_model_set_adapter");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_qualified_name(
    "Duplicate qualified name for configuration: ");

}
namespace dogen::logical::helpers {

namespace {

/**
 * @brief Extracts variability data from logical model types, and
 * inserts it into a configuration model.
 */
class populator {
private:
    template<typename Configurable>
    void extract(Configurable& c) {
        const auto& n(c.configuration()->name());
        const auto& qn(n.qualified());
        BOOST_LOG_SEV(lg, trace) << "Extracting: " << n.simple()
                                 << " (" << qn << ") ";

        auto pair(std::make_pair(qn, c.configuration()));
        const auto inserted(model_.local().insert(pair).second);
        if (inserted)
            return;

        BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << qn;
        BOOST_THROW_EXCEPTION(
            adaptation_exception(duplicate_qualified_name + qn));
    }

public:
    void operator()(entities::element& e) { extract(e); }
    void operator()(entities::structural::module& m) {
        if (m.is_root())
            model_.global(m.configuration());
        else
            extract(m);
    }
    void operator()(entities::structural::object_template& ot) {
        extract(ot);
        for (auto& attr : ot.local_attributes())
            extract(attr);
    }
    void operator()(entities::structural::enumeration& e) {
        extract(e);
        for (auto& enm : e.enumerators())
            extract(enm);
    }
    void operator()(entities::structural::object& o) {
        extract(o);
        for (auto& attr : o.local_attributes())
            extract(attr);
    }

public:
    variability::entities::configuration_model& result() {
        return model_;
    }

private:
    variability::entities::configuration_model model_;
};

}

variability::entities::configuration_model
configuration_model_set_adapter::adapt(const entities::model& m) {
    populator e;
    entities::elements_traversal(m, e);
    return e.result();
}

variability::entities::configuration_model_set
configuration_model_set_adapter::adapt(const entities::model_set& ms) {
    variability::entities::configuration_model_set r;
    r.models().push_back(adapt(ms.target()));

    for (const auto& m : ms.references())
        r.models().push_back(adapt(m));

    return r;
}

}

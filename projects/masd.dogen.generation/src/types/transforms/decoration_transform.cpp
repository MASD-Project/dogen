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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_group.hpp"
#include "masd.dogen.coding/types/meta_model/technical_space.hpp"
#include "masd.dogen.coding/types/meta_model/element_visitor.hpp"
#include "masd.dogen.coding/io/meta_model/technical_space_io.hpp"
#include "masd.dogen.generation/io/meta_model/model_io.hpp"
#include "masd.dogen.generation/types/transforms/transformation_error.hpp"
#include "masd.dogen.generation/types/transforms/decoration_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.technical_space_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_technical_space(
    "More than one modeline defined for technical space: ");
const std::string duplicate_modeline_group(
    "Modeline group defined more than once: ");

}

namespace masd::dogen::generation::transforms {

/**
 * @brief Organises all modelines by modeline group and by
 * technical space.
 */
class modelines_aggregator : public coding::meta_model::element_visitor {
public:
    using coding::meta_model::element_visitor::visit;
    void visit(const coding::meta_model::modeline_group& mg);

public:
    const std::unordered_map<std::string,
                       std::unordered_map<coding::meta_model::technical_space,
                                          boost::shared_ptr<
                                              coding::meta_model::modeline>
                                          >
                       >&
    result() const {
        return modelines_by_modeline_group_by_technical_space_;
    }

private:
    std::unordered_map<std::string,
                       std::unordered_map<coding::meta_model::technical_space,
                                          boost::shared_ptr<
                                              coding::meta_model::modeline>
                                          >
                       >
    modelines_by_modeline_group_by_technical_space_;
};

void modelines_aggregator::visit(const coding::meta_model::modeline_group& mg) {
    std::unordered_map<coding::meta_model::technical_space,
                       boost::shared_ptr<coding::meta_model::modeline>> map;

    for (const auto& ml : mg.modelines()) {
        const auto ts(ml->technical_space());
        const auto id(ml->name().qualified().dot());
        const auto pair(std::make_pair(ts, ml));
        const bool inserted(map.insert(pair).second);
        if (!inserted) {
            const auto ts_str(boost::lexical_cast<std::string>(ts));
            BOOST_LOG_SEV(lg, error) << duplicate_technical_space << ts_str
                                     << " For modeline: " << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_technical_space + ts_str));
        }
    }

    const auto gid(mg.name().qualified().dot());
    const auto pair(std::make_pair(gid, map));
    const bool inserted(
        modelines_by_modeline_group_by_technical_space_.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_modeline_group << gid;
        BOOST_THROW_EXCEPTION(
            transformation_error(duplicate_modeline_group + gid));
    }
}

std::unordered_map<
    std::string,
    std::unordered_map<coding::meta_model::technical_space,
                       boost::shared_ptr<
                           coding::meta_model::modeline>
                       >
    >
decoration_transform::aggregate_modelines(meta_model::model& m) {
    modelines_aggregator ag;
    for (const auto& e : m.elements())
        e->accept(ag);
    return ag.result();
}

void decoration_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "decoration transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    aggregate_modelines(m);
    stp.end_transform(m);
}

}

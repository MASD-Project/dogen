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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/modeline.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_group.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/modelines_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.modelines_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string editor_emacs("emacs");
const std::string editor_vi("vi");
const std::string editor_vim("vim");
const std::string editor_ex("ex");

const std::string modeline_location_top("top");
const std::string modeline_location_bottom("bottom");

const std::string technical_space_cpp("cpp");
const std::string technical_space_csharp("csharp");
const std::string technical_space_cmake("cmake");
const std::string technical_space_xml("xml");
const std::string technical_space_odb("odb");
const std::string technical_space_sln("sln");

const std::string missing_container("Modeline does not have a container: ");
const std::string missing_group("Cannot find modeline group: ");
const std::string invalid_editor("Editor is invalid or unsupported: ");
const std::string invalid_modeline_location(
    "Modeline location is invalid or unsupported: ");
const std::string invalid_technical_space(
    "Technical space is invalid or unsupported: ");

}

namespace masd::dogen::coding::transforms {

meta_model::editor modelines_transform::to_editor(const std::string& s) {
    using meta_model::editor;
    if (s == editor_emacs)
        return editor::emacs;
    else if (s == editor_vi)
        return editor::vi;
    else if (s == editor_vim)
        return editor::vim;
    else if (s == editor_ex)
        return editor::ex;

    BOOST_LOG_SEV(lg, error) << invalid_editor << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_editor + s));
}

meta_model::modeline_location modelines_transform::
to_modeline_location(const std::string& s) {
    using meta_model::modeline_location;
    if (s == modeline_location_top)
        return modeline_location::top;
    else if (s == modeline_location_bottom)
        return modeline_location::bottom;

    BOOST_LOG_SEV(lg, error) << invalid_modeline_location << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_modeline_location + s));
}

meta_model::technical_space
modelines_transform::to_technical_space(const std::string& s) {
    using meta_model::technical_space;
    if (s == technical_space_cpp)
        return technical_space::cpp;
    else if (s == technical_space_csharp)
        return technical_space::csharp;
    else if (s == technical_space_cmake)
        return technical_space::cmake;
    else if (s == technical_space_xml)
        return technical_space::xml;
    else if (s == technical_space_odb)
        return technical_space::odb;
    else if (s == technical_space_sln)
        return technical_space::sln;

    BOOST_LOG_SEV(lg, error) << invalid_technical_space << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_technical_space + s));
}

modelines_transform::type_group
modelines_transform::make_type_group(const variability::type_repository& atrp) {
    type_group r;
    const variability::type_repository_selector s(atrp);

    using ml = traits::decoration::modeline;
    r.editor = s.select_type_by_name(ml::editor());
    r.modeline_location = s.select_type_by_name(ml::location());
    r.technical_space = s.select_type_by_name(ml::technical_space());
    return r;
}

meta_model::editor modelines_transform::
make_editor(const type_group& tg, const variability::annotation& a) {
    const variability::entry_selector s(a);
    const auto str(s.get_text_content(tg.editor));
    return to_editor(str);
}

meta_model::modeline_location modelines_transform::make_modeline_location(
    const type_group& tg, const variability::annotation& a) {
    const variability::entry_selector s(a);
    const auto str(s.get_text_content(tg.modeline_location));
    return to_modeline_location((str));
}

meta_model::technical_space modelines_transform::
make_technical_space(const type_group& tg, const variability::annotation& a) {
    const variability::entry_selector s(a);
    const auto str(s.get_text_content(tg.technical_space));
    return to_technical_space(str);
}

void modelines_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "modelines transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto tg(make_type_group(*ctx.type_repository()));
    for(auto& pair : m.modelines()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, trace) << "Processing modeline: " << id;

        auto& ml(*pair.second);
        const auto a(ml.annotation());

        ml.editor(make_editor(tg, a));
        ml.location(make_modeline_location(tg, a));
        ml.technical_space(make_technical_space(tg, a));

        if (ml.contained_by().empty()) {
            BOOST_LOG_SEV(lg, error) << missing_container << id;
            BOOST_THROW_EXCEPTION(transformation_error(missing_container + id));
        }

        auto& mgs(m.modeline_groups());
        const auto i(mgs.find(ml.contained_by()));
        if (i == mgs.end()) {
            BOOST_LOG_SEV(lg, error) << missing_group << ml.contained_by();
            BOOST_THROW_EXCEPTION(
                transformation_error(missing_group + ml.contained_by()));
        }
        i->second->modelines().push_back(pair.second);
    }

    stp.end_transform(m);
}

}

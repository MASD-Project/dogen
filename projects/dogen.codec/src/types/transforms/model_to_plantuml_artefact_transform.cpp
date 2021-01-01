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
#include <boost/algorithm/string/replace.hpp>
#include <sstream>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/io/entities/artefact_io.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/transforms/model_to_plantuml_artefact_transform.hpp"

namespace {

const std::string
transform_id("codec.transforms.model_to_plantuml_artefact_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string default_element_colour("#F7E5FF");
const std::string default_module_colour("#F2F2F2");
const std::string parent_tag("masd.codec.parent");
const std::string stereotypes_tag("masd.codec.stereotypes");
const std::string type_tag("masd.codec.type");
const std::string masd_assistant("masd::assistant");
const std::string masd_build_cmakelists("masd::build::cmakelists");
const std::string masd_decoration_generation_marker(
    "masd::decoration::generation_marker");
const std::string masd_decoration_licence("masd::decoration::licence");
const std::string masd_decoration_licence_text("masd::decoration::licence_text");
const std::string masd_decoration_modeline("masd::decoration::modeline");
const std::string masd_decoration_modeline_group(
    "masd::decoration::modeline_group");
const std::string masd_entry_point("masd::entry_point");
const std::string masd_enumeration("masd::enumeration");
const std::string masd_exception("masd::exception");
const std::string masd_module("masd::module");
const std::string masd_mapping_extensible_mappable(
    "masd::mapping::extensible_mappable");
const std::string masd_mapping_fixed_mappable("masd::mapping::fixed_mappable");
const std::string masd_object("masd::object");
const std::string masd_object_template("masd::object_template");
const std::string masd_orm_common_odb_options("masd::orm::common_odb_options");
const std::string masd_orm_object("masd::orm::object");
const std::string masd_orm_value("masd::orm::value");
const std::string masd_physical_helper("masd::physical::helper");
const std::string masd_physical_archetype("masd::physical::archetype");
const std::string masd_physical_archetype_kind("masd::physical::archetype_kind");
const std::string masd_physical_backend("masd::physical::backend");
const std::string masd_physical_facet("masd::physical::facet");
const std::string masd_physical_part("masd::physical::part");
const std::string masd_primitive("masd::primitive");
const std::string masd_serialization_type_registrar(
    "masd::serialization::type_registrar");
const std::string masd_templating_logic_less_templates(
    "masd::templating::logic_less_templates");
const std::string masd_variability_feature_bundle(
    "masd::variability::feature_bundle");
const std::string masd_variability_feature_template_bundle(
    "masd::variability::feature_template_bundle");
const std::string masd_variability_initializer(
    "masd::variability::initializer");
const std::string masd_variability_profile("masd::variability::profile");
const std::string masd_variability_profile_template(
    "masd::variability::profile_template");
const std::string masd_visual_studio_msbuild_targets(
    "masd::visual_studio::msbuild_targets");
const std::string masd_visual_studio_project("masd::visual_studio::project");
const std::string masd_visual_studio_solution("masd::visual_studio::solution");
const std::string dogen_handcrafted_typeable("dogen::handcrafted::typeable");
const std::string dogen_handcrafted_typeable_header_only(
    "dogen::handcrafted::typeable::header_only");
const std::string dogen_handcrafted_typeable_implementation_only (
    "dogen::handcrafted::typeable::implementation_only");
const std::string dogen_untestable("dogen::untestable");

const std::string empty_id("Element has an empty ID: ");

}

namespace dogen::codec::transforms {

model_to_plantuml_artefact_transform::properties
model_to_plantuml_artefact_transform::extract_properties(
    const std::list<identification::entities::tagged_value>& tvs) {
    properties r;
    for (const auto& tv : tvs) {
        if (tv.tag() == parent_tag)
            r.parents = tv.value();
        else if (tv.tag() == stereotypes_tag)
            r.stereotypes = tv.value();
        else if (tv.tag() == type_tag)
            r.type = tv.value();
    }

    return r;
}

std::string model_to_plantuml_artefact_transform::
stereotype_to_colour(const std::string& stereotypes, const bool is_module) {
    std::string r;

    if (boost::contains(stereotypes, masd_assistant))
        return std::string("#D89EF1");
    else if (boost::contains(stereotypes, masd_build_cmakelists))
        return std::string("#99CB99");
    else if (boost::contains(stereotypes, masd_decoration_generation_marker))
        return std::string("#E8D0C5");
    else if (boost::contains(stereotypes, masd_decoration_licence))
        return std::string("#F9F0EB");
    else if (boost::contains(stereotypes, masd_decoration_licence_text))
        return std::string("#F9F0EB");
    else if (boost::contains(stereotypes, masd_decoration_modeline))
        return std::string("#D6B19F");
    else if (boost::contains(stereotypes, masd_decoration_modeline_group))
        return std::string("#CECECE");
    else if (boost::contains(stereotypes, masd_entry_point))
        return std::string("#DDA9F3");
    else if (boost::contains(stereotypes, masd_enumeration))
        return std::string("#F2DAFD");
    else if (boost::contains(stereotypes, masd_exception))
        return std::string("#E8C2F8");
    else if (boost::contains(stereotypes, masd_mapping_extensible_mappable))
        return std::string("#FFFF72");
    else if (boost::contains(stereotypes, masd_mapping_fixed_mappable))
        return std::string("#FFFFAC");
    else if (boost::contains(stereotypes, masd_object_template))
        return std::string("#E3B6F6");
    else if (boost::contains(stereotypes, masd_object))
        return std::string("#F7E5FF");
    else if (boost::contains(stereotypes, masd_orm_common_odb_options))
        return std::string("#80FFBF");
    else if (boost::contains(stereotypes, masd_orm_object))
        return std::string("#CCFFE6");
    else if (boost::contains(stereotypes, masd_orm_value))
        return std::string("#B3FFD9");
    else if (boost::contains(stereotypes, masd_physical_helper))
        return std::string("#68D7BB");
    else if (boost::contains(stereotypes, masd_physical_archetype))
        return std::string("#68D799");
    else if (boost::contains(stereotypes, masd_physical_archetype_kind))
        return std::string("#A0E6BF");
    else if (boost::contains(stereotypes, masd_physical_backend))
        return std::string("#EBFAF1");
    else if (boost::contains(stereotypes, masd_physical_facet))
        return std::string("#C6F0D8");
    else if (boost::contains(stereotypes, masd_physical_part))
        return std::string("#43CD80");
    else if (boost::contains(stereotypes, masd_primitive))
        return std::string("#EDCEFB");
    else if (boost::contains(stereotypes, masd_serialization_type_registrar))
        return std::string("#00FF00");
    else if (boost::contains(stereotypes, masd_templating_logic_less_templates))
        return std::string("#FFC072");
    else if (boost::contains(stereotypes, masd_variability_feature_bundle))
        return std::string("#BAD7D7");
    else if (boost::contains(stereotypes,
            masd_variability_feature_template_bundle))
        return std::string("#CCE2E2");
    else if (boost::contains(stereotypes, masd_variability_initializer))
        return std::string("#A9CDCD");
    else if (boost::contains(stereotypes, masd_variability_profile))
        return std::string("#DDECEC");
    else if (boost::contains(stereotypes, masd_variability_profile_template))
        return std::string("#EEF6F6");
    else if (boost::contains(stereotypes, masd_visual_studio_msbuild_targets))
        return std::string("#B3DDB3");
    else if (boost::contains(stereotypes, masd_visual_studio_project))
        return std::string("#CCEECC");
    else if (boost::contains(stereotypes, masd_visual_studio_solution))
        return std::string("#E5FFE5");
    else if (boost::contains(stereotypes, dogen_handcrafted_typeable))
        return std::string("#FFFACD");
    else if (boost::contains(stereotypes,
            dogen_handcrafted_typeable_header_only))
        return std::string("#FFFADD");
    else if (boost::contains(stereotypes,
            dogen_handcrafted_typeable_implementation_only))
        return std::string("#FFFADE");
    else if (boost::contains(stereotypes, dogen_untestable))
        return std::string("#ED8181");

    /*
     * If we did not match any stereotype, use the default colours for
     * modules and elements.
     */
    return is_module ? default_module_colour : default_element_colour;
}

void model_to_plantuml_artefact_transform::walk_parent_to_child(
    std::ostream& os, const unsigned int level,
    const std::string& id, const std::unordered_map<std::string,
    std::list<entities::element>>& parent_to_child_map) {
    BOOST_LOG_SEV(lg, debug) << "Processing ID: '" << id << "'";

    const auto i(parent_to_child_map.find(id));
    if (i != parent_to_child_map.end()) {
        /*
         * Loop through all the elements at this level and recurse to
         * their children.
         */
        BOOST_LOG_SEV(lg, debug) << "Found ID in map.";
        const auto lambda([](const unsigned int level) {
            if (level == 0)
                return empty;
            return std::string(level * 8, ' ');
        });
        const auto indent(lambda(level));
        const std::string inner_indent(lambda(level + 1));
        for (const auto& e : i->second) {
            BOOST_LOG_SEV(lg, debug) << "Processing element: "
                                     << e.name().qualified();

            const auto props(extract_properties(e.tagged_values()));
            const auto sts(props.stereotypes);
            if (boost::contains(sts, masd_enumeration))
                os << indent << "enum ";
            else if (e.fallback_element_type() == masd_module)
                os << indent << "namespace ";
            else
                os << indent << "class ";
            os << e.name().simple();

            if (!sts.empty())
                os << " <<" << sts << ">>";

            const bool is_module(e.fallback_element_type() == masd_module);
            const auto colour(stereotype_to_colour(sts, is_module));
            os << " " << colour;

            os << " {" << std::endl;
            for (const auto& attr : e.attributes()) {
                os << inner_indent << "+{field} " << attr.name().simple();

                const auto props(extract_properties(attr.tagged_values()));
                if (!props.type.empty())
                    os << " " << props.type;

                os << std::endl;
            }

            const auto& map(parent_to_child_map);
            const auto inner_id(e.provenance().codec_id().value());
            if (inner_id.empty()) {
                BOOST_LOG_SEV(lg, error) << empty_id << e.name().qualified();
                BOOST_THROW_EXCEPTION(
                    transformation_error(empty_id + e.name().qualified()));
            }
            walk_parent_to_child(os, level + 1, inner_id, map);

            os << indent << "}" << std::endl << std::endl;

            if (!props.parents.empty()) {
                using utility::string::splitter;
                const auto parents(splitter::split_csv(props.parents));
                for (const auto& parent : parents) {
                    os << parent << " <|-- "
                       << e.name().qualified()
                       << std::endl;
                }
            }

            if (!e.comment().documentation().empty()) {
                os << "note top of  " << e.name().simple() << std::endl
                   << e.comment().documentation() << std::endl
                   << "end note" << std::endl << std::endl;
            }

        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished processing ID.";
}

entities::artefact model_to_plantuml_artefact_transform::
apply(const transforms::context& ctx, const boost::filesystem::path& p,
    const entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "org artefact to model",
        transform_id, m.name().qualified(), *ctx.tracer(), m);

    std::ostringstream os;
    os << "@startuml" << std::endl
       << "set namespaceSeparator ::" << std::endl;

    if (!m.comment().documentation().empty()) {
        os << "note as N1" << std::endl
           << m.comment().documentation() << std::endl
           << "end note" << std::endl << std::endl;
    }

    /*
     * Construct a map with the ID of the parent pointing to a list of
     * its children.
     */
    std::unordered_map<std::string,
                       std::list<entities::element>> parent_to_child_map;
    for (const auto& e : m.elements()) {
        auto& n(parent_to_child_map[e.containing_element_id().value()]);
        n.push_back(e);
    }

    walk_parent_to_child(os, 0, empty, parent_to_child_map);

    os << "@enduml" << std::endl;

    const auto s(os.str());

    entities::artefact r;
    r.path(p);
    r.content(s);
    r.codec_name("plantuml");

    stp.end_transform(r);
    return r;
}


}

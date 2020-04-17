# -*- mode: python; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#
note_palette =  ['#fcfae8', '#f0e68c']
package_palette =  ['#f2f2f2', '#ececec', '#e7e7e7', '#e0e0e0', '#dbdbdb', '#d4d4d4', '#cecece', '#c8c8c8', '#c2c2c2', '#bcbcbc']
manually_gen_palette =  ['#e5e8ff', '#d6daff', '#c6ccff', '#b6bdff', '#a6afff', '#96a1ff', '#8693ff', '#7684ff', '#6776ff', '#5768ff']
testing_palette =  ['#fee7e7']
orm_palette =  ['#e5fff2', '#ccffe6', '#b3ffd9', '#99ffcc', '#80ffbf', '#66ffb2', '#4dffa5', '#32ff98', '#19ff8c', '#00ff7f']
decoration_palette =  ['#f9f0eb', '#e8d0c5', '#d6b19f', '#c49179', '#b27253', '#a0522d']
variability_palette =  ['#eef6f6', '#ddecec', '#cce2e2', '#bad7d7', '#a9cdcd', '#97c2c2', '#86b8b8', '#74adad', '#63a3a3', '#529999']
mapping_palette =  ['#ffffe5', '#ffffac', '#ffff72', '#ffff39', '#ffff00']
templating_palette =  ['#fff3e5', '#ffc072', '#ff8c00']
serialization_palette =  ['#e5ffe5', '#00ff00']
visual_studio_palette =  ['#e5ffe5', '#cceecc', '#b3ddb3', '#99cb99', '#80ba80', '#66a966', '#4d984d', '#328632', '#197519', '#006400']
core_palette =  ['#f7e5ff', '#f2dafd', '#edcefb', '#e8c2f8', '#e3b6f6', '#dda9f3', '#d89ef1', '#d391ef', '#ce85ed', '#c879ea', '#c36de8', '#be60e5', '#b955e3', '#b348e1', '#ae3cdf', '#a930dc', '#a424da', '#9e17d7', '#990cd5', '#9400d3']
physical_palette =  ['#ebfaf1', '#d8f5e5', '#c6f0d8', '#b3ebcc', '#a0e6bf', '#8de1b2', '#7bdca6', '#68d799', '#55d28c', '#43cd80']

for layer in dia.active_display().diagram.data.layers:
    for object in layer.objects:
        #
        # MASD specific stereorypes.
        # --------------------------
        #

        #
        # Theme: UML elements
        #
        if object.type.name == "UML - Note":
            object.properties["fill_colour"] = note_palette[1]
            continue;

        if object.type.name == "UML - LargePackage":
            stereotype = object.properties["stereotype"].value
            if "masd::decoration::modeline_group" in stereotype:
                object.properties["fill_colour"] = package_palette[6]
            elif "masd::physical::backend" in stereotype:
                object.properties["fill_colour"] = physical_palette[0]
            elif "masd::physical::facet" in stereotype:
                object.properties["fill_colour"] = physical_palette[2]
            else:
                object.properties["fill_colour"] = package_palette[0]
            continue;

        if object.type.name != "UML - Class":
            continue;

        name = object.properties["name"].value
        stereotype = object.properties["stereotype"].value

        #
        # Dogen specific stereorypes.
        # --------------------------
        #

        #
        # Theme: Manually generated
        #
        if "dogen::handcrafted::typeable::header_only" in stereotype:
            object.properties["fill_colour"] = manually_gen_palette[2]
        elif "dogen::handcrafted::typeable::implementation_only" in stereotype:
            object.properties["fill_colour"] = manually_gen_palette[1]
        elif "dogen::handcrafted::typeable" in stereotype:
            object.properties["fill_colour"] = manually_gen_palette[0]

        #
        # Theme: Testing
        #
        elif "dogen::untestable" in stereotype:
            object.properties["fill_colour"] = testing_palette[0]

        #
        # C++ Reference Implementation specific stereorypes.
        # -------------------------------------------------
        #

        #
        # Theme: Manually generated
        #
        elif "cpp_ref_impl::cpp::header_only" in stereotype:
            object.properties["fill_colour"] = manually_gen_palette[2]
        elif "cpp_ref_impl::cpp::implementation_only" in stereotype:
            object.properties["fill_colour"] = manually_gen_palette[1]
        elif "cpp_ref_impl::handcrafted::typeable" in stereotype:
            object.properties["fill_colour"] = manually_gen_palette[0]

        #
        # MASD specific stereorypes.
        # --------------------------
        #

        #
        # Theme: ORM
        #
        elif "masd::orm::object" in stereotype:
            object.properties["fill_colour"] = orm_palette[1]
        elif "masd::orm::value" in stereotype:
            object.properties["fill_colour"] = orm_palette[2]
        elif "masd::orm::common_odb_options" in stereotype:
            object.properties["fill_colour"] = orm_palette[4]

        #
        # Theme: Decorations
        #
        elif "masd::decoration::licence" in stereotype:
            object.properties["fill_colour"] = decoration_palette[0]
        elif "masd::decoration::generation_marker" in stereotype:
            object.properties["fill_colour"] = decoration_palette[1]
        elif "masd::decoration::modeline" in stereotype:
            object.properties["fill_colour"] = decoration_palette[2]

        #
        # Theme: Variability
        #
        elif "masd::variability::profile_template" in stereotype:
            object.properties["fill_colour"] = variability_palette[0]
        elif "masd::variability::profile" in stereotype:
            object.properties["fill_colour"] = variability_palette[1]
        elif "masd::variability::feature_template_bundle" in stereotype:
            object.properties["fill_colour"] = variability_palette[2]
        elif "masd::variability::feature_bundle" in stereotype:
            object.properties["fill_colour"] = variability_palette[3]
        elif "masd::variability::initializer" in stereotype:
            object.properties["fill_colour"] = variability_palette[4]

        #
        # Theme: Mapping
        #
        elif "masd::mapping::fixed_mappable" in stereotype:
            object.properties["fill_colour"] = mapping_palette[1]
        elif "masd::mapping::extensible_mappable" in stereotype:
            object.properties["fill_colour"] = mapping_palette[2]

        #
        # Theme: Templating
        #
        elif "masd::templating::logic_less_templates" in stereotype:
            object.properties["fill_colour"] = templating_palette[1]

        #
        # Theme: Serialization
        #
        elif "masd::serialization::type_registrar" in stereotype:
            object.properties["fill_colour"] = serialization_palette[1]

        #
        # Theme: Visual Studio
        #
        elif "masd::visual_studio::solution" in stereotype:
            object.properties["fill_colour"] = visual_studio_palette[0]
        elif "masd::visual_studio::project" in stereotype:
            object.properties["fill_colour"] = visual_studio_palette[1]
        elif "masd::visual_studio::msbuild_targets" in stereotype:
            object.properties["fill_colour"] = visual_studio_palette[2]

        #
        # Theme: Build
        #
        elif "masd::build::cmakelists" in stereotype:
            object.properties["fill_colour"] = visual_studio_palette[3]

        #
        # Theme: Physical
        #
        elif "masd::physical::archetype" in stereotype:
            object.properties["fill_colour"] = physical_palette[7]
        elif "masd::physical::part" in stereotype:
            object.properties["fill_colour"] = physical_palette[8]


        #
        # Theme: Core meta-elements
        #
        elif "masd::enumeration" in stereotype:
            object.properties["fill_colour"] = core_palette[1]
        elif "masd::primitive" in stereotype:
            object.properties["fill_colour"] = core_palette[2]
        elif "masd::exception" in stereotype:
            object.properties["fill_colour"] = core_palette[3]
        elif "masd::object_template" in stereotype:
            object.properties["fill_colour"] = core_palette[4]
        elif "masd::object" in stereotype:
            object.properties["fill_colour"] = core_palette[1]
        elif "masd::entry_point" in stereotype:
            object.properties["fill_colour"] = core_palette[5]
        elif "masd::assistant" in stereotype:
            object.properties["fill_colour"] = core_palette[6]
        else:
            object.properties["fill_colour"] = core_palette[0]

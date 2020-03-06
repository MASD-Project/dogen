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
            object.properties["fill_colour"] = "#F0E68C"
            continue;

        if object.type.name == "UML - LargePackage":
            stereotype = object.properties["stereotype"].value
            if "masd::decoration::modeline_group" in stereotype:
                object.properties["fill_colour"] = "#FFEFFE"
            else:
                object.properties["fill_colour"] = "#F5F5F5"
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
        if "dogen::handcrafted::typeable" in stereotype:
            object.properties["fill_colour"] = "#FFFACD"
        elif "dogen::handcrafted::typeable::header_only" in stereotype:
            object.properties["fill_colour"] = "#FFFACD"
        elif "dogen::handcrafted::typeable::implementation_only" in stereotype:
            object.properties["fill_colour"] = "#EEFACD"

        #
        # Theme: Testing
        #
        elif "dogen::untestable" in stereotype:
            object.properties["fill_colour"] = "#FBA5A5"

        #
        # C++ Reference Implementation specific stereorypes.
        # -------------------------------------------------
        #

        #
        # Theme: Manually generated
        #
        elif "cpp_ref_impl::handcrafted::typeable" in stereotype:
            object.properties["fill_colour"] = "#FFFACD"
        elif "cpp_ref_impl::cpp::header_only" in stereotype:
            object.properties["fill_colour"] = "#FFFACD"
        elif "cpp_ref_impl::cpp::implementation_only" in stereotype:
            object.properties["fill_colour"] = "#EEFACD"


        #
        # MASD specific stereorypes.
        # --------------------------
        #

        #
        # Theme: ORM
        #
        elif "masd::orm::object" in stereotype:
            object.properties["fill_colour"] = "#98FB98"
        elif "masd::orm::value" in stereotype:
            object.properties["fill_colour"] = "#DDA0DD"
        elif "masd::orm::common_odb_options" in stereotype:
            object.properties["fill_colour"] = "#C278C2"

        #
        # Theme: Decorations
        #
        elif "masd::decoration::modeline" in stereotype:
            object.properties["fill_colour"] = "#DDB7B7"
        elif "masd::decoration::licence" in stereotype:
            object.properties["fill_colour"] = "#DDB7DD"
        elif "masd::decoration::generation_marker" in stereotype:
            object.properties["fill_colour"] = "#ACACBB"

        #
        # Theme: variability
        #
        elif "masd::variability::profile_template" in stereotype:
            object.properties["fill_colour"] = "#EDE6F2"
        elif "masd::variability::feature_template_bundle" in stereotype:
            object.properties["fill_colour"] = "#B2E2E2"
        elif "masd::variability::initializer" in stereotype:
            object.properties["fill_colour"] = "#B2E2E2"

        #
        # Theme: Mapping
        #
        elif "masd::mapping::fixed_mappable" in stereotype:
            object.properties["fill_colour"] = "#DEE463"
        elif "masd::mapping::extensible_mappable" in stereotype:
            object.properties["fill_colour"] = "#F9FF7C"

        #
        # Theme: Templating
        #
        elif "masd::templating::logic_less_templates" in stereotype:
            object.properties["fill_colour"] = "#5EB55E"

        #
        # Theme: Serialization
        #
        elif "masd::serialization::type_registrar" in stereotype:
            object.properties["fill_colour"] = "#00FF00"

        #
        # Theme: Visual Studio
        #
        elif "masd::visual_studio::solution" in stereotype:
            object.properties["fill_colour"] = "#5768FF"
        elif "masd::visual_studio::project" in stereotype:
            object.properties["fill_colour"] = "#909BFF"
        elif "masd::visual_studio::msbuild_targets" in stereotype:
            object.properties["fill_colour"] = "#535A99"

        #
        # Theme: Build
        #
        elif "masd::build::cmakelists" in stereotype:
            object.properties["fill_colour"] = "#C0CE42"

        #
        # Theme: Core meta-elements
        #
        elif "masd::enumeration" in stereotype:
            object.properties["fill_colour"] = "#FFEFD5"
        elif "masd::primitive" in stereotype:
            object.properties["fill_colour"] = "#B0C4DE"
        elif "masd::exception" in stereotype:
            object.properties["fill_colour"] = "#FFDAB9"
        elif "masd::object_template" in stereotype:
            object.properties["fill_colour"] = "#EED2DE"
        elif "masd::object_template" in stereotype:
            object.properties["fill_colour"] = "#EED2DE"
        elif "masd::entry_point" in stereotype:
            object.properties["fill_colour"] = "#A8EAFF"
        elif "masd::assistant" in stereotype:
            object.properties["fill_colour"] = "#A09D9D"
        else:
            object.properties["fill_colour"] = "#F5FFFA"

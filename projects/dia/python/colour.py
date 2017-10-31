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
for object in dia.active_display().diagram.data.layers[0].objects:
    if object.type.name != "UML - Class":
        continue;

    name = object.properties["name"].value
    stereotype = object.properties["stereotype"].value
    if "yarn::enumeration" in stereotype:
        object.properties["fill_colour"] = "Papaya Whip"
    elif "yarn::orm::object" in stereotype:
        object.properties["fill_colour"] = "Pale Green"
    elif "yarn::primitive" in stereotype:
        object.properties["fill_colour"] = "Light Goldenrod Yellow"
    elif "yarn::orm::value" in stereotype:
        object.properties["fill_colour"] = "Plum"
    elif "yarn::exception" in stereotype:
        object.properties["fill_colour"] = "Peach Puff"
    elif "yarn::object_template" in stereotype:
        object.properties["fill_colour"] = "Azure"
    elif "handcrafted" in stereotype:
        object.properties["fill_colour"] = "Lemon Chiffon"
    else:
        object.properties["fill_colour"] = "Mint Cream"

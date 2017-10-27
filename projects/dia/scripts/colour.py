for object in dia.active_display().diagram.data.layers[0].objects:
    if object.type.name != "UML - Class":
        continue;

    name = object.properties["name"].value
    stereotype = object.properties["stereotype"].value
    if "yarn::enumeration" in stereotype:
        object.properties["fill_colour"] = "Papaya Whip"
    elif "yarn::exception" in stereotype:
        object.properties["fill_colour"] = "Peach Puff"
    elif "yarn::object_template" in stereotype:
        object.properties["fill_colour"] = "Azure"
    elif "handcrafted" in stereotype:
        object.properties["fill_colour"] = "Lemon Chiffon"
    else:
        object.properties["fill_colour"] = "Mint Cream"

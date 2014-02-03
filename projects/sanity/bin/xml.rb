require 'builder'

xml = Builder::XmlMarkup.new(target: STDOUT, indent: 2)
xml.person(type: "programmer") do
    xml.name do
        xml.first "Dave"
        xml.last "Thomas"
    end
    xml.location "Texas"
    xml.preference("ruby")
end

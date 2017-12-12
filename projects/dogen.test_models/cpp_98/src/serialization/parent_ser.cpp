#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/test_models/cpp_98/serialization/child_ser.hpp"
#include "dogen/test_models/cpp_98/serialization/parent_ser.hpp"

BOOST_CLASS_TRACKING(
    dogen::test_models::cpp_98::parent,
    boost::serialization::track_selectively)

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::test_models::cpp_98::parent& v,
    const unsigned int /*version*/) {
    ar << make_nvp("prop_0", v.prop_0_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::test_models::cpp_98::parent& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("prop_0", v.prop_0_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::test_models::cpp_98::parent& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::test_models::cpp_98::parent& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::test_models::cpp_98::parent& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::test_models::cpp_98::parent& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::test_models::cpp_98::parent& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::test_models::cpp_98::parent& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::test_models::cpp_98::parent& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::test_models::cpp_98::parent& v, unsigned int version);

} }

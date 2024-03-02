#include <fstream>
#include <iostream>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

class gps_position
{
public:
    gps_position() {}
    gps_position(int d, int m, float s) : degrees(d), minutes(m), seconds(s) {}

    std::ostream& print(std::ostream& os)
    {
        return (os << degrees << ' ' << minutes << ' ' << seconds << '\n');
    }

private:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive& ar, [[maybe_unused]] const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(degrees)
           & BOOST_SERIALIZATION_NVP(minutes)
           & BOOST_SERIALIZATION_NVP(seconds);
    }

    int degrees, minutes;
    float seconds;
};

int main() {
    std::ofstream ofs("gps.xml");

    const gps_position g(35, 59, 24.567f);

    {
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(g);
    }

    gps_position newg;
    {
        std::ifstream ifs("gps.xml");
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(newg);
        newg.print(std::cout);
    }
}

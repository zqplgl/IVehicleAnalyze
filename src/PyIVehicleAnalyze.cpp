//
// Created by zqp on 18-8-1.
//

#include<boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <Itracker.h>
#include <VehicleAnalyze.h>
#include <opencv2/opencv.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(_VehicleAnalyze)
{
    class_<cv::Rect>("zone",no_init)
            .add_property("x",&cv::Rect::x)
            .add_property("y",&cv::Rect::y)
            .add_property("w",&cv::Rect::width)
            .add_property("h",&cv::Rect::height);

    class_<tracker::Track>("track",no_init)
            .def(vector_indexing_suite<tracker::Track>())
            .def("size",&tracker::Track::size);

    class_<tracker::Tracker>("tracker",no_init)
            .add_property("track",&tracker::Tracker::track)
            .add_property("id",&tracker::Tracker::id)
            .add_property("start_frame",&tracker::Tracker::start_frame)
            .add_property("end_frame",&tracker::Tracker::end_frame)
            .add_property("cls",&tracker::Tracker::cls);

    class_<vector<tracker::Tracker> >("trackers",no_init)
            .def(vector_indexing_suite<vector<tracker::Tracker> >())
            .def("size",&vector<tracker::Tracker>::size);

    class_<VehicleAnalyze::VehicleAnalyze>("VehicleAnalyze",init<const string&,const int,const int,const int>())
            .def("input",&VehicleAnalyze::VehicleAnalyze::input)
            .def("get_trackers",&VehicleAnalyze::IVehicleAnalyze::getTracks);

}

//
// Created by zqp on 18-8-1.
//

#ifndef PROJECT_VEHICLEANALYZE_H
#define PROJECT_VEHICLEANALYZE_H

#include <opencv2/opencv.hpp>

#include <IVehicleAnalyze.h>
#include <IObjZoneDetect.h>
namespace VehicleAnalyze {

    using namespace ObjZoneDetect;
    using namespace cv;

    class VehicleAnalyze : public IVehicleAnalyze {
    public:
        VehicleAnalyze(const string &model_dir, const int gpu_id, const int frameskip, const int numnull);

        virtual void input(const string &filepath);

        virtual vector<tracker::Tracker> getTracks();

        void transform(vector<ObjZoneDetect::Object> &detect_objs, vector<tracker::Object> &tracker_objs);

    private:
        IObjZoneDetect *detector = nullptr;
        tracker::ITrackers *tracker = nullptr;
        int frameskip = 0;
        int numnull = 0;
        int gpu_id = 0;
        VideoCapture capture;
        int capindex = 0;
        float confidence_threshold = 0;
    };
}


#endif //PROJECT_VEHICLEANALYZE_H

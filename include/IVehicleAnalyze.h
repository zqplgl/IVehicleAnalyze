#ifndef IVEHICLEANALYZE_H_
#define IVEHICLEANALYZE_H_

namespace VehicleAnalyze
{
    #ifndef TRACKER
    #define TRACKER

    #include <string>
    #include <vector>

    using namespace std;

    typedef vector<cv::Rect> Track;

    struct Tracker
    {
        Track track;
        size_t id;
        int start_frame;
        int end_frame;
        int cls;
    }

    typedef vector<Tracker> Trackers;

    #endif

    class IVehicleAnalyze
    {
        public:
            virtual void input(const string &filePath)=0;
            virtual void getTracks(Trackers &trackers)=0;
            virtual ~IVehicleAnalyze(){}

    };

    IVehicleAnalyze *CreateIVehicleAnalyze(const string &model_dir,const int gpu_id,const int frameskip, const int numnull);
    void DestroyIVehicleAnalyze(IVehicleAnalyze *ptr);
}

#endif


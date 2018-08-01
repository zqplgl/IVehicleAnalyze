#ifndef IVEHICLEANALYZE_H_
#define IVEHICLEANALYZE_H_


#include <Itracker.h>
namespace VehicleAnalyze
{
    class IVehicleAnalyze
    {
        public:
            virtual void input(const string &filepath)=0;
            virtual void getTracks(vector<tracker::Tracker> &trackers)=0;
            virtual ~IVehicleAnalyze(){}
    };

    IVehicleAnalyze *CreateIVehicleAnalyze(const string &model_dir,const int gpu_id,const int frameskip, const int numnull);
}

#endif


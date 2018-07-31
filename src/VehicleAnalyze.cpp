#include <IVehicleAnalyze.h>
#include <IObjZoneDetectYoloV3.h>

namespace VehicleAnalyze
{
    using namespace ZoneDetectYoloV3;

    class VehicleAnalyze: public IVehicleAnalyze
    {
        public:
            VehicleAnalyze(const &string mode_dir,const int gpu_id, const int frameskip,const int numnull);
            virtual void input(const string &filePath);
            virtual void getTracks(Trackers &trackers);

        private:
            IObjZoneDetectYoloV3 *detector=nullptr;
            int frameskip=0;
            int numnull=0;
            int gpu_id = 0;
    };

    VehicleAnalyze::VehicleAnalyze(const &string mode_dir,const int gpu_id, const int freamskip,const int numnull):frameskip(frameskip),numnull(numnull),gpu_id(gpu_id)
    {
        detector = CreateObjZoneYoloV3Detector();
    }

    void VehicleAnalyze::input(const string &filePath)
    {
    }

    void VehicleAnalyze::getTracks(Trackers &trackers)
    {
    }




    IVehicleAnalyze *CreateIVehicleAnalyze(const string &model_dir,const int gpu_id, const int frameskip, const int numnull)
    {
        IVehicleAnalyze *ptr=nullptr;
        ptr = new VehicleAnalyze(model_dir,gpu_id,freamSkip,nullNull);

        return ptr;

    }

    void DestroyIVehicleAnalyze(IVehicleAnalyze *ptr)
    {
        delete ptr;
    }
}

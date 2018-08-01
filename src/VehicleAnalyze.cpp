#include <opencv2/opencv.hpp>

#include <IVehicleAnalyze.h>
#include <IObjZoneDetect.h>

namespace VehicleAnalyze
{
    using namespace ObjZoneDetect;
    using namespace cv;

    class VehicleAnalyze: public IVehicleAnalyze
    {
        public:
            VehicleAnalyze(const string& model_dir,const int gpu_id, const int frameskip,const int numnull);
            virtual void input(const string &filepath);
            virtual void getTracks(vector<tracker::Tracker> &trackers);

        private:
            IObjZoneDetect *detector=nullptr;
            int frameskip=0;
            int numnull=0;
            int gpu_id = 0;
            VideoCapture capture;
            int capindex = 0;
            float confidence_threshold = 0;
    };

    VehicleAnalyze::VehicleAnalyze(const string& model_dir,const int gpu_id, const int freamskip,const int numnull):frameskip(frameskip),numnull(numnull),gpu_id(gpu_id)
    {
        string temp_model_dir = "";
        if(model_dir[model_dir.size()-1]=='/')
            temp_model_dir = model_dir;
        else
            temp_model_dir = model_dir + "/";


        detector = CreateObjZoneYoloV3Detector(temp_model_dir+"yolov3/yolov3.cfg",temp_model_dir+"yolov3/yolov3.weights",gpu_id);
        confidence_threshold = 0,65;
    }

    void VehicleAnalyze::input(const string &filepath)
    {
        capture.open(filepath);
    }

    void VehicleAnalyze::getTracks(vector<tracker::Tracker> &trackers)
    {
        Mat frame;
        int null_num = 0;
        int skip_num = 0;

        vector<ObjZoneDetect::Object> objs;
        while(capture.read(frame))
        {
            if(null_num < numnull)
            {
                detector->Detect(frame,objs,confidence_threshold);
                if (!objs.size())
                {
                    null_num++;
                }
            }
            else if(skip_num < frameskip)
            {
                skip_num++;
            }
            else
            {
                skip_num = 0;
                null_num = 0;
            }

            capindex++;

        }
    }

    IVehicleAnalyze *CreateIVehicleAnalyze(const string &model_dir,const int gpu_id, const int frameskip, const int numnull)
    {
        IVehicleAnalyze *ptr=nullptr;
        ptr = new VehicleAnalyze(model_dir,gpu_id,frameskip,numnull);

        return ptr;
    }
}

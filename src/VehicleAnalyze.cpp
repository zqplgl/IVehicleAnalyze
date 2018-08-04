#include <opencv2/opencv.hpp>

#include <IVehicleAnalyze.h>
#include <IObjZoneDetect.h>
#include <VehicleAnalyze.h>

namespace VehicleAnalyze
{
    using namespace ObjZoneDetect;
    using namespace cv;

    VehicleAnalyze::VehicleAnalyze(const string& model_dir,const int gpu_id, const int frameskip,const int numnull):gpu_id(gpu_id),frameskip(frameskip),numnull(numnull)
    {
        string temp_model_dir = "";
        if(model_dir[model_dir.size()-1]=='/')
            temp_model_dir = model_dir;
        else
            temp_model_dir = model_dir + "/";


        detector = CreateObjZoneYoloV3Detector(temp_model_dir+"yolov3/yolov3.cfg",temp_model_dir+"yolov3/yolov3.weights",0);
        confidence_threshold = 0.65;
        tracker = tracker::CreateITrackers();
    }

    void VehicleAnalyze::input(const string &filepath)
    {
        capture.open(filepath);
    }

    void VehicleAnalyze::transform(vector<ObjZoneDetect::Object> &detect_objs,vector<tracker::Object> &tracker_objs)
    {
        tracker_objs.clear();
        for(int i=0; i<detect_objs.size(); ++i)
        {
            tracker::Object obj;
            obj.first = detect_objs[i].zone;
            obj.second = detect_objs[i].cls;
            tracker_objs.push_back(obj);
        }
    }

    vector<tracker::Tracker> VehicleAnalyze::getTracks()
    {
        cout<<"gpu_id: "<<gpu_id<<endl;
        cout<<"frameskip: "<<frameskip<<endl;
        cout<<"numnull: "<<numnull<<endl;
        vector<tracker::Tracker> trackers;
        Mat frame;
        int null_num = 0;
        int skip_num = 0;

        vector<ObjZoneDetect::Object> objs;
        vector<tracker::Object> tracker_objs;
        while(capture.read(frame))
        {
            cout<<"process frame: "<<capindex<<endl;
            if(null_num < numnull)
            {
                detector->Detect(frame,objs,confidence_threshold);
                cout<<"objs: "<<objs.size()<<endl;
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

            transform(objs,tracker_objs);
            tracker->Update(tracker_objs,capindex);
            capindex++;
        }

        vector<tracker::Tracker> trackers_over,trackers_running;
        tracker->getTracks(trackers_over,trackers_running);

        for (int i=0; i<trackers_over.size(); ++i)
        {
            trackers.push_back(trackers_over[i]);
        }

        for (int i=0; i<trackers_running.size(); ++i)
        {
            trackers.push_back(trackers_running[i]);
        }

        return trackers;
    }

    IVehicleAnalyze *CreateIVehicleAnalyze(const string &model_dir,const int gpu_id, const int frameskip, const int numnull)
    {
        IVehicleAnalyze *ptr=nullptr;
        ptr = new VehicleAnalyze(model_dir,gpu_id,frameskip,numnull);

        return ptr;
    }
}

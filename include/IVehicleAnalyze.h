#ifndef IVEHICLEANALYZE_H_
#define IVEHICLEANALYZE_H_

#ifndef TRACKER
#define TRACKER

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
        virtual void getTracks()=0;
        virtual ~IVehicleAnalyze(){}

};

IVehicleAnalyze *CreateIVehicleAnalyze(int freamSkip, int numNull);
void DestroyIVehicleAnalyze();


#endif
